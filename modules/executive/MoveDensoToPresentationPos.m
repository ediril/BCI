function MoveDensoToPresentationPos( task_state_config)

% MoveDensoToPresentationPos( task_state_config)
%
% Moves DENSO robot to the presentation position that has been selected for
% the current trial

    global XM;
    global DF;


    if( XM.config.enable_denso && task_state_config.use_denso )

        if strcmp(task_state_config.present_target, '-') == 0

            if strcmp(task_state_config.present_target, 'wiggle')
                tool_cfg = sprintf('config_tool_%d', XM.active_tool_id);
                amplitude = task_state_config.target_configurations.(tool_cfg).wiggle_amplitude;
                num_cycles = task_state_config.target_configurations.(tool_cfg).wiggle_num_cycles;
                sequence = task_state_config.target_configurations.(tool_cfg).wiggle_sequence;

                XM.Denso.CurrentMoveID = XM.Denso.CurrentMoveID + 1;

                msg = DF.MDF.DENSO_WIGGLE;
                msg.movement_id(1) = XM.Denso.CurrentMoveID;
                msg.num_cycles(1) = num_cycles;
                msg.amplitude = amplitude;
                msg.sequence(1:length(sequence)) = sequence;
                SendMessage( 'DENSO_WIGGLE', msg);

            else
                denso_target_config = sprintf('config_%s', task_state_config.present_target);
                denso_tgt_idx = 1;
                if (length(task_state_config.target_configurations.(denso_target_config).target_denso_moveIDs) > 1)
                    denso_tgt_idx = task_state_config.target_configurations.combos.(task_state_config.present_target)(XM.active_combo_index);
                end
                PosNumber = task_state_config.target_configurations.(denso_target_config).target_denso_moveIDs(denso_tgt_idx);

                %fprintf('Denso target: %s,  idx: %d,  pos_num: %d\n', task_state_config.present_target, denso_tgt_idx, PosNumber);

                MoveDenso( 'Present', PosNumber);
            end
        end
    end
