function EM = LoadEMConfigFile(EM, filename)

%
% Load config settings and add them to the config structure
%

    done = false;
    while ~done
        try
            % Load the config file
            if ischar(filename)
                c = LoadValidateConfigFile( filename, []);
            else
                c = filename;
            end

            EM.config = c.config;
            
            if isfield(EM.config, 'verbose')
                EM.config.decoder.options.verbose = EM.config.verbose;
            else
                EM.config.decoder.options.verbose = 1;
            end    

            EM.config.NumDimensions = length(EM.config.decoder.options.Gain);

            ctrl_dims = EM.config.decoder.options.Gain;
            EM.config.ControlledDims(ctrl_dims ~= 0) = 1;

            if isnumeric( EM.config.measurement.options.Dt)
                EM.config.Dt = config.measurement.options.Dt;
            end        

            EM.Filter = EM.config.measurement.options.FilterCoeffs';

            done = true;
            
        catch ME
            fprintf('\n>>> Please correct the following error(s) in config file: %s\n', filename);
            fprintf('%s\n\nWhen finished, hit ENTER to try reloading\n', ME.message);
            pause;
        end
    end    


