function [Data, DL, result] = ReadMergeData_Incr(path, file_read_count, Data, DL)

    global RTMA;

    result = true;

    
    [new_idata, r2i] = Raw2Intermediate_v3_Incr(path, file_read_count, DL.IncrState_R2I);
    if isempty(new_idata)
        result = false;
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
    
