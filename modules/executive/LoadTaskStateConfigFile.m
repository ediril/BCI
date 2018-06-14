function LoadTaskStateConfigFile( FileName)
%   LoadTaskStateConfigFile( FileName)
%
%   Loads a task state config file, given by FileName into XM.config.task_state_config
%   FileName should be the file name (not path) of the config file. If
%   "mode" is 'verify' then loads the file and performs consistence checks
%   but does not assign them to XM. If no arguments are specified, then
%   just loads the task state config for the current rep.

    global XM;

    config_file_path = [XM.config_files_dir '/' FileName];
    VerifyFileExists(config_file_path);

    % DisplayMessageToUser( [caller_name '(): loading task_state_config file ' config_file_path]);
    fprintf('\nUsing task state config file: %s\n', FileName);
    c = LoadValidateConfigFile(config_file_path, {['task_state_config.' 'target_configurations_file,' ...
                                                                        'use_denso,', ...
                                                                        'state_names,' ...
                                                                        'skip_state,' ...
                                                                        'trial_begins,' ...
                                                                        'trial_complete,' ...
                                                                        'task_end_state,' ...
                                                                        'manual_proceed,' ...
                                                                        'manual_cancel,' ...
                                                                        'time_penalty,' ...
                                                                        'timeout,' ...
                                                                        'timeout_range_percent,' ...
                                                                        'timed_out_conseq,' ...
                                                                        'dim_domains,' ...
                                                                        'auto_command_fraction,' ...
                                                                        'vf_orth_impedance'] });


    % repmat the rows of start_collection and end_collection so we don't need to
    % have so many rows in config file - they're always kept the same anyway
    max_control_dims = length(XM.config.robot_control_dims);

    if isfield(c.task_state_config, 'use_for_calibration')
        num_use_for_calibration_rows = size(c.task_state_config.use_for_calibration, 1);
        if num_use_for_calibration_rows == 1
            c.task_state_config.use_for_calibration = repmat(c.task_state_config.use_for_calibration, [max_control_dims, 1]);
        end
    end

    row_cnt = length(c.task_state_config.dim_domains);
    max_col_cnt = length(c.task_state_config.state_names);

    auto_command_fraction = ones(max_control_dims, max_col_cnt);
    for r = 1 : row_cnt
        idx = c.task_state_config.dim_domains{r};
        if (ischar(idx)), idx = str2num(idx); end
        auto_command_fraction(idx, :) = repmat(c.task_state_config.auto_command_fraction(r, :), length(idx) ,1);
    end
    c.task_state_config.auto_command_fraction = auto_command_fraction;

    vf_orth_impedance = zeros(max_control_dims, max_col_cnt);
    for r = 1 : row_cnt
        idx = c.task_state_config.dim_domains{r};
        if (ischar(idx)), idx = str2num(idx); end
        vf_orth_impedance(idx, :) = repmat(c.task_state_config.vf_orth_impedance(r, :), length(idx) ,1);
    end
    c.task_state_config.vf_orth_impedance = vf_orth_impedance;

    XM.config.task_state_config = c.task_state_config;

    
    % --- check goto's
    if isfield(XM.config.task_state_config, 'goto')
        fields = fieldnames(XM.config.task_state_config.goto);
        
        for f = 1 : length(fields)
            field = fields{f};
            
            if strcmpi(field, 's') || strcmpi(field, 'f')
                cols = XM.config.task_state_config.goto.(field);
                for k = 1 : length(cols)
                    col = cols{k};
                    n_col = str2num(col);
                    if ~isempty(n_col)
                        if (n_col<1) || (n_col > length(XM.config.task_state_config.state_names))
                            error(['ERROR: In file "' FileName '", invalid "goto" field value: ' col ...
                                    ' (should be "-" or 1 to ' num2str(length(XM.config.task_state_config.state_names)) ')']);
                        end
                    else
                        if ~strcmpi(col, '-')
                            error(['ERROR: In file "' FileName '", invalid "goto" field value: ' col ...
                                   ' (should be "-" or 1 to ' num2str(length(XM.config.task_state_config.state_names)) ')']);
                        end
                    end
                end
            else
                error(['ERROR: In file "' FileName '", invalid "goto" field name: ' field ' (can only be "f" or "s")']);
            end
        end
    end

    if (XM.config.task_state_config.use_denso == 1)
        if ~isfield(XM.config.task_state_config, 'present_target')
            error(['ERROR: In file "' FileName '", missing "present_target" field']);
        end
    end
    
    
    % --- Load target_configurations file
    tgt_cfg_file = XM.config.task_state_config.target_configurations_file;
    fprintf(1, 'Using target config file: %s\n', tgt_cfg_file);
    config_file_path = [XM.config_files_dir '/' tgt_cfg_file];
    VerifyFileExists(config_file_path);
    fields_to_check = {};
    if (XM.config.task_state_config.use_denso == 1)
        fields_to_check = {'target_configurations.combos,denso_away_moveID'};
    end
    c = LoadValidateConfigFile(config_file_path, fields_to_check);

    % Check reach_target configs
    if isfield(XM.config.task_state_config, 'reach_target')
        reach_targets = unique(XM.config.task_state_config.reach_target);
        reach_targets(~cellfun(@isempty,strfind(reach_targets, '-'))) = [];
        for t = 1 : length(reach_targets)
            tgt = reach_targets{t};
            tgt_cfg = sprintf('config_%s', tgt);
            if ( size(c.target_configurations.(tgt_cfg).targets, 1) > 1)
                if ~isfield(c.target_configurations.combos, tgt)
                    error(['ERROR: Missing "' tgt '" field in target_configurations.combos']);
                end

                % Check combo indexes
                ids = unique(c.target_configurations.combos.(tgt));
                if (min(ids) < 1) || (max(ids) > size(c.target_configurations.(tgt_cfg).targets, 1))
                    error(['ERROR: Invalid index fount at "' tgt '" field in c.target_configurations.combos']);
                end
            end
        end
    end

    if isfield(XM.config.task_state_config, 'hand_target')
        if ~isfield(c.target_configurations.combos, 'tool')
            error(['ERROR: Missing "tool" field in target_configurations.combos']);
        end
    end
    
    if isfield(c.target_configurations.combos, 'tool')
        if ~isfield(XM.config.task_state_config, 'hand_target')
            error(['ERROR: In file "' FileName '", missing "hand_target" field']);
        end
    end

    % Check present_target configs
    if (XM.config.task_state_config.use_denso == 1)
        present_targets = unique(XM.config.task_state_config.present_target);
        present_targets(strcmp(present_targets, '-')) = [];
        present_targets(strcmpi(present_targets, 'wiggle')) = [];
        for t = 1 : length(present_targets)
            tgt = present_targets{t};
            tgt_cfg = sprintf('config_%s', tgt);
            if ( length(c.target_configurations.(tgt_cfg).target_denso_moveIDs) > 1)
                if ~isfield(c.target_configurations.combos, tgt)
                    error(['ERROR: Missing "' tgt '" field in target_configurations.combos']);
                end

                % Check combo indexes
                ids = unique(c.target_configurations.combos.(tgt));
                if (min(ids) < 1) || (max(ids) > length(c.target_configurations.(tgt_cfg).target_denso_moveIDs))
                    error(['ERROR: Invalid index fount at "' tgt '" field in c.target_configurations.combos']);
                end
            end
        end


        % Check tool configs
        if isfield(c.target_configurations.combos, 'tool')
            tool_ids = unique(c.target_configurations.combos.tool);
            present_targets = unique(XM.config.task_state_config.present_target);
            check_wiggle_params = false;
            if any(strcmpi(present_targets, 'wiggle'))
                check_wiggle_params = true;
            end

            for t = 1 : length(tool_ids)
                tool_id = tool_ids(t);
                tool_cfg = sprintf('config_tool_%d', tool_id);

                if ~isfield(c.target_configurations, tool_cfg)
                    error(['ERROR: In file "' tgt_cfg_file '" ' tool_cfg ' is missing']);
                end

                if ~isfield(c.target_configurations.(tool_cfg), 'dimensions')
                    error(['ERROR: In file "' tgt_cfg_file '" ' tool_cfg ' is missing "dimensions" field']);
                end

                if check_wiggle_params
                    if ~isfield(c.target_configurations.(tool_cfg), 'wiggle_amplitude')
                        error(['ERROR: In file "' tgt_cfg_file '" ' tool_cfg ' is missing "wiggle_amplitude" field']);
                    else
                        if (length(c.target_configurations.(tool_cfg).wiggle_amplitude) == 3)
                            if any(abs(c.target_configurations.(tool_cfg).wiggle_amplitude) > 30)
                                error(['ERROR: In file "' tgt_cfg_file '" ' tool_cfg '.wiggle_amplitude: Entries can''t be larger than 30']);
                            end
                        else
                            error(['ERROR: In file "' tgt_cfg_file '" ' tool_cfg '.wiggle_amplitude: Should have exactly 3 entries']);
                        end
                    end

                    if ~isfield(c.target_configurations.(tool_cfg), 'wiggle_sequence')
                        error(['ERROR: In file "' tgt_cfg_file '" ' tool_cfg ' is missing "wiggle_sequence" field']);
                    else
                        if (length(c.target_configurations.(tool_cfg).wiggle_sequence) <= 8)
                            if any(abs(c.target_configurations.(tool_cfg).wiggle_sequence) > 3)
                                error(['ERROR: In file "' tgt_cfg_file '" ' tool_cfg '.wiggle_sequence: Entries can''t be larger than 3']);
                            end

                            if any(abs(c.target_configurations.(tool_cfg).wiggle_sequence) < 1)
                                error(['ERROR: In file "' tgt_cfg_file '" ' tool_cfg '.wiggle_sequence: Entries can''t be less than 1']);
                            end
                        else
                            error(['ERROR: In file "' tgt_cfg_file '" ' tool_cfg '.wiggle_amplitude can have no more than 8 entries']);
                        end
                    end

                    if ~isfield(c.target_configurations.(tool_cfg), 'wiggle_num_cycles')
                        error(['ERROR: In file "' tgt_cfg_file '" ' tool_cfg ' is missing "wiggle_num_cycles" field']);
                    else
                        num_cycles = c.target_configurations.(tool_cfg).wiggle_num_cycles;
                        if (length(num_cycles) == 1)
                            if (num_cycles < 1) || (num_cycles > 5)
                                error(['ERROR: In file "' tgt_cfg_file '" ' tool_cfg '.wiggle_num_cycles should be positive and no larger than 5']);
                            end
                        else
                            error(['ERROR: In file "' tgt_cfg_file '" ' tool_cfg '.wiggle_num_cycles should have exactly 1 entry']);
                        end
                    end
                end
            end
        end
    end


    XM.config.task_state_config.target_configurations = c.target_configurations;


