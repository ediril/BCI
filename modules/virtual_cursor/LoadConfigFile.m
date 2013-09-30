function config = LoadConfigFile( filename)

%
% Load config settings
%
    c = LoadValidateConfigFile( filename, []);
    config = c.config;
