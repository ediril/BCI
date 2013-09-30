function [Log, IncrState] = RemoveOrphanSamples( Log, IncrState)

    % Make a list of message types with fewer samples than others
    MessageTypes = fieldnames(Log.ValidSampleMask);
    LastSN = Log.SampleNos(end);
    OrphanMessageTypes = {};
    LastCommonSN = LastSN;
    
    % find highest common sample no and which message types go beyond it
    for i = 1 : length(MessageTypes)
        MessageType = MessageTypes{i};
        
        CurrSN = max(Log.Data.(MessageType).sample_header.SerialNo);
        if ( CurrSN == LastSN )
            OrphanMessageTypes = [OrphanMessageTypes MessageType];
        else
            if (CurrSN < LastCommonSN)
                LastCommonSN = CurrSN;
            end
        end
    end


    TopLevelFieldNames = fieldnames(Log);

    % remove 'SampleNos' from recurse list 
    TopLevelFieldNames(find(ismember(TopLevelFieldNames, 'SampleNos')==1)) = [];
    
    
    % do we have any orphans among sample data?
    if ( LastCommonSN < LastSN )

        SampleRemoveCount = LastSN - LastCommonSN;

        % update 'SampleNos' to reflect that we removed orphan samples
        idx = find(Log.SampleNos == LastCommonSN);
        Log.SampleNos = Log.SampleNos(:, 1:idx);

        for i = 1 : length(MessageTypes)
            MessageType = MessageTypes{i};
    
            for t = 1 : length(TopLevelFieldNames)
                TopLevelFieldName = TopLevelFieldNames{t};
                MsgData = Log.(TopLevelFieldName).(MessageType);
                [RemainingData, RemovedData] = AdjustField( MsgData, SampleRemoveCount);
                Log.(TopLevelFieldName).(MessageType) = RemainingData;
                
                if ~isempty(strmatch(MessageType, OrphanMessageTypes))
                    IncrState.OrphanSamples.(TopLevelFieldName).(MessageType) = RemovedData;
                end
            end
        end
        
        % remove 'ValidSampleMask', we don't need to keep track of it
        IncrState.OrphanSamples = rmfield(IncrState.OrphanSamples, 'ValidSampleMask');
    end
        
    % find and extract orphans among nonsampled data based on last SAMPLE_GENERATED sequence no
    LastSequenceNo = Log.SequenceNo.SAMPLE_GENERATED(end);
    MessageTypes = fieldnames(Log.Data);
    TopLevelFieldNames(find(ismember(TopLevelFieldNames, 'ValidSampleMask')==1)) = [];
    
    for f = 1 : length(MessageTypes)
        MessageType = MessageTypes{f};
        
        %skip ones that have 'sample_header' field
        %skip ones that have empty data
        if ( isfield(Log.Data.(MessageType), 'sample_header') || ...
             isempty(Log.Data.(MessageType)) )
            continue;
        end
        
        idx = find(Log.SequenceNo.(MessageType) > LastSequenceNo);
        if ~isempty(idx)
            for t = 1 : length(TopLevelFieldNames)
                TopLevelFieldName = TopLevelFieldNames{t};
                MsgData = Log.(TopLevelFieldName).(MessageType);
                SampleRemoveCount = length(idx);
                [RemainingData, RemovedData] = AdjustField(MsgData, SampleRemoveCount);
                Log.(TopLevelFieldName).(MessageType) = RemainingData;
                IncrState.OrphanSamples.(TopLevelFieldName).(MessageType) = RemovedData;
            end
        end
    end
    
    
    
function [AdjustedField, RemovedField] = AdjustField( FieldData, SamplesToRemove)

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
                [AdjustedSubField, RemovedSubField] = AdjustField( SubFieldData, SamplesToRemove);
                AdjustedField.(SubFieldName) = AdjustedSubField;
                RemovedField.(SubFieldName) = RemovedSubField;
            end
        otherwise
            % If it's regular data then go ahead and do the remove. 
            AdjustedField = FieldData(:, 1:end-SamplesToRemove);
            RemovedField = FieldData(:, end-SamplesToRemove+1:end);
    end    
    