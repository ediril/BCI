function Log = AlignSampledData( Log)
% AlignSampledData  Takes DK message logs and pulls out aligned data.
% 
%     Log = AlignSampledData(Log)
%
% AlignSampledData is called by LoadQLSessionData and does not need to be
% invoked from the command line.
% 
% Original help text:
% Takes DK message logs and pulls out aligned data. I.e. finds all 30 msec
% sampled data and aligns them by sample number. Data is aligned by
% matching everything to the greatest range of samples that exist across
% all message types. For any one message type that does not have all 
% samples in the total range, missing samples at the beginning, middle or 
% end are filled with NaN-s for floating point data types and zeros for
% integer types. This function only modifies those fields that contain
% sampled data. Other fields are left untouched and are copied to the
% output. One new top-level field, ValidSampleMask, is created to indicate
% for each message type, what samples are actually valid.

    MessageTypes = fieldnames( Log.Data);

    % Get first and last sample number across all messages, get some summary stats and do sanity checking
    % on messages that contain sampled data.
    fprintf( '                                  FirstSN..LastSN NumRepeats NumOutOfOrder NumGaps GapLengths\n');
    SampledTypes = {};
    FirstSNos = [];
    LastSNos = [];
    for i = 1 : length( MessageTypes)
        MessageType = MessageTypes{i};
        MessageData = Log.Data.(MessageType);
        % Check whether it is sampled data by checking for the existence of a
        % sample header
        if( isfield( MessageData, 'sample_header'))
            SampleNos = MessageData.sample_header.SerialNo;
            if( SampleNos(1) <= 0), continue; end % Ignore data that have negative or zero SampleNos because they are not valid
            first_sample_no = SampleNos(1);
            last_sample_no = SampleNos(end);
            DeltaSNos = diff( SampleNos);
            gaps = DeltaSNos( DeltaSNos > 1);
            num_gaps = length( gaps);
            num_repeats = length( find( DeltaSNos == 0));
            num_out_of_order = length( find( DeltaSNos < 0));
            fprintf( '%32s: %7i..%6i %10i %13i %7i %20s\n', MessageType, first_sample_no, last_sample_no, num_repeats, num_out_of_order, num_gaps, ['[' num2str(gaps) ']']);
            SampledTypes(end+1,1) = {MessageType};
            FirstSNos(end+1) = first_sample_no;
            LastSNos(end+1) = last_sample_no;
        end
    end
    if( ~isempty( SampledTypes))
        FirstSNos = unique( FirstSNos);
        LastSNos = unique( LastSNos);
        FirstSNo = FirstSNos(1);
        LastSNo = LastSNos(end);
        SNoTemplate = FirstSNo : LastSNo;
    end
    
    % Create output data matrices where all data have the same number of
    % samples and the samples are aligned, i.e. i-th column in one matrix
    % refers to the same sample number as i-th column is any other matrix
    ValidSampleMask = [];
    for i = 1 : length( SampledTypes)
        MessageType = SampledTypes{i};
        % Create mask of valid samples for this message type aligned by sample serial number
        SN = Log.Data.(MessageType).sample_header.SerialNo;
        [CommonSampleNumbers, ValidSampleIdx_InAlignedData, ValidSampleIdx_InOriginalData] = intersect( SNoTemplate, SN);
        ValidSampleMask_InAlignedData = false( size( SNoTemplate));
        ValidSampleMask_InAlignedData(ValidSampleIdx_InAlignedData) = true;
        ValidSampleMask_InOriginalData = false( size( SampleNos));
        ValidSampleMask_InOriginalData(ValidSampleIdx_InOriginalData) = true;
        % Align data, header and other fields for this message type based
        % on the mask
        TopLevelFieldNames = fieldnames( Log);
        for t = 1 : length( TopLevelFieldNames)
            % For each top-level field, align all the message data inside of it
            TopLevelFieldName = TopLevelFieldNames{t};
            MessageData = Log.(TopLevelFieldName).(MessageType);
            AlignedMessageData = AlignField( MessageData, ValidSampleMask_InAlignedData, ValidSampleMask_InOriginalData);
            Log.(TopLevelFieldName).(MessageType) = AlignedMessageData;
        end
        % Store the mask of valid samples for the output structure
        ValidSampleMask.(MessageType) = ValidSampleMask_InAlignedData;
    end
    Log.ValidSampleMask = ValidSampleMask;
    Log.SampleNos = SNoTemplate;
    
    
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Take the fields in the log for a particular sampled data message type, and 
% output the same fields so that they will be aligned with samples from
% other message types
function AlignedField = AlignField( FieldData, ValidSampleMask_InAlignedData, ValidSampleMask_InOriginalData)

    FieldType = class( FieldData);
    switch( FieldType)
        case 'struct'
            % If the data is nested, then iterate fields and go recursive to
            % align data in each field
            AlignedField = [];
            SubFieldNames = fieldnames( FieldData);
            for i = 1 : length( SubFieldNames)
                SubFieldName = SubFieldNames{i};
                SubFieldData = FieldData.(SubFieldName);
                AlignedSubField = AlignField( SubFieldData, ValidSampleMask_InAlignedData, ValidSampleMask_InOriginalData);
                AlignedField.(SubFieldName) = AlignedSubField;
            end
        otherwise
            % If it's regular data then go ahead and to the alignment.
            % Create a data template of NaN-s
            NumRows = size( FieldData, 1);
            DefaultValue = cast( nan, FieldType);
            AlignedField = repmat( DefaultValue, [NumRows length( ValidSampleMask_InAlignedData)]);
            % Over-write the template with real data at columns
            % where samples exist
            AlignedField(:,ValidSampleMask_InAlignedData) = FieldData(:,ValidSampleMask_InOriginalData);
    end
    