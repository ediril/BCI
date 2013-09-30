function [Data, IncrState] = Intermediate2Formatted_v3( iData, IncrState)

    dbstop if error;
    
% [Data, IncrState] = Intermediate2Formatted( iData, IncrState)
% 
% Takes data in the Intermediate format (iData, as output by
% Raw2Intermediate and turns it into the Formatted data format that
% is supposed to serve as the common format for analysis in the RP3
% project
    
    
    if ~exist('IncrState', 'var') || isempty(IncrState)
        IncrState = struct( 'OrphanSamples', {{}}, ...
                            'LastSampleNo', {{}}, ...
                            'FDataEnd', {{}} );
    end
    
    version_info = 'v3';

    func_info = mfilename('fullpath');
    [dirname filename] = fileparts(func_info);
    files = dir(dirname);
    ix = find(strcmp({files.name}, [filename '.m'])==1);
    build_info = files(ix).date;

    %
    % Init arrays that continue from previous iteration with proper "start
    % data"
    % (ie, most/all fields that are written to the output struct "Data")
    % If none, then init them to "zero" as speficied in the call
    %
    %INIT_sample_time = InitStartData(IncrState, 'Time', []);
    INIT_trial_no = InitStartData(IncrState, 'TrialNo', []);
    INIT_block_no = InitStartData(IncrState, 'BlockNo', []);
    INIT_tool_no = InitStartData(IncrState, 'ToolNo', []);
    INIT_task_state_codes = InitStartData(IncrState, 'TaskStateCodes.Values', 0);
    %
    INIT_did_not_start = InitStartData(IncrState, 'OutcomeMasks.DidNotStart', false);
    INIT_success = InitStartData(IncrState, 'OutcomeMasks.Success', false);
    INIT_manual_success = InitStartData(IncrState, 'OutcomeMasks.ManualSuccess', false);
    INIT_manual_proceed = InitStartData(IncrState, 'OutcomeMasks.ManualProceed', false);
    INIT_cancelled = InitStartData(IncrState, 'OutcomeMasks.Cancelled', false);
    %INIT_timeout = InitStartData(IncrState, 'OutcomeMasks.Timeout', false);
    INIT_failure = InitStartData(IncrState, 'OutcomeMasks.Failure', false);
    INIT_idle_timeout = InitStartData(IncrState, 'OutcomeMasks.IdleTimeout', false);
    %
    INIT_used4calib = InitStartData(IncrState, 'OtherMasks.UsedForCalib', false);
    INIT_button_sq1 = InitStartData(IncrState, 'OtherMasks.ButtonPress_SQ1 ', false);
    INIT_button_tri1 = InitStartData(IncrState, 'OtherMasks.ButtonPress_TRI1', false);
    INIT_button_cir1 = InitStartData(IncrState, 'OtherMasks.ButtonPress_CIR1', false);
    INIT_button_x1 = InitStartData(IncrState, 'OtherMasks.ButtonPress_X1', false);
    %
    INIT_active_chan_mask = InitStartData(IncrState, 'ActiveChannelMask', 0);
    INIT_position_target = InitStartData(IncrState, 'Position.target', []);
    INIT_position_jang = InitStartData(IncrState, 'Position.JointAngles', []);
    %
    INIT_auto_ctrl = InitStartData(IncrState, 'TaskConfigVals.AutoControl', []);
    INIT_ortho_imp = InitStartData(IncrState, 'TaskConfigVals.OrthoImpedance', []);
    INIT_ctrl_dims = InitStartData(IncrState, 'TaskConfigVals.ControlledDims', []);
    %
    INIT_jthresh = InitStartData(IncrState, 'TaskJudging.Threshold', []);
    %
    INIT_tsom_success = InitStartData(IncrState, 'TaskStateOutcomeMasks.Success', false);
    INIT_tsom_manual = InitStartData(IncrState, 'TaskStateOutcomeMasks.Manual', false);
    INIT_tsom_failure = InitStartData(IncrState, 'TaskStateOutcomeMasks.Failure', false);
    INIT_tsom_cancel = InitStartData(IncrState, 'TaskStateOutcomeMasks.Cancelled', false);
    %
    INIT_idly_state = InitStartData(IncrState, 'IdlyLabelling.state', false);
    INIT_idly_reset = InitStartData(IncrState, 'IdlyLabelling.reset', false);

    %
    % Insert SG message to the beginning to make sure there is at least one
    % SG message before all other messages
    %
    if isempty(IncrState.LastSampleNo)
        iData.QL = InsertSampleGeneratedMsg(iData.QL);
    end    
    
    % if for some reason we didn't get any END_TASK_STATE msgs,
    % postpone processing until we get them
    if ~isfield(iData.QL.Data, 'END_TASK_STATE')
        fprintf('Not enough trial data to process...\n');
        Data = [];
        return;
    end        
    
    %
    % Merge in orphan samples (if any) from previous run
    %
    [iData.QL, IncrState] = MergeOrphanSamples(iData.QL, IncrState);

    %
    % Align sampled data so the i-th column in one matrix corresponds to the
    % same sample number as the i-th column in any other matrix
    %
    iData.QL = AlignSampledData(iData.QL, IncrState);

    %
    % Remove current orphan samples (if any) and keep them for next run
    % (affects only data with valid sample_header)
    num_task_states = length(iData.XM.config.task_state_config.task_end_state{1});
    [iData.QL, IncrState] = RemoveOrphanSamples(iData.QL, IncrState, num_task_states);
   
    if isempty(iData.QL)
        fprintf('Not enough trial data to process...\n');
        Data = [];
        return;
    end


    %
    % Create some short-hand variables
    %
    D = iData.QL.Data;
    R = iData.DF;
    num_samples = length( iData.QL.SampleNos);
    IncrState.LastSampleNo = iData.QL.SampleNos(end);
    fprintf('\n#samples = %d (%d..%d)\n', num_samples, ...
                                          iData.QL.SampleNos(1), ...
                                          iData.QL.SampleNos(end));

    %
    % Reduce spike counts to only the active channels to save
    % storage space
    %
    all_spike_data = [];
    active_chan_mask = [];
    if (isfield(D, 'SPM_SPIKECOUNT'))
        all_spike_data  = D.SPM_SPIKECOUNT.counts;
    elseif( isfield(D, 'SPM_FIRINGRATE'))
        all_spike_data  = D.SPM_FIRINGRATE.rates;
    end
    if ~isempty(all_spike_data)
        active_chan_mask = any( all_spike_data, 2) | INIT_active_chan_mask;
        active_spike_data = all_spike_data(active_chan_mask, :);
    end


    config_dir = iData.XM.config_files_dir{1};
    config_name_idx = strfind(config_dir, 'config');
    config_name_info = config_dir(config_name_idx+7:end);
    
    % --------------------------------------------------------------
    % Create Time, TrialNo, BlockNo
    % --------------------------------------------------------------
    timeline = double(D.SAMPLE_GENERATED.sample_header.SerialNo);
    DeltaTimes = D.SAMPLE_GENERATED.sample_header.DeltaTime(iData.QL.ValidSampleMask.SAMPLE_GENERATED);
    dt_per_bin = DeltaTimes(1);
    time_per_bin = timeline*dt_per_bin;
    
    trial_start_idx = find(D.TASK_STATE_CONFIG.id == 1);
    fprintf('#all_trials: %d\n', length(trial_start_idx));
    
    trial_start_to_SG = GetRelativeRefIndices(iData.QL.SequenceNo.TASK_STATE_CONFIG(trial_start_idx), ... 
                                              iData.QL.SequenceNo.SAMPLE_GENERATED);
    
    tc_idx = 1:length(D.TRIAL_CONFIG.trial_no);
                                         
    % do we have missing trials (due to error etc)?
    if length(trial_start_idx) < length(D.TRIAL_CONFIG.trial_no)
        trial_config_to_SG = GetRelativeRefIndices(iData.QL.SequenceNo.TRIAL_CONFIG, ... 
                                                   iData.QL.SequenceNo.SAMPLE_GENERATED);
        tc_idx = [];
        for k = 1 : length(trial_start_idx)
            seqno_diff = trial_start_to_SG.seqno(k) - trial_config_to_SG.seqno;
            seqno_diff(seqno_diff<0) = nan;
            [val, idx_dist] = min(seqno_diff);
            tc_idx = [tc_idx idx_dist];
        end
    end
                                         
    trial_no_per_bin = FillValueAtInds(D.TRIAL_CONFIG.trial_no(tc_idx), ...
                        trial_start_to_SG.idx, num_samples, INIT_trial_no);
    block_no_per_bin = FillValueAtInds(D.TRIAL_CONFIG.rep_no(tc_idx), ...
                        trial_start_to_SG.idx, num_samples, INIT_block_no);
                    
    % --------------------------------------------------------------
    % Create ToolNo
    % --------------------------------------------------------------
    if (isfield(D, 'CHANGE_TOOL_COMPLETE'))
        tool_change_to_SG = GetRelativeRefIndices(iData.QL.SequenceNo.CHANGE_TOOL_COMPLETE, iData.QL.SequenceNo.SAMPLE_GENERATED);
        tool_change_to_SG_seqno = tool_change_to_SG.seqno(tool_change_to_SG.valid);
        tool_change = GetRelativeRefIndices(tool_change_to_SG_seqno, trial_start_to_SG.seqno, 'after');
        tcc_idx = tool_change.idx(tool_change.valid);
        tool_no_per_bin = FillValueAtInds(D.CHANGE_TOOL_COMPLETE.tool_id, ...
                                          trial_start_to_SG.idx(tcc_idx), num_samples, INIT_tool_no);

        Data.ToolNo = tool_no_per_bin;
    end
    
    % --------------------------------------------------------------
    % Create Tags
    % --------------------------------------------------------------
    Data.Tags = [];
    if isfield(D.TASK_STATE_CONFIG, 'tags')
        if ~isempty(find(D.TASK_STATE_CONFIG.tags>0)) 
            tsc_tags = struct;
            for c = 1 : length(trial_start_idx)
                idx = trial_start_idx(c);
                new_tags = strSplit(deblank(char(iData.QL.Data.TASK_STATE_CONFIG.tags(:,idx))'), ' ');

                for t = 1 : length(new_tags)
                    tag = new_tags{t};
                    if ~isfield(tsc_tags, tag), tsc_tags.(tag) = [];   end
                    tsc_tags.(tag) = [tsc_tags.(tag) c];
                end
            end

            tags = fieldnames(tsc_tags);
            for t = 1 : length(tags)
                tag = tags{t};
                tag_trial_idx = tsc_tags.(tag);
                Data.Tags.(tag) = FillStateAtInds(trial_start_to_SG.idx(tag_trial_idx), ...
                                              trial_start_to_SG.idx, num_samples, false);
            end
            fprintf('tags: ');
            fprintf('%s ', tags{:});
            fprintf('\n');
        end
    end
                    
    % --------------------------------------------------------------
    % idly collecting mask
    % --------------------------------------------------------------
    idly = struct();
   
    idly.state = false(1, num_samples);
    idly.state(1:end) = INIT_idly_state;
    if isfield(D, 'IDLY_LABELLING')
        idly_to_SG = GetRelativeRefIndices(iData.QL.SequenceNo.IDLY_LABELLING, ... 
                                           iData.QL.SequenceNo.SAMPLE_GENERATED);
        idly.state = FillValueAtInds(logical(D.IDLY_LABELLING.state), ...
                     idly_to_SG.idx, num_samples, INIT_idly_state);
        %idly.state = logical(idly.state);
    end

    idly.reset = false(1, num_samples);
    idly.reset(1:end) = INIT_idly_reset;

    
    % --------------------------------------------------------------
    % button press masks
    % --------------------------------------------------------------
    button_sq1_per_bin = FindButtonPressIds(iData, iData.DF.defines.PS3_B_SQUARE, 1, INIT_button_sq1);
    fprintf('#SQ1 button press: %d\n', length(find(button_sq1_per_bin==1)));

    button_tri1_per_bin = FindButtonPressIds(iData, iData.DF.defines.PS3_B_TRIANGLE, 1, INIT_button_tri1);
    fprintf('#TRI1 button press: %d\n', length(find(button_tri1_per_bin==1)));
    
    button_cir1_per_bin = FindButtonPressIds(iData, iData.DF.defines.PS3_B_CIRCLE, 1, INIT_button_cir1);
    fprintf('#CIR1 button press: %d\n', length(find(button_cir1_per_bin==1)));
    
    button_x1_per_bin = FindButtonPressIds(iData, iData.DF.defines.PS3_B_X, 1, INIT_button_x1);
    fprintf('#X1 button press: %d\n', length(find(button_x1_per_bin==1)));

    
    % --------------------------------------------------------------
    % Create trial outcome masks
    % --------------------------------------------------------------
    trial_begins_task_id = find(iData.XM.config.task_state_config.trial_begins{1}==1, 1, 'first');
    trial_complete_task_id = find(iData.XM.config.task_state_config.trial_complete{1}==1, 1, 'first');
    
    %
    % Success
    %---------
    trial_complete_idx = find_task_state_inds(trial_complete_task_id, D.END_TASK_STATE.id);
    all_tasks_success_idx = find(D.END_TASK_STATE.outcome == 1);
    success_idx = intersect(all_tasks_success_idx, trial_complete_idx);
    success_seqno = iData.QL.SequenceNo.END_TASK_STATE(success_idx);
    success_to_trial_start = GetRelativeRefIndices(success_seqno, trial_start_to_SG.seqno); 
    success_trial_idx = success_to_trial_start.idx(success_to_trial_start.valid);
    success_per_bin = FillStateAtInds(trial_start_to_SG.idx(success_trial_idx), ...
                                      trial_start_to_SG.idx, num_samples, INIT_success);
    fprintf('#trial success: %d\n', length(success_trial_idx));

    %
    % Manual Success
    %----------------
    controller_id = 0;
    manual_succeed_idx = [];
    if (isfield(D, 'PS3_BUTTON_PRESS'))
        controller_idx = find(D.PS3_BUTTON_PRESS.controllerId == controller_id);
        R1_pressed_idx = find(D.PS3_BUTTON_PRESS.whichButton == iData.DF.defines.PS3_B_R1);
        R1_pressed_idx = intersect(R1_pressed_idx, controller_idx);
        if ~isempty(R1_pressed_idx)
            R1_pressed_seqno = iData.QL.SequenceNo.PS3_BUTTON_PRESS(R1_pressed_idx);
            R1_pressed = GetRelativeRefIndices(R1_pressed_seqno, iData.QL.SequenceNo.TASK_STATE_CONFIG);
            R1_pressed_TSC_idx = R1_pressed.idx(R1_pressed.valid);
            manual_succeed_idx = find(D.TASK_STATE_CONFIG.id(R1_pressed_TSC_idx) == trial_complete_task_id);
            manual_succeed_idx = R1_pressed_TSC_idx(manual_succeed_idx);
            manual_succeed_seqno = iData.QL.SequenceNo.TASK_STATE_CONFIG(manual_succeed_idx);
            manual_succeed_to_trial_start = GetRelativeRefIndices(manual_succeed_seqno, trial_start_to_SG.seqno);
            manual_succeed_idx = manual_succeed_to_trial_start.idx(manual_succeed_to_trial_start.valid);
        end
    end
    manual_success_per_bin = FillStateAtInds(trial_start_to_SG.idx(manual_succeed_idx), ...
                                       trial_start_to_SG.idx, num_samples, INIT_manual_success);
    fprintf('#trial manual success: %d\n', length(manual_succeed_idx));
    
    %
    % Manual Proceed
    %----------------
    controller_id = 0;
    manual_proceed_idx = [];
    if (isfield(D, 'PS3_BUTTON_PRESS'))
        controller_idx = find(D.PS3_BUTTON_PRESS.controllerId == controller_id);
        R1_pressed_idx = find(D.PS3_BUTTON_PRESS.whichButton == iData.DF.defines.PS3_B_R1);
        R1_pressed_idx = intersect(R1_pressed_idx, controller_idx);
        if ~isempty(R1_pressed_idx)
            R1_pressed_seqno = iData.QL.SequenceNo.PS3_BUTTON_PRESS(R1_pressed_idx);
            R1_pressed = GetRelativeRefIndices(R1_pressed_seqno, iData.QL.SequenceNo.TASK_STATE_CONFIG);
            R1_pressed_TSC_idx = R1_pressed.idx(R1_pressed.valid);
            trial_started_idx = find_task_state_inds([trial_begins_task_id:trial_complete_task_id], D.TASK_STATE_CONFIG.id);
            manual_proceed_idx = intersect(trial_started_idx, R1_pressed_TSC_idx);
            manual_proceed_seqno = iData.QL.SequenceNo.TASK_STATE_CONFIG(manual_proceed_idx);
            manual_proceed_to_trial_start = GetRelativeRefIndices(manual_proceed_seqno, trial_start_to_SG.seqno);
            manual_proceed_idx = manual_proceed_to_trial_start.idx(manual_proceed_to_trial_start.valid);
        end
    end
    manual_proceed_per_bin = FillStateAtInds(trial_start_to_SG.idx(manual_proceed_idx), ...
                                             trial_start_to_SG.idx, num_samples, INIT_manual_proceed);
    fprintf('#trial manual proceed: %d\n', length(manual_proceed_idx));

    %
    % Did Not Start
    %---------------
    possible_dns_idx = find_task_state_inds([1:trial_begins_task_id], D.END_TASK_STATE.id);
    failed_task_state_idx = find(D.END_TASK_STATE.outcome == 0);
    dns_idx = intersect(possible_dns_idx, failed_task_state_idx);
    dns_seqno = iData.QL.SequenceNo.END_TASK_STATE(dns_idx);
    dns_to_trial_start = GetRelativeRefIndices(dns_seqno, trial_start_to_SG.seqno);
    dns_trial_idx = dns_to_trial_start.idx(dns_to_trial_start.valid);
    dns_per_bin = FillStateAtInds(trial_start_to_SG.idx(dns_trial_idx), ...
                                        trial_start_to_SG.idx, num_samples, INIT_did_not_start);
    fprintf('#trial did not start: %d\n', length(dns_trial_idx));

    %
    % Cancelled
    %-----------
    trial_cancelled_idx = [];
    if (isfield(D, 'PS3_BUTTON_PRESS'))
        TRI_pressed_idx = find(D.PS3_BUTTON_PRESS.whichButton == iData.DF.defines.PS3_B_TRIANGLE);
        TRI_pressed_seqno = iData.QL.SequenceNo.PS3_BUTTON_PRESS(TRI_pressed_idx);
        TRI_pressed = GetRelativeRefIndices(TRI_pressed_seqno, iData.QL.SequenceNo.TASK_STATE_CONFIG);
        X_pressed_idx = find(D.PS3_BUTTON_PRESS.whichButton == iData.DF.defines.PS3_B_X);
        X_pressed_seqno = iData.QL.SequenceNo.PS3_BUTTON_PRESS(X_pressed_idx);
        X_pressed = GetRelativeRefIndices(X_pressed_seqno, iData.QL.SequenceNo.TASK_STATE_CONFIG);
        all_cancelled_idx = union(TRI_pressed.idx(TRI_pressed.valid), X_pressed.idx(X_pressed.valid));
        all_cancelled_task_ids = D.TASK_STATE_CONFIG.id(all_cancelled_idx);
        trial_cancelled_idx = all_cancelled_idx(find_task_id_in_list(all_cancelled_task_ids, ...
                                                 [trial_begins_task_id:trial_complete_task_id]));
        trial_cancelled_seqno = iData.QL.SequenceNo.TASK_STATE_CONFIG(trial_cancelled_idx);
        trial_cancelled_to_trial_start = GetRelativeRefIndices(trial_cancelled_seqno, trial_start_to_SG.seqno);
        trial_cancelled_idx = trial_cancelled_to_trial_start.idx(trial_cancelled_to_trial_start.valid);
    end
    cancelled_per_bin = FillStateAtInds(trial_start_to_SG.idx(trial_cancelled_idx), ...
                                      trial_start_to_SG.idx, num_samples, INIT_cancelled);
    fprintf('#trial cancelled: %d\n', length(trial_cancelled_idx));

    %
    % Timeout
    %---------


    %
    % Idle Timeout
    %--------------
    ets_failed_idx = find((D.END_TASK_STATE.outcome == 0) & ...
                          (D.END_TASK_STATE.id >= trial_begins_task_id & D.END_TASK_STATE.id <= trial_complete_task_id)==1);
    ets_reason = {}; 
    for k = 1 : length(ets_failed_idx)
        str_term = find(D.END_TASK_STATE.reason(:, ets_failed_idx(k))==0, 1);
        ets_reason{k} = deblank(char(D.END_TASK_STATE.reason(1:str_term-1, ets_failed_idx(k))))';
    end

    ets_idle_tout_rel_idx = find(strcmp(ets_reason, 'JV_IDLE_TIMEOUT')==1);
    ets_idle_tout_idx = ets_failed_idx(ets_idle_tout_rel_idx);
    ets_idle_tout_seqno =  iData.QL.SequenceNo.END_TASK_STATE(ets_idle_tout_idx);

    idle_timeout = GetRelativeRefIndices(ets_idle_tout_seqno, trial_start_to_SG.seqno);
    idle_timeout_idx = idle_timeout.idx(idle_timeout.valid);
    idle_timeout_per_bin = FillStateAtInds(trial_start_to_SG.idx(idle_timeout_idx), ...
                                           trial_start_to_SG.idx, num_samples, INIT_idle_timeout);
    fprintf('#idle_timeout:%d\n', length(idle_timeout_idx));
    
    %
    % Failure
    %---------
    possible_failure_idx = find_task_state_inds([trial_begins_task_id+1:trial_complete_task_id], D.END_TASK_STATE.id);
    failed_task_state_idx = find(D.END_TASK_STATE.outcome == 0);
    failure_idx = intersect(possible_failure_idx, failed_task_state_idx);
    failure_seqno = iData.QL.SequenceNo.END_TASK_STATE(failure_idx);
    failure_to_trial_start = GetRelativeRefIndices(failure_seqno, trial_start_to_SG.seqno);
    failure_trial_idx = failure_to_trial_start.idx(failure_to_trial_start.valid);
    failure_per_bin = FillStateAtInds(trial_start_to_SG.idx(failure_trial_idx), ...
                                      trial_start_to_SG.idx, num_samples, INIT_failure);
    fprintf('#trial failure: %d\n', length(failure_trial_idx));

    %
    % Attempt
    %----------
    attempt_per_bin = (success_per_bin | failure_per_bin) & ~idle_timeout_per_bin;
    fprintf('#attempt: %d\n', length(unique(trial_no_per_bin(attempt_per_bin))));
    

    % --------------------------------------------------------------
    % Create task state masks
    % --------------------------------------------------------------
    task_states_to_SG = GetRelativeRefIndices(iData.QL.SequenceNo.TASK_STATE_CONFIG, ... 
                                              iData.QL.SequenceNo.SAMPLE_GENERATED);
    % duplicate indices are ok (we don't need to validate them)
    task_state_indices = task_states_to_SG.idx;
    task_state_codes = D.TASK_STATE_CONFIG.id;
    task_state_code_defs = iData.XM.config.task_state_config.state_names{1}; 
    %task_state_code_defs = iData.XM.config.task_state_config.state_names{end};
    for f = 1 : length(task_state_code_defs) 
        task_state_tags.(task_state_code_defs{f}) = f; 
    end
%     if( ~isfield( D, 'TASK_STATE_CONFIG')) %%% 'TRIAL_EVENT'
%         % If data is in Pre-July 2011 format, then we look for a
%         % TRIAL_EVENT messages to find task state transitions
%         task_state_codes = D.TRIAL_EVENT.event_code;
%         task_state_code_defs = CopyStructFields( R.defines, 'TE_');
% 		% Rename task state fields to match the RP3 data format definition
% 		task_state_code_defs = rename_task_states( task_state_code_defs);
%         task_state_indices = GetEventIndices( iData.QL, ...
%             'TRIAL_EVENT', 'SAMPLE_GENERATED');
%         task_state_tags = fieldnames( task_state_code_defs);
%     end
    
    % Convert array of task state indices to continuous vector of task state codes
    task_state_codes_per_bin = double(INIT_task_state_codes) * ones( 1, num_samples);
    task_state_indices(end+1) = num_samples+1;
    for i = 1 : length( task_state_codes)
        code = task_state_codes(i);
        % if there are duplicates in task_state_indices due to aliasing,
        % the codes that fall within one SG sample period will be 
        % discarded because their begin_idx > end_idx
        begin_idx = task_state_indices(i);
        end_idx = task_state_indices(i+1)-1;
        task_state_codes_per_bin(begin_idx:end_idx) = code;
    end

    task_state_masks_per_bin = struct();
    for code = 1 : length( task_state_code_defs)
        tag = task_state_code_defs{code};
        task_state_masks_per_bin.(tag) = false( 1, num_samples);

        task_begin_idx = find(D.TASK_STATE_CONFIG.id == code);
        begin_end_mask = false(1, num_samples);
        for r = 1 : length( task_begin_idx)
            idx = task_begin_idx(r);
            begin_ind = task_state_indices(idx);
            end_ind = task_state_indices(idx+1);
            % here we handle duplicate indices by allowing them to exist
            % for one sample period (note that this will contradict
            % task_state_codes_per_bin calculated above which overwrites
            % older of the messages which occupy the same SG sample period,
            % but that's ok)
            if (begin_ind ~= end_ind), end_ind = end_ind - 1; end
            begin_end_mask(begin_ind:end_ind) = true;
        end

        if ((INIT_task_state_codes == code) && (task_state_indices(1) > 1))
            begin_ind = 1;
            end_ind = task_state_indices(1);
            if (begin_ind ~= end_ind), end_ind = end_ind - 1; end
            begin_end_mask(begin_ind:end_ind) = true;
        end

        task_state_masks_per_bin.(tag)(begin_end_mask) = true;
    end
    
    
    % --------------------------------------------------------------
    % Create task state outcome masks
    % --------------------------------------------------------------

    %
    % Success
    %---------
    tsom_success_ETS_inds = find_task_state_inds(1, D.END_TASK_STATE.outcome);
    tsom_success_ETS_seqno = iData.QL.SequenceNo.END_TASK_STATE(tsom_success_ETS_inds);
    tsom_success_TSC = GetRelativeRefIndices(tsom_success_ETS_seqno, iData.QL.SequenceNo.TASK_STATE_CONFIG);
    tsom_success_TSC_idx = tsom_success_TSC.idx(tsom_success_TSC.valid);
    tsom_success_per_bin = FillStateAtInds(task_states_to_SG.idx(tsom_success_TSC_idx), ...
                                           task_states_to_SG.idx, num_samples, INIT_tsom_success);
    fprintf('#task state success: %d\n', length(tsom_success_TSC.idx));

    %
    % Manual
    %--------
    tsom_manual_idx = [];
    if (isfield(D, 'PS3_BUTTON_PRESS'))
        R1_pressed_idx = find(D.PS3_BUTTON_PRESS.whichButton == iData.DF.defines.PS3_B_R1);
        R1_pressed_seqno = iData.QL.SequenceNo.PS3_BUTTON_PRESS(R1_pressed_idx);
        R1_pressed = GetRelativeRefIndices(R1_pressed_seqno, iData.QL.SequenceNo.TASK_STATE_CONFIG);
        tsom_manual_idx = R1_pressed.idx(R1_pressed.valid);
    end
    tsom_manual_per_bin = FillStateAtInds(task_states_to_SG.idx(tsom_manual_idx), ...
                                          task_states_to_SG.idx, num_samples, INIT_tsom_manual);
    fprintf('#task state manual proceed: %d\n', length(tsom_manual_idx));

    %
    % Failure
    %---------
    tsom_fail_ETS_inds = find_task_state_inds(0, D.END_TASK_STATE.outcome);
    tsom_fail_ETS_seqno = iData.QL.SequenceNo.END_TASK_STATE(tsom_fail_ETS_inds);
    tsom_fail_TSC = GetRelativeRefIndices(tsom_fail_ETS_seqno, iData.QL.SequenceNo.TASK_STATE_CONFIG);
    tsom_fail_TSC_idx = tsom_fail_TSC.idx(tsom_fail_TSC.valid);
    tsom_fail_per_bin = FillStateAtInds(task_states_to_SG.idx(tsom_fail_TSC_idx), ...
                                        task_states_to_SG.idx, num_samples, INIT_tsom_failure);
    fprintf('#task state failure: %d\n', length(tsom_fail_TSC.idx));
    
    %
    % Cancelled
    %-----------
    tsom_cancel_idx = [];
    if (isfield(D, 'PS3_BUTTON_PRESS'))
        TRI_pressed_idx = find(D.PS3_BUTTON_PRESS.whichButton == iData.DF.defines.PS3_B_TRIANGLE);
        TRI_pressed_seqno = iData.QL.SequenceNo.PS3_BUTTON_PRESS(TRI_pressed_idx);
        TRI_pressed = GetRelativeRefIndices(TRI_pressed_seqno, iData.QL.SequenceNo.TASK_STATE_CONFIG);
        X_pressed_idx = find(D.PS3_BUTTON_PRESS.whichButton == iData.DF.defines.PS3_B_X);
        X_pressed_seqno = iData.QL.SequenceNo.PS3_BUTTON_PRESS(X_pressed_idx);
        X_pressed = GetRelativeRefIndices(X_pressed_seqno, iData.QL.SequenceNo.TASK_STATE_CONFIG);
        tsom_cancel_idx = union(TRI_pressed.idx(TRI_pressed.valid), X_pressed.idx(X_pressed.valid));
    end
    tsom_cancel_per_bin = FillStateAtInds(task_states_to_SG.idx(tsom_cancel_idx), ...
                                          task_states_to_SG.idx, num_samples, INIT_tsom_cancel);
    fprintf('#task state cancelled: %d\n', length(tsom_cancel_idx));
    
    
    % --------------------------------------------------------------
    % OtherMasks
    % --------------------------------------------------------------
    used_for_calib_idx = [];
    if (isfield(D.TASK_STATE_CONFIG, 'use_for_calib'))
        used_for_calib_inds = find_task_state_inds(1, D.TASK_STATE_CONFIG.use_for_calib);
        used_for_calib_seqno = iData.QL.SequenceNo.TASK_STATE_CONFIG(used_for_calib_inds);
        used_for_calib_SG = GetRelativeRefIndices(used_for_calib_seqno, task_states_to_SG.seqno);
        used_for_calib_idx = used_for_calib_SG.idx(used_for_calib_SG.valid);
    end
    calib_per_bin = FillStateAtInds(task_states_to_SG.idx(used_for_calib_idx), ...
                                    task_states_to_SG.idx, num_samples, INIT_used4calib);

    monkey_success = success_per_bin & ~manual_success_per_bin;
    calib_per_bin = calib_per_bin & monkey_success;


    % --------------------------------------------------------------
    % TaskJudging
    % --------------------------------------------------------------
    AllThresholds = [D.TASK_STATE_CONFIG.trans_threshold; ...
                     nan(3,length(D.TASK_STATE_CONFIG.trans_threshold));
                     D.TASK_STATE_CONFIG.ori_threshold; ...
                     nan(3,length(D.TASK_STATE_CONFIG.trans_threshold));
                     D.TASK_STATE_CONFIG.finger_threshold];
    
    threshold = FillValueAtInds(AllThresholds(:,task_states_to_SG.valid), ...
                                    task_states_to_SG.idx(task_states_to_SG.valid), num_samples, INIT_jthresh);

    Data.TaskJudging.Threshold = threshold;
    
    % --------------------------------------------------------------
    % Get IDLE data
    % --------------------------------------------------------------

    idle_data = struct();
    if( isfield( D, 'IDLE'))
        idle_data = D.IDLE;
        idle_data.idle = logical( idle_data.idle);
        idle_data = rmfield( idle_data, 'sample_header');
        idle_data = rmfield( idle_data, 'reserved');
    end
    
    % --------------------------------------------------------------
    % Get kinematic data
    % --------------------------------------------------------------
    position = struct();
    velocity = struct();
    
    if( isfield( D, 'EM_MOVEMENT_COMMAND'))
        position.Decoded = D.EM_MOVEMENT_COMMAND.pos;
        velocity.Decoded = D.EM_MOVEMENT_COMMAND.vel;
    end

    if( isfield( D, 'ROBOT_CONTROL_SPACE_ACTUAL_STATE'))
        position.Actual = D.ROBOT_CONTROL_SPACE_ACTUAL_STATE.pos;
        velocity.Actual = D.ROBOT_CONTROL_SPACE_ACTUAL_STATE.vel;
        position.ActualCoriMatrix = D.ROBOT_CONTROL_SPACE_ACTUAL_STATE.CoriMatrix;
    end

    if( isfield( D, 'PLANNER_MOVEMENT_COMMAND'))
        velocity.Planner = D.PLANNER_MOVEMENT_COMMAND.vel;
    end

    if( isfield( D, 'FINAL_MOVEMENT_COMMAND'))
        velocity.Control = D.FINAL_MOVEMENT_COMMAND.vel;
    elseif( isfield( D, 'FIXTURED_COMPOSITE_MOVEMENT_COMMAND'))
        velocity.Control = D.FIXTURED_COMPOSITE_MOVEMENT_COMMAND.vel;
    elseif( isfield( D, 'COMPOSITE_MOVEMENT_COMMAND'))
        velocity.Control = D.COMPOSITE_MOVEMENT_COMMAND.vel;
    end
    
    if( isfield( D, 'OPTOTRAK_SAMPLED_DATA'))
        valid_idx = find(iData.QL.ValidSampleMask.OPTOTRAK_SAMPLED_DATA == 1, 1, 'first');
        nMarkers = D.OPTOTRAK_SAMPLED_DATA.nMarkers(valid_idx);
        for m = 1 : nMarkers
            marker_data(:,:,m) = [D.OPTOTRAK_SAMPLED_DATA.x(m,:); ...
                                  D.OPTOTRAK_SAMPLED_DATA.y(m,:); ...
                                  D.OPTOTRAK_SAMPLED_DATA.z(m,:)];
        end

        for m = nMarkers + 1 : size(D.OPTOTRAK_SAMPLED_DATA.x, 1)
            marker_data(:,:,m) = [nan(1, length(D.OPTOTRAK_SAMPLED_DATA.nMarkers)); ...
                                  nan(1, length(D.OPTOTRAK_SAMPLED_DATA.nMarkers)); ...
                                  nan(1, length(D.OPTOTRAK_SAMPLED_DATA.nMarkers))];
        end

        position.Markers = marker_data;
    end
    
    if( isfield( D, 'ROBOT_CONTROL_CONFIG'))
        rcc_SG = GetRelativeRefIndices( iData.QL.SequenceNo.ROBOT_CONTROL_CONFIG, ...
                                        iData.QL.SequenceNo.SAMPLE_GENERATED);
                                    
        position.target = FillValueAtInds(D.ROBOT_CONTROL_CONFIG.target(:,rcc_SG.valid), ...
                                          rcc_SG.idx(rcc_SG.valid), num_samples, INIT_position_target);

        ortho_imp = FillValueAtInds(D.ROBOT_CONTROL_CONFIG.orthVelImpedance(:,rcc_SG.valid), ...
                                    rcc_SG.idx(rcc_SG.valid), num_samples, INIT_ortho_imp);

        auto_ctrl = FillValueAtInds(D.ROBOT_CONTROL_CONFIG.autoVelControlFraction(:,rcc_SG.valid), ...
                                    rcc_SG.idx(rcc_SG.valid), num_samples, INIT_auto_ctrl);

        ctrl_dims = FillValueAtInds(D.ROBOT_CONTROL_CONFIG.importantDOF(:,rcc_SG.valid), ...
                                    rcc_SG.idx(rcc_SG.valid), num_samples, INIT_ctrl_dims);
                                
        Data.TaskConfigVals.ControlledDims = ctrl_dims;
        Data.TaskConfigVals.OrthoImpedance = ortho_imp;
        Data.TaskConfigVals.AutoControl = auto_ctrl;
    end

    if( isfield( D, 'PLANNER_STATE'))
        position.PlannerTarget = D.PLANNER_STATE.targetPos;
    end
    
    % We need to init position.JointAngles incase we got no
    % GROBOT_RAW_FEEDBACK messages (because VulcanX is dead)
    % (This is just to make things work for online processing)
    position.JointAngles = nan(length(iData.DF.MDF.GROBOT_RAW_FEEDBACK.j_ang), num_samples);
    if( isfield( D, 'GROBOT_RAW_FEEDBACK'))
        jang_SG = GetRelativeRefIndices( iData.QL.SequenceNo.GROBOT_RAW_FEEDBACK, ...
                                         iData.QL.SequenceNo.SAMPLE_GENERATED);
        position.JointAngles = FillValueAtInds(D.GROBOT_RAW_FEEDBACK.j_ang(:,jang_SG.valid), ...
                                               jang_SG.idx(jang_SG.valid), num_samples, INIT_position_jang);
    end

    if( isfield( D, 'EM_DRIFT_CORRECTION'))
        drift_correction = D.EM_DRIFT_CORRECTION.drift_correction;
        Data.DriftCorrection = drift_correction;
    end


    Data.TaskStateMasks = task_state_masks_per_bin;
    
    Data.TaskStateOutcomeMasks.Success = tsom_success_per_bin;
    Data.TaskStateOutcomeMasks.Manual = tsom_manual_per_bin;
    Data.TaskStateOutcomeMasks.Failure = tsom_fail_per_bin;
    Data.TaskStateOutcomeMasks.Cancelled = tsom_cancel_per_bin;
    
    Data.TaskStateCodes.Values = task_state_codes_per_bin;
    Data.TaskStateCodes.Definitions = task_state_tags;
    
    Data.OutcomeMasks.Success = success_per_bin;
    Data.OutcomeMasks.ManualSuccess = manual_success_per_bin;
    Data.OutcomeMasks.ManualProceed = manual_proceed_per_bin;
    Data.OutcomeMasks.Failure = failure_per_bin;
    Data.OutcomeMasks.Cancelled = cancelled_per_bin;
    Data.OutcomeMasks.Attempt = attempt_per_bin;
    Data.OutcomeMasks.DidNotStart = dns_per_bin;
    Data.OutcomeMasks.IdleTimeout = idle_timeout_per_bin;
    %Data.OutcomeMasks.Timeout = timeout_per_bin;
    
    Data.OtherMasks.UsedForCalib = calib_per_bin;
    Data.OtherMasks.ButtonPress_SQ1 = button_sq1_per_bin;
    Data.OtherMasks.ButtonPress_TRI1 = button_tri1_per_bin;
    Data.OtherMasks.ButtonPress_CIR1 = button_cir1_per_bin;
    Data.OtherMasks.ButtonPress_X1 = button_x1_per_bin;

    Data.IdlyLabelling = idly;

    Data.Position = position;
    Data.Velocity = velocity;
    if (isfield(D, 'SPM_SPIKECOUNT')), Data.SpikeCount = active_spike_data;
    elseif (isfield(D, 'SPM_FIRINGRATE')), Data.FiringRate = active_spike_data; end
    Data.Time = time_per_bin;
    Data.TrialNo = trial_no_per_bin;
    Data.BlockNo = block_no_per_bin;
    Data.ActiveChannelMask = active_chan_mask;
    Data.Dt = dt_per_bin;
    Data.Version = version_info;
    Data.Build = build_info;
    Data.ConfigName = config_name_info;

    Data.Idle = idle_data;


    %
    % save the end bits of Data (above) for initializing the next iteration
    %
    IncrState.FDataEnd = GetEndData(Data);
    
    

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%	
function [ids] = find_task_state_inds(ts_ids, ref_ids)
    ids = [];
    for i = 1 : length(ts_ids)
        ts_id = ts_ids(i);
        ids = [ids find(ref_ids == ts_id)];
    end
    ids = sort(ids);


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%	
function [out] = find_task_id_in_list(ts_ids, list)
    out = false(1, length(ts_ids));

    for i = 1 : length(ts_ids)
        ts_id = ts_ids(i);
        if ~isempty(find(ts_id==list))
            out(i) = true;
        end
    end
