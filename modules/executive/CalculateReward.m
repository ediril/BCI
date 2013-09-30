%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [amount, valid] = CalculateReward(level)
    
    valid = true;
    if ischar(level)
        if ~isempty(regexp(level, 'e\d+', 'match'))
            amount = strrep(level, 'e', '');
            amount = exprnd(str2double(amount));
        else
            amount = str2num(level);
            if isempty(amount)
                amount = 0;
                valid = false;
            end
        end
    else
        amount = level;
    end    