
function CleverMonkey(config_file, mm_ip)

    dbstop if error;

    global RTMA;

    RTMAPath = getenv('RTMA');
    SourcePath = getenv('ROBOTSRC');
	CommonPath = getenv('ROBOT_COMMON');
    IncludePath = getenv('ROBOTINC');

    addpath([RTMAPath '/lang/matlab']);
	addpath([CommonPath '/Matlab']);

    RTMAConfigFile = [IncludePath '/RTMA_config.mat'];
    ConnectArgs = {0, '', RTMAConfigFile};
    if exist('mm_ip','var') && ~isempty(mm_ip)
        ConnectArgs{end+1} = ['-server_name ' mm_ip];
    end
    ConnectToMMM(ConnectArgs{:})

    Subscribe RELOAD_CONFIGURATION
    Subscribe ROBOT_CONTROL_SPACE_ACTUAL_STATE
    Subscribe ROBOT_CONTROL_CONFIG
    Subscribe TASK_STATE_CONFIG
    Subscribe END_TASK_STATE
    Subscribe EXIT
    Subscribe PING

    trans_threshold = nan;
    reach_offset_enabled = 0;
    target_configured = 0;
    inside_cone = 0;
    task_state_configured = 0;

    config = LoadModuleConfigFile(config_file);

    disp('CleverMonkey running...');

    while(1)
        M = ReadMessage( 1);
        if(isempty(M))
            %fprintf('.')
        else
            % Perform message processing specific to SimpleMonkey
            switch( M.msg_type)

                case 'END_TASK_STATE'
                    fprintf(' E ');
                    % reset control flags
                    target_configured = 0;
                    reach_offset_enabled = 0;
                    inside_cone = 0;
                    task_state_configured = 0;

                case 'TASK_STATE_CONFIG'
                    fprintf(' C ');
                    trans_threshold = M.data.trans_threshold;
                    reach_offset_enabled = M.data.reach_offset;
                    task_state_configured = 1;

                case 'ROBOT_CONTROL_CONFIG'
                    fprintf(' R ');
                    trial_config = M.data;
                    tgt_pos = trial_config.target(1:3);
                    rch_vec = TargetOffset(trial_config.target(5:7), config.reach_offset);
                    rch_pos = tgt_pos + rch_vec;
                    tip_offset_vec = TargetOffset(trial_config.target(5:7), -config.cone_tip_offset);
                    tip_pos = tgt_pos - tip_offset_vec;
                    robot_tgt = [];
                    target_configured = 1;

                case 'ROBOT_CONTROL_SPACE_ACTUAL_STATE'
                    %if target_configured
                    if target_configured && task_state_configured
                        new_tgt = tgt_pos;

                        if reach_offset_enabled
                            fbk_pos = M.data.pos(1:3);
                            tgt_dist = sqrt( sum( (tgt_pos-fbk_pos) .^2 ))

                            if (tgt_dist > trans_threshold)
                                %tgt_pos
                                %rch_pos
                                fbk_vec = fbk_pos - tip_pos;
                                rch_offset_vec = rch_pos - tip_pos;
                                vec_ang = acos((rch_offset_vec*fbk_vec')/(mag(rch_offset_vec')*mag(fbk_vec')));

                                raw_fbk_vec = fbk_pos - tgt_pos;
                                %rch_vec
                                dist_to_plane = raw_fbk_vec * (rch_vec' / config.reach_offset);

                                if ~inside_cone
                                    if (vec_ang <= config.inner_cone_angle)
                                        inside_cone = 1;
                                        new_tgt = tgt_pos;
                                        fprintf('\nOC ** IN **\n');
                                    else
                                        if (dist_to_plane < config.distance_to_plane)
                                            inside_cone = 0;
                                            new_tgt = fbk_pos + rch_vec
                                            fprintf('\nOC  PLANE\n');
                                        else
                                            new_tgt = rch_pos;
                                            fprintf('\nOC  OUT\n');
                                        end
                                    end
                                else
                                    if (vec_ang <= config.outer_cone_angle)
                                        new_tgt = tgt_pos;
                                        fprintf('\nIC ** IN **\n');
                                    else
                                        inside_cone = 0;
                                        new_tgt = rch_pos;
                                        fprintf('\nIC  OUT\n');
                                    end
                                end
                            else
                                fprintf('\nAT TARGET\n');
                            end
                        end

                        if isempty(robot_tgt) || ~all(robot_tgt == new_tgt)
                            robot_tgt = new_tgt;
                            target = [robot_tgt trial_config.target(4:end)];
                            msg = RTMA.MDF.PLANNER_CONTROL_CONFIG;
                            msg.target = target;
                            msg.coriMatrix = trial_config.coriMatrix;
                            SendMessage( 'PLANNER_CONTROL_CONFIG', msg);
                        end
                    end

                case 'RELOAD_CONFIGURATION'
                    c = LoadModuleConfigFile(config_file);
                    if ~isempty(c)
                        disp 'config reloaded'
                        config = c;
                        config.outer_cone_angle
                        config.inner_cone_angle
                    end

                case 'PING'
                    RespondToPing(M, 'CleverMonkey');

                case 'EXIT'
                    if (M.dest_mod_id == GetModuleID()) || (M.dest_mod_id == 0)
                        SendSignal EXIT_ACK
                        break;
                    end

            end
        end
    end
    DisconnectFromMMM
    exit



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function vec = TargetOffset(ori, len)
% calculate xyz components of an offset corresponding to a length
% `len' at orientation angle `ori`

    % len_prime is length of projection of orientation * len on horizontal plane
    len_prime = abs(len * cos(ori(2)));
    vec = [len_prime * cos(ori(3)), len_prime * sin(ori(3)), -len * sin(ori(2))];

