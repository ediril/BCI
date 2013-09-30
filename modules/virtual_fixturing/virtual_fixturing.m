function virtual_fixturing( config_filename,mm_ip)

% virtual_fixturing( config_filename)
%
% This module implements Virtual Fixturing, i.e. taking an extrinsic command
% that is assumed to be imperfect, and an intrinsic command assumed to be
% perfect, and constraining the extrinsic command to a manifold determined
% by the intrinsic command.
%
% It implements the following equation:
% v = D_m * u  +  (I - R_r) * D_r * u, where:
%
% u - extrinsic (user) command
% v - output command
% D_m - matrix that projects u onto a desired Manifold
% D_r - matrix that projects u onto a direction oRthogonal to the
%       manifold
% R_r - orthogonal impedance
%
% Meel Velliste 4/5/2011

    DragonflyPath = getenv('DRAGONFLY');
    IncludePath = getenv('BCI_INCLUDE');
    CommonPath = getenv('BCI_COMMON');

    addpath([DragonflyPath '/lang/matlab']);
    addpath([CommonPath '/matlab']);

    %
    % Make sure config file exists and load it
    %
    if( ~exist( 'config_filename', 'var'))
        error('Config file must be specified as an input argument');
    end
    if( ~exist( config_filename, 'file'))
        error(['Cannot find config file: ' config_filename]);
    end
    config = LoadTextData( config_filename);
    config = InitializeVariables( config);

    ConnectArgs = { 'VIRTUAL_FIXTURING', '', [IncludePath '/Dragonfly_config.mat']};
    if exist('mm_ip','var') && ~isempty(mm_ip)
        ConnectArgs{end+1} = ['-server_name ' mm_ip];
    end
    ConnectToMMM(ConnectArgs{:})

    Subscribe ROBOT_CONTROL_CONFIG;
    Subscribe PLANNER_MOVEMENT_COMMAND;
    Subscribe EM_MOVEMENT_COMMAND;
    Subscribe OPERATOR_MOVEMENT_COMMAND;
    Subscribe EXIT;
    Subscribe PING;


    while( 1)
        M = ReadMessage( 1);
        if( isempty( M))
            fprintf('.');
        else
            config = ProcessMessage( M, config);
        end
    end


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function config = ProcessMessage( M, config)

    switch( M.msg_type)

        case 'PING'
            RespondToPing(M, 'virtual_fixturing');

        case 'EXIT'
            if (M.dest_mod_id == GetModuleID()) || (M.dest_mod_id == 0)
                SendSignal EXIT_ACK
                DisconnectFromMMM
                exit
            end

        case 'ROBOT_CONTROL_CONFIG'
            rc_config = M.data;
            config.ortho_impedance = rc_config.orthVelImpedance';
        case 'PLANNER_MOVEMENT_COMMAND'
            ideal_velocity = M.data.vel';
            % By default, the target cloud consists of just the ideal
            % movement vector
            config.target_cloud = ideal_velocity;
        case {'EM_MOVEMENT_COMMAND','OPERATOR_MOVEMENT_COMMAND'}
            incoming_tag = deblank(char(M.data.tag));
            %disp(['<' incoming_tag '>'])
            %disp(['<' config.input_tag '>'])
            if strcmp(incoming_tag,config.input_tag)
                extrinsic_cmd = M.data.vel';
                output_cmd = zeros( size( extrinsic_cmd));
                
                if ~all(abs(extrinsic_cmd) < eps)
                    unique_domains = unique( config.domain_map(config.domain_map~=0));
                    for i = 1 : length( unique_domains)
                        this_domain = unique_domains(i);
                        domain_mask = (config.domain_map == this_domain);
                        D = config.target_cloud(domain_mask);
                        if config.bidirectional, D = [D -1*D]; end
                        u = extrinsic_cmd(domain_mask);
                        domain_admittance = 1 - config.ortho_impedance(domain_mask);
                        Ct = diag( domain_admittance);
                        v = apply_ortho_impedance( D, u, Ct);
                        output_cmd(domain_mask) = v;
                    end
                end
                
                SendCommand( output_cmd, M.data, config.output_tag, config.domain_map);
            end
    end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function config = InitializeVariables( config)

    config.domain_map = config.domain_map(:); % Make it a column vector
    config.ortho_impedance = zeros( size( config.domain_map));
    config.target_cloud = zeros( size( config.domain_map));

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function SendCommand( output_cmd, incoming_data, tag, domain_map)

    outgoing_data = incoming_data;
    outgoing_data.controlledDims(:) = logical(domain_map);
    outgoing_data.vel = output_cmd(:)';
    outgoing_data.tag(1:length(tag)) = tag;
    outgoing_data.tag(length(tag)+1:end) = 0;
    SendMessage( 'FIXTURED_MOVEMENT_COMMAND', outgoing_data);
