function state_idx = ValidateStateName( StateName)
% ValidateStateName( StateName)
% Checks if the given StateName is valid. Throws an error if not
% state_idx: the index of the state in the XM.config.task_state_config arrays

global XM;

% verify StateName is a string
if(~ischar(StateName))
	if(isnumeric(StateName))
		StateName = num2str(StateName);
		error(['ValidateStateName: StateName is not a character array: [' StateName ']']);
	else
		error('ValidateStateName: StateName is not a character array, and is not numeric');
	end
end
% verify we were given a valid state name
state_idx = strmatch( StateName, XM.config.task_state_config.state_names, 'exact');
if(isempty(state_idx))
	error(['ValidateStateName(): got invalid state name: ' StateName]);
end
% check for duplicates in the config file
if(length(state_idx) ~= 1)
	error(['ValidateStateName(): same state name (' StateName ') appears twice in the config file under task_state_config.state_names']);
end
