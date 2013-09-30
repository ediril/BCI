function SSH_Controller(confFileFullPath, mm_ip)

   % dbstop if error

    global DF;

    DragonflyPath = getenv('DRAGONFLY');
    CommonPath = getenv('BCI_COMMON');
    App_IncDir = getenv('BCI_INCLUDE');

    addpath([RTMAPath '/lang/matlab']);
    addpath([CommonPath '/Matlab']);
    addpath([CommonPath '/VulcanX_M']);

    C = InitializeController( confFileFullPath);

    MessageTypes = { ...
                    C.config.command_msg, ...
                    'WAM_FEEDBACK', ...
                    'WAM_HAND_FEEDBACK', ...
                    'RELOAD_CONFIGURATION', ...
                    'PING' ...
                    'EXIT' ...
                   };


    disp('SSH_Controller');

    if(~exist(confFileFullPath, 'file'))
       disp(['conf file ' confFileFullPath ' does not exists']);
       return;
    end

    ConnectArgs = {'SSH_CONTROLLER', DragonflyPath, [App_IncDir '/Dragonfly_config.mat']};
    if exist('mm_ip','var') && ~isempty(mm_ip)
        ConnectArgs{end+1} = ['-server_name ' mm_ip];
    end

    ConnectToMMM(ConnectArgs{:});
    Subscribe( MessageTypes{:})
    SendModuleReady( );

    while( ~isempty( C))
        M = ReadMessage( 1);
        if( isempty(M))
            fprintf('.')
        else
            C = ProcessMessage( C, M);
        end
    end

    'All done, nothing else to do, Exiting now...'
    DisconnectFromMMM
    exit


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function C = ProcessMessage( C, M)

    switch(M.msg_type)

        case C.config.command_msg

            finger_output_type = C.hand_controller.config.output_type;

            % We hope to have received feedback from robot before
            % we process a command
            if( isfield( C.Pf, 'arm')) % && isfield( C.Pf, 'hand'))

                % Pick components out of incoming command
                Vc = M.data.vel;
                Vc_transl = Vc(1:3);
                Vc_orient = Vc(5:7);
                Vc_hand = Vc(9:18);
                Pc = M.data.pos';
                Pc_hand = Pc(9:18);
                dt = M.data.sample_header.DeltaTime;

                % Pick components out of raw feedback
                Pf_arm.pos = C.Pf.arm.pos([1:3, 5:7]);
                Pf_arm.R = C.Pf.arm.CoriMatrix;

                % Pick out the following 10 finger joints:
                %  1. Finger1
                %  2. Finger2
                %  3. Finger3
                %  4. Spread
%                Pf_fingers = C.Pf.hand.pos([9 10 11 12])';

                % Evaluate Arm Control Law
                [C.arm_controller, Vc_transl_robot, Vc_orient_robot, ...
                    Pf_transl, Pf_orient, Vf_transl, Vf_orient, Pf_R] = ...
                    EvaluateArmControlLaw( C.arm_controller, Vc_transl, Vc_orient, Pf_arm, C.config.output_offsets, dt);

                % Evaluate Hand Control Law
%                [C.hand_controller, Pc_fingers, Pf_hand, Vf_hand] = ...
%                    EvaluateHandControlLaw( C.hand_controller, Vc_hand, Pc_hand, Pf_fingers, dt);
                Pc_fingers = zeros( size( Pc_hand));
                Pf_hand = zeros( size( Pc_hand));
                Vf_hand = zeros( size( Pc_hand));

                % Send Robot command
                SendMovementCommand( M.data.sample_header, Vc_transl_robot, Vc_orient_robot, Pc_fingers, finger_output_type);

                % Send out control space feedback
                SendFeedback( M.data.sample_header, Pf_transl, Pf_orient, Pf_hand, Vf_transl, Vf_orient, Vf_hand, Pf_R);

%                 Vc_transl_robot
%                 Vc_orient_robot
%                 Pc_fingers
%                 Pf_hand
%                 Vf_hand

            else
                % if no feedback yet, send out zero vel command
                Vc_transl_robot = zeros(1, 3);
                Vc_orient_robot = zeros(1, 3);
                Pc_fingers = zeros(1, 10);
                SendMovementCommand( M.data.sample_header, Vc_transl_robot, Vc_orient_robot, Pc_fingers, finger_output_type);
            end


        case 'WAM_FEEDBACK'
            C.Pf.arm = M.data;

        case 'WAM_HAND_FEEDBACK'
            C.Pf.hand = M.data;

        case 'RELOAD_CONFIGURATION'
            % We might want to implement reloading on the fly
            C.config.output_offsets = LoadOutputOffsets();

        case 'PING'
            RespondToPing(M, 'SSH_Controller');

        case 'EXIT'
            if (M.dest_mod_id == GetModuleID()) || (M.dest_mod_id == 0)
                SendSignal EXIT_ACK
                C = [];
            end
    end

