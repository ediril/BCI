function C = InitializeController( ConfigFilename)

    C = struct();
    
    % Load config settings from file
    C.config = LoadControllerConfigFile( ConfigFilename);

    % Initialize Arm controller
    C.arm_controller = InitializeArmController( C.config.arm);

    % Initialize Hand controller
    C.hand_controller = InitializeHandController( C.config.hand);
    
    C.Pf = struct();