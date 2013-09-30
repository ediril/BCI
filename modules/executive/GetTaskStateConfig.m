function [config] = GetTaskStateConfig( index)
% [config] = GetTaskStateConfig( StateName)
% Returns a structure containing values from XM.config.task_state_config
% for the given state

global XM;

% verify we were given a valid state name
%%%state_idx = ValidateStateName(StateName);
NumStates = length( XM.config.task_state_config.state_names);
CONFIG = XM.config.task_state_config;
config = GetValuesForCurrentStateFromFields( CONFIG, index, NumStates);


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function config = GetValuesForCurrentStateFromFields( CONFIG, state_idx, NumStates)

    config = [];
    f = fieldnames( CONFIG);
    for i = 1 : length( f)
        fieldname = f{i};
        fielddata = CONFIG.(fieldname);

        if strcmpi(fieldname, 'target_configurations')
            config.(fieldname) = fielddata;
            continue;
        end
        
        
        % break up cell array of strings
        if (strcmp(class(fielddata),'cell') && size(fielddata, 1)>1)
            newdata = {};
            save_new_fielddata = true;
            for r = 1 : size(fielddata, 1)
                data = fielddata{r};
                if (~strcmp(class(data),'cell')), data = num2str(data); end
                list = regexp( data, '\S+', 'match');
                if (length(list) ~= NumStates)
                    % don't try to break up strings that are not "one data per task state"
                    save_new_fielddata = false;
                    break;  
                end
                newdata = vertcat(newdata, list);
            end
            if (save_new_fielddata),  fielddata = newdata;  end
        end

        switch( class( fielddata))
            case 'struct'
                config.(fieldname) = GetValuesForCurrentStateFromFields( fielddata, state_idx, NumStates);
            case 'cell'
                if( size( fielddata, 2) == NumStates)
                    if ( size(fielddata, 1) > 1)
                        config.(fieldname) = fielddata(:,state_idx);
                    else
                        config.(fieldname) = fielddata{:,state_idx};
                    end
                else
                    config.(fieldname) = fielddata;
                end

            case 'char'
                config.(fieldname) = fielddata;
                
            otherwise
                if( size( fielddata, 2) == NumStates)
                    % If it is a field that has one element per task state, then pick the value for the specified task state
                    config.(fieldname) = fielddata(:,state_idx);
                else
                    % If it is not one per task state, assign the whole field
                    config.(fieldname) = fielddata;
                end
        end
    end
    