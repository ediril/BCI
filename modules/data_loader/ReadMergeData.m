function [Data, DL] = ReadMergeData(path, Data, DL)

    [new_idata, r2i] = Raw2Intermediate(path, DL.IncrState_R2I);
    if isempty(new_idata)
        return;
    else
        DL.IncrState_R2I = r2i;
        if isempty(DL.IData)
            DL.IData = new_idata;
        else
            DL.IData = MergeIntermediateData(DL.IData, new_idata);
        end
    end
    
    new_fdata = Intermediate2Formatted(DL.IData);
    if ~isempty(new_fdata)
        Data = new_fdata;
    end
