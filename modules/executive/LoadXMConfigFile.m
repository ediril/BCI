function LoadXMConfigFile( filename)
%   Loads the main XM config file and all sub config files   
%   Should only be called from SetupSession() !!
    
    global XM;
    
%    DisplayMessageToUser( ['Loading main config file for subject ' XM.subject_name]);

    %--- Load main config file
    % Load config file data into a struct: XM config file has a struct called
    % 'config' which includes all the configuration vars
%    DisplayMessageToUser( ['Loading configuration file (' filename')']);
    VerifyFileExists(filename);
    c = LoadValidateConfigFile(filename, {['config.' 'use_controller,' ...
                                                     'enable_denso,' ...			   
                                                     'denso_speed,' ...				   
                                                     'num_reps,' ...                
                                                     'do_video,' ...					
                                                     'do_tool_change,' ...             
                                                     'max_num_tries_per_target,' ...   
                                                     'max_num_tries_per_start_loc,' ...
                                                     'task_state_config_files,' ...
                                                     'task_state_config_schedule,' ...  
                                                     'EM_used_dimensions,' ...
                                                     'robot_control_dims,' ...
                                                     'robot_control_mode,' ...
                                                     'camera_ip,' ...		
                                                     'camera_port'] });		
    
	
    % Go over the fields one by one and make sure the file has all the required fields
    f = fieldnames( XM.config);
    for i = 1 : length( f)
        % iterate to check that all needed fields are present
        fieldname = f{i};
        switch( fieldname)
            case {'target_configurations','tool_change_config', 'task_state_config'}
                % Special fields will be handled separately below
            otherwise
                if( ~isfield( c.config, fieldname))
                    error( ['Field name "' fieldname '" does not exist in config file']);
                end
        end
    end
    
    f = fieldnames( c.config);
    for i = 1 : length( f)
        fieldname = f{i};
        XM.config.(fieldname) = c.config.(fieldname);
    end
    
    %DisplayMessageToUser( ['Main config file loaded successfully']);

    % Run sanity checks on the values in XM.config.task_state_config_files & task_state_config_schedule
    num_ts_file_names     = length(XM.config.task_state_config_files);
    num_ts_schedule_items = length(XM.config.task_state_config_schedule);
    if(num_ts_schedule_items ~= num_ts_file_names)
        error(['XM config file has ' num2str(num_ts_schedule_items)...
               ' items in XM.config.task_state_config_schedule, but ' num2str(num_ts_file_names) ' items in XM.config.task_state_config_files']);
    end
    if(min(diff(XM.config.task_state_config_schedule)) < 1)
        error(['Items in XM.config.task_state_config_schedule must be in increasing order']);
    end
    if(XM.config.task_state_config_schedule(1) ~= 1)
        error(['The first rep number in XM.config.task_state_config_schedule needs to be 1']);
    end
    if( ~isfield( XM.config, 'use_controller'))
        XM.config.use_controller = 0;
    end     
    if( isfield( XM.config, 'alternate_occurrence_freq'))
        if (XM.config.alternate_occurrence_freq > 1 || XM.config.alternate_occurrence_freq < 0)
            error('XM.config.alternate_occurrence_freq cannot be greater than 1');
        end
        if (isfield( XM.config, 'alternate_state_config_files') && isfield( XM.config, 'alternate_state_config_freq'))
            num_asc_files = length(XM.config.alternate_state_config_files);
            num_asc_freqs = length(XM.config.alternate_state_config_freq);
            if(num_asc_freqs ~= num_asc_files)
                error(['XM config file has ' num2str(num_asc_freqs)...
                       ' items in XM.config.alternate_state_config_freq, but ' num2str(num_asc_files) ' items in XM.config.alternate_state_config_files']);
            end
        
            total = sum(XM.config.alternate_state_config_freq);
            if (total ~= 1)
                error('XM.config.alternate_state_config_freq entries should sum up to 1');
            end
        else
            error('XM.config.alternate_occurrence_freq option requires alternate_state_config_freq and alternate_state_config_files fields as well');
        end
    end
        
    