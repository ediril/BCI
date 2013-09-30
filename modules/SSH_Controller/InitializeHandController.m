function c = InitializeHandController( config)

    %
    % Modify/add some config values for hand controller algorithm
    %
    
    % Convert mapper function name to function handle
    config.L2H = struct( ...
        'G', eval(['@' config.low2high_mapper.function_name]), ...
        'config', config.low2high_mapper);
    
    % Set initial position and velocity
    config.initial_pos = zeros( sum( config.low_dof_mask), 1);
    config.initial_vel = zeros( sum( config.low_dof_mask), 1);

    %
    % Initialize the hand controller algorithm named in the config
    %
    c = feval( ['Initialize_' config.algorithm], config);

    c.config = config;
    