function [Data, IncrState] = Intermediate2Formatted_v2( iData, IncrState)

% [Data, IncrState] = Intermediate2Formatted( iData, IncrState)
% 
% Takes data in the Intermediate format (iData, as output by
% Raw2Intermediate and turns it into the Formatted data format that
% is supposed to serve as the common format for analysis in the RP3
% project

    if ~exist('IncrState', 'var') || isempty(IncrState)
        IncrState = struct( 'OrphanSamples', {{}}, ...
                            'FDataEnd', {{}} );
    end

    %
    % Init arrays that continue from previous iteration with proper "start data"
    % (If none, then init them to "zero" as speficied in the call
    %
    INIT_trial_no_per_bin = InitStartData(IncrState, 'TrialNo', []);
    INIT_task_state_codes = InitStartData(IncrState, 'TaskStateCodes.Values', 0);
    INIT_success = InitStartData(IncrState, 'OutcomeMasks.Success', false);
    INIT_position_target = InitStartData(IncrState, 'Position.target', []);
    INIT_active_chan_mask = InitStartData(IncrState, 'ActiveChannelMask', 0);
    

    %
    % Merge in orphan samples (if any) from previous run
    %
    [iData.QL, IncrState] = MergeOrphanSamples(iData.QL, IncrState);

    
    % Align sampled data so the i-th column in one matrix corresponds to the
    % same sample number as the i-th column in any other matrix
    iData.QL = AlignSampledData(iData.QL);

    %
    % Remove current orphan samples (if any) and keep them for next run
    % (affects only data with valid sample_header)
    [iData.QL, IncrState] = RemoveOrphanSamples(iData.QL, IncrState);
 
    %
    % Create some short-hand variables
    %
    D = iData.QL.Data;
    R = iData.RTMA;
    num_samples = length( iData.QL.SampleNos);
    
    %
    % Reduce spike counts to only the active channels to save
    % storage space
    %
    all_counts  = D.SPM_SPIKECOUNT.counts;
    active_chan_mask = any( all_counts, 2) | INIT_active_chan_mask;
    active_counts = all_counts(active_chan_mask,:);

    % 
    % Create trial number and start number vectors
    %
    trial_no_indices = GetEventIndices( iData.QL, ...
        'TRIAL_CONFIG', 'SAMPLE_GENERATED');
    trial_no_per_bin = FillValueAtInds(D.TRIAL_CONFIG.trial_no, ...
        trial_no_indices, num_samples, INIT_trial_no_per_bin);
    start_no = 1:size(trial_no_indices, 2);
    start_no_per_bin = FillValueAtInds(start_no, ...
        trial_no_indices, num_samples);
    block_no_per_bin = FillValueAtInds(D.TRIAL_CONFIG.rep_no, ...
        trial_no_indices, num_samples);
    
    
    % useful index into Valid Bins
    % i.e. ones after beginning of first trial
    vb = start_no_per_bin > 0;
    
    %
    % Create task state masks
    %
    if( isfield( D, 'TRIAL_EVENT'))
        % If data is in Pre-July 2011 format, then we look for a
        % TRIAL_EVENT messages to find task state transitions
        task_state_begin_codes = D.TRIAL_EVENT.event_code;
        task_state_code_defs = CopyStructFields( R.defines, 'TE_');
		% Rename task state fields to match the RP3 data format definition
		task_state_code_defs = rename_task_states( task_state_code_defs);
        task_state_begin_indices = GetEventIndices( iData.QL, ...
            'TRIAL_EVENT', 'SAMPLE_GENERATED');
        task_state_tags = fieldnames( task_state_code_defs);
    else
        % Otherwise we look for the TASK_STATE_CONFIG message
        task_state_begin_tags = D.TASK_STATE_CONFIG.tag;
        task_state_tags = unique( task_state_begin_tags);
        % task_state_begin_codes = ...convert tags to codes
        % task_state_code_defs = ...create struct with field names as
        % tags, and values as codes
        % ... TO BE COMPLETED
    end
	
    % Convert array of task state begin codes to continuous vector
    % of task state codes
    bad_begin_idx_mask = isnan(task_state_begin_indices);
    task_state_codes = double(INIT_task_state_codes) * ones( 1, num_samples);
    task_state_begin_codes(bad_begin_idx_mask) = [];
    task_state_begin_indices(bad_begin_idx_mask) = [];
    task_state_begin_indices(end+1) = num_samples+1;
    for i = 1 : length( task_state_begin_codes)
        code = task_state_begin_codes(i);
        begin_idx = task_state_begin_indices(i);
        end_idx = task_state_begin_indices(i+1)-1;
        task_state_codes(begin_idx:end_idx) = code;
    end
    
	% Create the masks
    task_state_masks = struct();
    for i = 1 : length( task_state_tags)
        tag = task_state_tags{i};
        code = task_state_code_defs.(tag);
        task_state_masks.(tag) = task_state_codes == code;
    end
    
    %
    % Create trial outcome masks - currently options are:
    %   success, failed, did not start
    %
    % success is specified directly in messages, per start
    success = INIT_success .* true(1, num_samples);
    success(vb) = ...
        D.TRIAL_STATUS.success(start_no_per_bin(vb));
    
    % failure is given by success == 0 ...
    %    AND next_trial_number == trial_number + 1
    failure = false(1, num_samples);
    % roll trial_no to get next_trial_no
    next_trial_no = [D.TRIAL_CONFIG.trial_no(2:end) ...
        D.TRIAL_CONFIG.trial_no(1)];
    next_trial_no_per_bin = FillValueAtInds(next_trial_no, trial_no_indices, ...
        num_samples);
    failure(vb) = ~success(vb) & ...
        (next_trial_no_per_bin(vb) == trial_no_per_bin(vb) + 1);

    %   did not start = neither of the other two
    dns = ~success & ~failure;
    
    %
    % Get kinematic data
    %
    position = struct();
    velocity = struct();
    if( isfield( D, 'EM_MOVEMENT_COMMAND'))
        position.Decoded = D.EM_MOVEMENT_COMMAND.pos;
        velocity.Decoded = D.EM_MOVEMENT_COMMAND.vel;
    end
    if( isfield( D, 'ROBOT_CONTROL_SPACE_ACTUAL_STATE'))
        position.Actual = D.ROBOT_CONTROL_SPACE_ACTUAL_STATE.pos;
        velocity.Actual = D.ROBOT_CONTROL_SPACE_ACTUAL_STATE.vel;
        position.ActualCoriMatrix = D.ROBOT_CONTROL_SPACE_ACTUAL_STATE.CoriMatrix
    end
    if( isfield( D, 'FINAL_MOVEMENT_COMMAND'))
        velocity.Control = D.FINAL_MOVEMENT_COMMAND.vel;
    else
        if( isfield( D, 'COMPOSITE_MOVEMENT_COMMAND'))
            velocity.Control = D.COMPOSITE_MOVEMENT_COMMAND.vel;
        end
    end
    if( isfield( D, 'ROBOT_CONTROL_CONFIG'))
        target_inds = GetEventIndices( iData.QL, ...
            'ROBOT_CONTROL_CONFIG', 'SAMPLE_GENERATED');
        position.target = FillValueAtInds(D.ROBOT_CONTROL_CONFIG.target, ...
            target_inds, num_samples, INIT_position_target);
    end
    if( isfield( D, 'PLANNER_STATE'))
        position.PlannerTarget = D.PLANNER_STATE.targetPos
    end
        
    
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    %
    % Create output struct
    %
    Data = struct(...
        'TrialNo', trial_no_per_bin, ...
        'BlockNo', block_no_per_bin, ...
        'ActiveChannelMask', active_chan_mask, ...
        'TaskStateMasks', task_state_masks, ...
        'TaskStateCodes', struct('Values', task_state_codes, ...
                                 'Definitions', task_state_code_defs), ...
        'OutcomeMasks', struct('Success', success, ...
                               'Failure', failure, ...
                               'DidNotStart', dns),...
        'Position', position, ...
        'Velocity', velocity, ...
        'SpikeCount', active_counts);
	
    
    %
    % save the end bits of Data (above) for initializing the next iteration
    %
    IncrState.FDataEnd = GetEndData(Data);
    
    
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%	
function task_state_code_defs = rename_task_states( task_state_code_defs)

    % BeginTrial = TE_BeginTrial
    % Present    = TE_Presentation
	% Reach      = TE_Reaching
	% Preshape   = TE_HandOpening
	% Approach   = TE_Homing | TE_PreGrasp
	% Grasp      = TE_Grippy
	% Hold       = TE_DoorHolding
	% Release    = TE_KnobReleasing
	% Depart     = NULL
	% Return     = TE_ReturningToPad | TE_ReleaseHand
	% InterTrial = TE_InterTrial | TE_Success | TE_Failure
