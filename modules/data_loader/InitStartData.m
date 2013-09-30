function InitVal = InitStartData(IncrState, Field, default_empty)

    if isempty(IncrState.FDataEnd)
        InitVal = default_empty;
    else
        Fields = strSplit(Field, '.');
        InitVal = IncrState.FDataEnd;
        for f = 1 : length(Fields)
            if isfield(InitVal, Fields{f})
                InitVal = InitVal.(Fields{f});
            else
                InitVal = default_empty;
                fprintf('>>> "%s" defaulted\n',Field);
                break;
            end
        end
    end
    

