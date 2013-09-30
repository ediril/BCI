%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function task_state_config_file_name = GetTaskStateConfigFileName( )
%   task_state_config_file_name = GetTaskStateConfigFileName( )
%   
%   OUTPUT: task_state_config_file_name = file name from XM.config.state_task_config_files
%   
%   Looks in XM.config.task_state_config_schedule and figures out what file
%   name index in XM.config.task_state_config_files should be used
%   Then returns the file name corresponding to that index

    global XM;
    
    indices_in_schedule = find( XM.config.task_state_config_schedule <= XM.rep_num);
    if(isempty(indices_in_schedule))
        caller_name = GetCallerName( );
        error(['->' caller_name '(): task_state_config_schedule does not have an index for the current ']);
    end
    
    index_in_task_state_config_files = indices_in_schedule(end);

    task_state_config_file_name      = XM.config.task_state_config_files{index_in_task_state_config_files};