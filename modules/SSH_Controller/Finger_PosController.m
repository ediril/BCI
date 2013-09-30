function Finger_Controller(confFileFullPath, mm_ip, finger_idx, finger_val)

    %dbstop if error

    global RTMA;

    RTMAPath = getenv('RTMA');
    CommonPath = getenv('ROBOT_COMMON');
    App_IncDir = getenv('ROBOTINC');

    addpath([RTMAPath '/lang/matlab']);
    addpath([CommonPath '/Matlab']);
    addpath([CommonPath '/VulcanX_M']);

    C = InitializeController( confFileFullPath);

    MessageTypes = { ...
                    C.config.command_msg, ...
                    'GROBOT_RAW_FEEDBACK', ...
                    'EXIT' ...
                   };

    disp('SSH_Controller');

    if(~exist(confFileFullPath, 'file'))
       disp(['conf file ' confFileFullPath ' does not exists']);
       return;
    end
   
    ConnectArgs = {0, RTMAPath, [App_IncDir '/RTMA_config.mat']};
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
            C = ProcessMessage( C, M, finger_idx, finger_val);
        end
    end
     
    'All done, nothing else to do, Exiting now...'
    DisconnectFromMMM

    
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function C = ProcessMessage( C, M, finger_idx, finger_val)

    global RTMA;

    switch(M.msg_type)

        case C.config.command_msg

            % We hope to have received feedback from robot before
            % we process a command
            if( isfield( C, 'Pf'))

                % Pick components out of incoming command
                Vc = M.data.vel';
                Vc_transl = Vc(1:3);
                Vc_orient = Vc(5:7);
                Vc_hand = Vc(9:18);
                dt = M.data.sample_header.DeltaTime;

            end


        case 'GROBOT_RAW_FEEDBACK'

            C.Pf = M.data.j_ang';

            % Pick components out of raw joint angle feedback
            Pf_arm_joints = C.Pf(1:7);
            % Pick out the following 10 finger joints:
            %  1. IndexAbAd
            %  2. IndexMCP
            %  3. MiddleMCP
            %  4. RingMCP
            %  5. LittleAbAd
            %  6. LittleMCP
            %  7. ThumbAbAd
            %  8. ThumbCMC
            %  9. ThumbMCP
            % 10. ThumbDIP
            Pf_fingers = C.Pf([8 9 13 17 20 21 24 25 26 27]);

            % Evaluate PD control law
            finger_Pf = Pf_fingers(finger_idx);
            finger_error = finger_val - finger_Pf;
            command_val = finger_Pf + finger_error*4;

            Pc_fingers = zeros(1,10);
            Pc_fingers(finger_idx) = command_val;
            
            % Send Robot command
            finger_output_type = 'pos';
            sample_header = RTMA.typedefs.SAMPLE_HEADER;
            SendMovementCommand( sample_header, [0 0 0], [0 0 0], Pc_fingers, finger_output_type);
            
        case 'RELOAD_CONFIGURATION'
            % We might want to implement reloading on the fly

        case 'EXIT'
            C = [];
    end         
