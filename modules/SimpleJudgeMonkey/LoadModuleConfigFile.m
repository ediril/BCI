function config = LoadModuleConfigFile( filename)

%
% Load config settings
%
    try
        % Load the config file
        config = LoadValidateConfigFile( filename, []);

    catch ME
        fprintf('\n>>> Failed to load because of the following error(s) in config file: %s\n', filename);
        fprintf('%s\n', ME.message);
        config = [];
    end

