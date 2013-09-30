function [iF] = AddDebug2Formatted(iD, iF, save_to_file)

    srcdir = [getenv('ROBOTSRC') '/data_loader'];
    if ~isfield(iD, 'Version')
        error('ERROR: intermediate data does not have a ''Version'' field');
    end
    if ~strcmp(iD.Version, 'v3')
        error('ERROR: This script works only with v3 data');
    end
    addpath([srcdir '/v3']);

    
    IncrState = struct( 'OrphanSamples', {{}}, ...
                    'LastSampleNo', {{}}, ...
                    'FDataEnd', {{}} );
    
    % Align sampled data so the i-th column in one matrix corresponds to the
    % same sample number as the i-th column in any other matrix
    iD.QL = AlignSampledData(iD.QL, IncrState);

    % Remove current orphan samples (if any) and keep them for next run
    % (affects only data with valid sample_header)
    trial_end_task_id = find(iD.XM.config.task_state_config.task_end_state{1}==1);
    [iD.QL, IncrState] = RemoveOrphanSamples(iD.QL, IncrState, trial_end_task_id);

    iF.Debug = struct();
    
    MsgTypes = fieldnames( iD.QL.Data);
    for m = 1 : length( MsgTypes)
        MsgType = MsgTypes{m};
        MsgData = iD.QL.Data.(MsgType);
        if( isfield( MsgData, 'sample_header'))
            fprintf('%s\n', MsgType);
            iF.Debug.(MsgType) = MsgData;
        end
    end

    if exist('save_to_file', 'var')
       Data = iF;
       save(save_to_file, 'Data');
    end    
    