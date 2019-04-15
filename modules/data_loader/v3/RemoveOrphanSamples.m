function [Log, IncrState] = RemoveOrphanSamples( Log, IncrState, ETS_id)

    LastSN = Log.SampleNos(end);
    MessageTypes = fieldnames(Log.ValidSampleMask);
    LastCommonSN = LastSN;

    %% do only for incremental data processing
    %if ~isempty(IncrState.LastSampleNo)
        % find highest common sample no and which message types go beyond it
        for i = 1 : length(MessageTypes)
            MessageType = MessageTypes{i};
            CurrSN = max(Log.Data.(MessageType).sample_header.SerialNo);
            if (CurrSN < LastCommonSN)
                LastCommonSN = CurrSN;
            end
        end
    %end
        
    % find where the last whole successful trial ends and cut there
    final_SG_idx = find(Log.Data.SAMPLE_GENERATED.sample_header.SerialNo == LastCommonSN);
    final_SG_seqno = Log.SequenceNo.SAMPLE_GENERATED(final_SG_idx);
    valid_ETS_idx = find( Log.SequenceNo.END_TASK_STATE < final_SG_seqno);
    last_ETS_idx = find( Log.Data.END_TASK_STATE.id(valid_ETS_idx) == ETS_id, 1, 'last');
    if isempty(last_ETS_idx),  Log = [];  return;   end
    last_ETS_seqno = Log.SequenceNo.END_TASK_STATE(last_ETS_idx);
    last_SG_idx = find(Log.SequenceNo.SAMPLE_GENERATED > last_ETS_seqno, 1, 'first');
    LastSequenceNo = Log.SequenceNo.SAMPLE_GENERATED(last_SG_idx);
    
    % take last_SG_idx-1 because we look for ref indices 'before', so 
    % last_SG_idx needs to be moved to the next iteration to be the first SG ref sample
    LastCommonSN = Log.Data.SAMPLE_GENERATED.sample_header.SerialNo(last_SG_idx-1);

    TopLevelFieldNames = fieldnames(Log);
    % remove 'SampleNos' from recurse list, don't need it
    TopLevelFieldNames(find(ismember(TopLevelFieldNames, 'SampleNos')==1)) = [];

    % do we have any orphans among sample data?
    if ( LastCommonSN < LastSN )
        SampleRemoveCount = LastSN - LastCommonSN;
        for i = 1 : length(MessageTypes)
            MessageType = MessageTypes{i};
            endvalidmask = Log.ValidSampleMask.(MessageType)(end-SampleRemoveCount+1:end);
            for t = 1 : length(TopLevelFieldNames)
                TopLevelFieldName = TopLevelFieldNames{t};
                MsgData = Log.(TopLevelFieldName).(MessageType);
                [RemainingData, RemovedData] = AdjustField( MsgData, SampleRemoveCount, endvalidmask);
                Log.(TopLevelFieldName).(MessageType) = RemainingData;
                if ~strcmp(TopLevelFieldName, 'ValidSampleMask')
                    IncrState.OrphanSamples.(TopLevelFieldName).(MessageType) = RemovedData;
                end
            end
        end
        
        % update 'SampleNos' to reflect that we removed orphan samples
        idx = find(Log.SampleNos == LastCommonSN);
        Log.SampleNos = Log.SampleNos(:, 1:idx);
    end
    
    % find and extract orphans among nonsampled data based on last SAMPLE_GENERATED msg
    % 
    % also remove all non-sampled messages that came in before the first SG msg
    % (SAMPLE_GENERATOR probably died and any such trial is useless)
    MessageTypes = fieldnames(Log.Data);
    FirstSequenceNo = Log.SequenceNo.SAMPLE_GENERATED(1);

    % remove 'ValidSampleMask' from recurse list, don't need it here
    TopLevelFieldNames(find(ismember(TopLevelFieldNames, 'ValidSampleMask')==1)) = [];

    
    for f = 1 : length(MessageTypes)
        MessageType = MessageTypes{f};
        
        % skip ones that have 'sample_header' field
        % skip ones that have empty data
        if ( isfield(Log.Data.(MessageType), 'sample_header') || ...
             isempty(Log.Data.(MessageType)) )
            continue;
        end
        
        idx = find(Log.SequenceNo.(MessageType) >= LastSequenceNo);
        if ~isempty(idx)
            SampleRemoveCount = length(idx);
            for t = 1 : length(TopLevelFieldNames)
                TopLevelFieldName = TopLevelFieldNames{t};
                MsgData = Log.(TopLevelFieldName).(MessageType);
                [RemainingData, RemovedData] = AdjustField(MsgData, SampleRemoveCount);
                Log.(TopLevelFieldName).(MessageType) = RemainingData;
                IncrState.OrphanSamples.(TopLevelFieldName).(MessageType) = RemovedData;
            end
        end

        idx = find(Log.SequenceNo.(MessageType) < FirstSequenceNo);
        if ~isempty(idx)
            SampleRemoveCount = length(idx);
            for t = 1 : length(TopLevelFieldNames)
                TopLevelFieldName = TopLevelFieldNames{t};
                MsgData = Log.(TopLevelFieldName).(MessageType);
                [RemainingData, RemovedData] = AdjustField(MsgData, SampleRemoveCount, [], 'front');
                Log.(TopLevelFieldName).(MessageType) = RemainingData;
            end
        end
    end

    
    
function [AdjustedField, RemovedField] = AdjustField( FieldData, RemoveCount, ValidMask, RemoveLocation)

    if ~exist('ValidMask', 'var') || isempty(ValidMask)
        ValidMask = true(1, RemoveCount);
    end
    
    if ~exist('RemoveLocation', 'var')
        RemoveLocation = 'back';
    end
    
    FieldType = class( FieldData);
    switch( FieldType)
        case 'struct'
            % If the data is nested, then iterate fields and go recursive to remove data in each field
            AdjustedField = [];
            RemovedField = [];
            SubFieldNames = fieldnames( FieldData);
            for i = 1 : length( SubFieldNames)
                SubFieldName = SubFieldNames{i};
                SubFieldData = FieldData.(SubFieldName);
                [AdjustedSubField, RemovedSubField] = AdjustField( SubFieldData, RemoveCount, ValidMask, RemoveLocation);
                AdjustedField.(SubFieldName) = AdjustedSubField;
                RemovedField.(SubFieldName) = RemovedSubField;
            end
        otherwise
            % If it's regular data then go ahead and do the remove. 
            if (strcmp(RemoveLocation, 'back'))
                AdjustedField = FieldData(:, 1:end-RemoveCount);
                RemovedField = FieldData(:, end-RemoveCount+1:end);
                RemovedField = RemovedField(:, ValidMask);
            else % front
                AdjustedField = FieldData(:, RemoveCount+1:end);
                RemovedField = FieldData(:, 1:RemoveCount);
                RemovedField = RemovedField(:, ValidMask);
            end
            
    end    
    