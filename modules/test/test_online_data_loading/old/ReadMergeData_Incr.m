function [Data, IncrState, result] = ReadMergeData_Incr(path, file_read_count, Data, IncrState)

    global RTMA;

    result = true;
    
    [IData, r2i] = Raw2Intermediate_v3_Incr(path, file_read_count, IncrState.R2I);
    if isempty(IData)
        result = false;
        return;   
    end
    
    [new_data, i2f] = Intermediate2Formatted(IData, IncrState.I2F);
    if isempty(new_data)
        result = false;
        return;   
    end
    
    IncrState.R2I = r2i;
    IncrState.I2F = i2f;
    
    if ~isempty(Data)
        field = 'SpikeCount';
        if ~isfield(Data, field), field='FiringRate'; end
        
        % create rows for newly active channels so they can be merged below
        if isfield(Data, field) && (size(Data.(field),1) ~= size(new_data.(field),1))
            fprintf('\nadjusting %ss...\n', field);
            old_spike_data = uint8(zeros(RTMA.defines.MAX_TOTAL_SPIKE_CHANS,size(Data.(field),2)));
            old_idx = find(Data.ActiveChannelMask==1);
            old_spike_data(old_idx, :) = Data.(field);
            rem_idx = ~new_data.ActiveChannelMask;
            old_spike_data(rem_idx, :) = [];
            Data.(field) = old_spike_data;
        end

        Data.TaskStateCodes.Definitions = [];
        Data.Dt = [];
        Data.Version = '';
        Data.Build = '';
        Data.ConfigName = '';
        Data.ActiveChannelMask = [];
    end

    Data = [Data new_data];
    Data = CatStructFields(Data, 'horizontal', 'merge-fields');
