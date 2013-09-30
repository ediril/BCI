function virtual_cursor(confFileFullPath, mm_ip)

    dbstop if error

    global DF;
    
    global first_time;

    first_time = 0;

    DragonflyPath = getenv('DRAGONFLY');
    CommonPath = getenv('BCI_COMMON');
    App_IncDir = getenv('BCI_INCLUDE');

    addpath([DragonflyPath '/lang/matlab']);
    addpath([CommonPath '/matlab']);

    C = struct();
    C.config = LoadConfigFile( confFileFullPath);

    MessageTypes = { ...
                    C.config.command_msg, ...
                    'RELOAD_CONFIGURATION', ...
                    'PING', ...
                    'EXIT' ...
                   };

    disp('virtual_cursor running..');

    if(~exist(confFileFullPath, 'file'))
       disp(['conf file ' confFileFullPath ' does not exists']);
       return;
    end
   
    ConnectArgs = {0, DragonflyPath, [App_IncDir '/Dragonfly_config.mat']};
    if exist('mm_ip','var') && ~isempty(mm_ip)
        ConnectArgs{end+1} = ['-server_name ' mm_ip];
    end    
   
    ConnectToMMM(ConnectArgs{:});
    Subscribe( MessageTypes{:})
    SendModuleReady( );

    % initialize pos and cori
    C.pos = zeros(1, DF.defines.MAX_CONTROL_DIMS);    %M.data.pos;
    C.cori = eye(3); %reshape( M.data.CoriMatrix, [3 3])';

    
    while( ~isempty( C))
        M = ReadMessage( 1);
        if( isempty(M))
            %fprintf('.')
        else
            C = ProcessMessage( C, M, confFileFullPath);
        end
    end
     
    'All done, nothing else to do, Exiting now...'
    DisconnectFromMMM
    exit

    
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function C = ProcessMessage( C, M, confFileFullPath)

    global DF;
    global first_time ;

    switch(M.msg_type)

        case C.config.command_msg

            % vel
            dims = logical(C.config.controlledDims);
            vel_vector = zeros(1, 18);
            vel_vector(dims) = M.data.vel(dims);

            Ni_tra = [0 0 0];
            if isfield(C.config.translation, 'noise')
                Ni_tra = normrnd(0, C.config.translation.noise, [1 3]);
            end
            
            Ni_ori = [0 0 0];
            if isfield(C.config.orientation, 'noise')
                Ni_tra = normrnd(0, C.config.orientation.noise, [1 3]);
            end
            
            % trans dims
            iii = (1:3);
            trans_vel = M.data.vel(iii);
            
        % -------------------------------------
            thresh = [0.06 0.14 0.14];
            ign = abs(trans_vel) <= thresh;
            trans_vel(ign) = trans_vel(ign)/50;
            lt = (trans_vel < 0) & (abs(trans_vel) > thresh);
            trans_vel(lt) = trans_vel(lt) + thresh(lt);
            gt = (trans_vel > 0) & (abs(trans_vel) > thresh);
            trans_vel(gt) = trans_vel(gt) - thresh(gt);
        % -------------------------------------            
        
            trans_vel = trans_vel + Ni_tra; % add noise
            
            incr = trans_vel * M.data.sample_header.DeltaTime;
            C.pos(iii) = C.pos(iii) + incr;
            
            % orient dims
            iii = (5:7);
            incr = zeros(1,18);
            ori_vel = M.data.vel(iii);
            
            ori_vel = ori_vel + Ni_ori;     % add noise
            
%            if isfield(C.config.orientation, 'coordinate_space') && ...
%                strcmpi(C.config.orientation.coordinate_space, 'local')            
%                ori_vel = (C.cori * ori_vel')';
%            end
            incr(iii) = ori_vel * M.data.sample_header.DeltaTime;
            incr_mat = Rodrigues(incr(5:7))';
            
            if first_time < 2
                C.cori 
            end
            
            
            C.cori = incr_mat * C.cori;
            [rotaxis, rotangle] = rotmat2rotvec(C.cori);

            if first_time < 2
                
                rotangle
                
               % incr2 = M.data.vel(iii)/2;
               % incr_mat2 = Rodrigues(incr2)'
                
                disp '-------------------'
                
                first_time = first_time + 1;
            end

            if (rotangle < 0),   error('whaa?');        end

            if (rotangle > C.config.ori_limit)
                %disp '** ORI LIMIT reached **'
                %rotangle
                %C.cori

                rotvec = rotaxis * C.config.ori_limit;
                C.cori = Rodrigues(rotvec)';

                %[rotaxis2, rotangle2] = rotmat2rotvec(C.cori);
                %rotangle2
                %C.cori
                %disp '------------'
            end

            upper = C.pos > C.config.upper_limits;
            upper(5:7) = false;
            C.pos(upper) = C.config.upper_limits(upper);
            
            lower = C.pos < C.config.lower_limits;
            lower(5:7) = false;
            C.pos(lower) = C.config.lower_limits(lower);
            
            transposed_cori = C.cori';

            fdbk = DF.MDF.ROBOT_CONTROL_SPACE_ACTUAL_STATE;
            fdbk.sample_header = M.data.sample_header;
            fdbk.pos(1:length(C.pos)) = C.pos;
            fdbk.vel(1:length(vel_vector)) = vel_vector;
            fdbk.CoriMatrix(:) = transposed_cori(:)';
            SendMessage( 'ROBOT_CONTROL_SPACE_ACTUAL_STATE', fdbk); 

        case 'RELOAD_CONFIGURATION'
            C.config = LoadConfigFile( confFileFullPath);

        case 'PING'
            RespondToPing(M, 'virtual_cursor');
        
        case 'EXIT'
            if (M.dest_mod_id == GetModuleID()) || (M.dest_mod_id == 0)
                SendSignal EXIT_ACK
                C = [];
            end
    end         

