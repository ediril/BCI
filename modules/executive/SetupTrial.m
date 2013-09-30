function SetupTrial()

    global XM;
    global DF;

    fprintf('\n');

    % Tell EM to reload its configuration file
    msg = DF.MDF.RELOAD_CONFIGURATION;
    SendMessage('RELOAD_CONFIGURATION', msg);

    %--- increment the trial number and attempted start number
    XM.trial_num = XM.trial_num + 1; % Increment the count of trial numbers
    XM.trial_started = false; % Reset the flag that tells the later task states whether the monkey succeeded at starting a trial

    CallFailSafe('LoadXMConfigFile', XM.config_file_name);

    % if recevied num_reps from XM_START_SESSION msg, use it
    if ~isempty(XM.num_reps)
        XM.config.num_reps = XM.num_reps;
    end

    SendMessage( 'DENSO_SET_SPEED', struct( 'speed', XM.config.denso_speed));

    XM.insert_alternate_state = false;
    if isfield(XM.config, 'alternate_occurrence_freq')
        if ~isfield(XM.config, 'alternate_occurrence_rep') || ...
           (isfield(XM.config, 'alternate_occurrence_rep') && (XM.rep_num >= XM.config.alternate_occurrence_rep))
            if (rand < XM.config.alternate_occurrence_freq)
                [prob_list, orig_idx] = sort(XM.config.alternate_state_config_freq);
                prob = rand;
                for c = 1 : length(prob_list)
                    if (prob <= sum(prob_list(1:c)))
                        alt_file_idx = orig_idx(c);
                        break;
                    end
                end
                alternate_state_config_file = XM.config.alternate_state_config_files{alt_file_idx};

                %DisplayMessageToUser(['--- Using alternate state config file: ' alternate_state_config_file]);

                %--- Reload all configuration files, so we can do live updates
                CallFailSafe('LoadTaskStateConfigFile', alternate_state_config_file);

                XM.insert_alternate_state = true;
            end
        end
    end

    if ~XM.insert_alternate_state
        % Increment rep counter
        if( isempty( XM.combos_to_be_tried))
            XM.rep_num = XM.rep_num + 1;
        end

        fprintf('\n======= [ Trial #%d, Rep #%d ] =======\n', XM.trial_num, XM.rep_num);

        %--- Reload all configuration files, so we can do live updates
        CallFailSafe('LoadTaskStateConfigFile',  GetTaskStateConfigFileName());

        %--- Start a new rep if there are no targets left to be tried
        if( isempty( XM.combos_to_be_tried))
            % Reset targets
            num_combos = length(XM.config.task_state_config.target_configurations.combos.home);
            XM.combos_to_be_tried = 1 : num_combos;
            XM.num_times_tried_combo = zeros( 1, num_combos);
        end

        %--- select next target out of those that are still to be tried
        tool_selection_method = XM.config.task_state_config.target_configurations.combos.selection_method;
        if( ~isempty(findstr(lower(tool_selection_method), 'sequential')))
            XM.active_combo_index = XM.combos_to_be_tried(1);
        elseif( ~isempty(findstr(lower(tool_selection_method), 'random')))
            XM.active_combo_index = XM.combos_to_be_tried(random('Discrete Uniform',length(XM.combos_to_be_tried)));
        else
            fprintf('\nWarning: Invalid target_configurations.combos.selection_method "%s"\n', tool_selection_method);
            fprintf('defaulting to random\n');
            XM.active_combo_index = XM.combos_to_be_tried(random('Discrete Uniform',length(XM.combos_to_be_tried)));
        end

        if( XM.config.max_num_tries_per_target > 0 )
            num_tries_left = num2str(XM.config.max_num_tries_per_target - XM.num_times_tried_combo(XM.active_combo_index));
            DisplayMessageToUser([num_tries_left ' tries left for this combo']);
        else
            num_tries_left = 'INFINITE';
        end
    else
        num_combos = length(XM.config.task_state_config.target_configurations.combos.tool);
        combos_to_be_tried = 1 : num_combos;
        XM.active_combo_index = combos_to_be_tried(random('Discrete Uniform',length(combos_to_be_tried)));
    end

    XM.active_tool_id = 1;
    if isfield(XM.config.task_state_config.target_configurations.combos, 'tool')
        XM.active_tool_id = XM.config.task_state_config.target_configurations.combos.tool(XM.active_combo_index);
    end

    fprintf('Using combo index: %d,  tool_id: %d\n', XM.active_combo_index, XM.active_tool_id);


    if( XM.config.enable_denso && XM.config.do_tool_change)
        %fprintf('\nChanging tool to %d\n', XM.active_tool_id);

        tc = DF.MDF.CHANGE_TOOL;
        tc.next_tool_id = int32(XM.active_tool_id);
        SendMessage( 'CHANGE_TOOL', tc);

        fprintf('\nWaiting for tool change to complete (Press R1 to proceed if stuck) ...');
        ExpectedEvents = {'CHANGE_TOOL_COMPLETE', 'CHANGE_TOOL_INVALID', 'PROCEED_TO_NextState'};
        RcvEvt = WaitFor( 100, ExpectedEvents{:});

        if ~strcmp(RcvEvt.msg_type, 'CHANGE_TOOL_INVALID')
            MoveDenso('Present', XM.config.task_state_config.target_configurations.denso_away_moveID);
            fprintf('done\n\n');
        else
            fprintf('\nERROR: Tool change failed!\n');
        end
    end


    % Tell SPM to flag the next sample as an alignment sample
    % So that we can get an alignment pulse from the robot controller
    % to get an unambiguous alignment between samples and timing pulses
    SendSignal RESET_SAMPLE_ALIGNMENT;

    if(isfield(XM, 'runtime'))
      XM.runtime.cancel_button_pressed = 0;
    end

    XM.penalty_time = 0;

    %--- Send out informational message that says how this trial is configured (for anyone that cares)
    SendTrialConfig( );
