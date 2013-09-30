function timeout = CalcTaskStateTimeout( task_state_config)

    global XM;

    timeout = task_state_config.timeout;
    TOMax = timeout * (1 + (task_state_config.timeout_range_percent / 100));
    
    StateName = task_state_config.state_names;
   
    % Pick timeout value randomly between min and max
    if (timeout ~= TOMax),  timeout = random( 'Uniform', timeout, TOMax);   end
    
%    DisplayMessageToUser( [StateName ': a timeout of ' num2str(timeout) 'ms has been set']);
	