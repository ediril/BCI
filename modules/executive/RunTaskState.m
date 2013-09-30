%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Runs the stuff that is common to all task states.
function RunTaskState( task_state_config, target, cori)

    global XM;
    global DF;
   
    % remove extra dims of control for now, not implemented
    target(DF.defines.MAX_CONTROL_DIMS+1:end) = [];
    
    % Get a snapshot of time at the beginning of this task state
    current_state_begin_time = GetAbsTime( );

    state_name = task_state_config.state_names;
    
    if(XM.config.do_video)
	  sstring = ['echo R', num2str(XM.rep_num), 'T', num2str(XM.trial_num), '-acf', ...
                 num2str(task_state_config.auto_command_fraction', '%.5g'), '-vf', num2str(task_state_config.vf_orth_impedance', '%.5g'), '| nc -q 0 ', XM.config.camera_ip, ' ', num2str(XM.config.camera_port)];
    
      if(~isfield(XM.runtime, 'sstring') || ~strcmp(sstring, XM.runtime.sstring));
        system(sstring);
        XM.runtime.sstring = sstring;
      end
    end  
    
    % Send robot control configuration
    SendRobotControlConfig( state_name, current_state_begin_time, task_state_config, target, cori);
    
  %DisplayMessageToUser( ['RunTaskState: <' event_name '> -> [' state_name ']']);
    
