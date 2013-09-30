function config = LoadControllerConfigFile( filename)

%
% Load config settings
%

%     done = false;
%     while ~done
%         try
            % Load the config file
            c = LoadValidateConfigFile( filename, []);

            config = c.config;
            config.hand.low_dof_mask = logical( config.hand.low_dof_mask);
                
            config.output_offsets = LoadOutputOffsets();
            
%             done = true;
%             
%         catch ME
%             fprintf('\n>>> Please correct the following error(s) in config file: %s\n', filename);
%             fprintf('%s\n\nWhen finished, hit ENTER to try reloading\n', ME.message);
%             pause;
%         end
%     end    
