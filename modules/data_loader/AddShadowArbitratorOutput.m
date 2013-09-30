function iF = AddShadowArbitratorOutput(iD, iF, save_to_file)

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
    
    % Insert SG message to the beginning to make sure there is at least one
    % SG message before all other messages
    iD.QL = InsertSampleGeneratedMsg(iD.QL);
                    
    % Align sampled data so the i-th column in one matrix corresponds to the
    % same sample number as the i-th column in any other matrix
    iD.QL = AlignSampledData(iD.QL, IncrState);

    % Remove current orphan samples (if any) and keep them for next run
    % (affects only data with valid sample_header)
    trial_end_task_id = find(iD.XM.config.task_state_config.task_end_state{1}==1);
    [iD.QL, IncrState] = RemoveOrphanSamples(iD.QL, IncrState, trial_end_task_id);

    iF.Shadow = struct();
    iF.Shadow.Planner = iD.QL.Data.PLANNER_MOVEMENT_COMMAND.vel;
    iF.Shadow.Fixtured = iD.QL.Data.FIXTURED_MOVEMENT_COMMAND.vel;
    iF.Shadow.Composite = iD.QL.Data.COMPOSITE_MOVEMENT_COMMAND.vel;
    U = iF.Shadow.Fixtured; %extrinsic_cmd;
    D = iF.Shadow.Planner; %config.intrinsic_cmd;
    C = 1 - iF.TaskConfigVals.AutoControl;
    iF.Shadow.ShadowComposite = C.*U + (1-C).*D;
        
    if exist('save_to_file', 'var')
       Data = iF;
       save(save_to_file, 'Data');
    end    
    