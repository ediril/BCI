function executive( ConfigFile, mm_ip)

% ExecutiveModule( ConfigFile, mm_ip)
%
% ConfigFile is the file name of the main config file that should be
% loaded from the config/ directory
%
% mm_ip is the network address of the MessageManager
%
% Meel Velliste 8/10/2008
% Emrah Diril 9/10/2011

    dbstop if error;

    global XM;
    global COMMAND_LINE_ARGUMENTS;
    global EVENT_MAP;
    global DF_runtime;

    Dragonfly_BaseDir = getenv('DRAGONFLY');
    App_SourceDir = getenv('BCI_MODULES');
    App_IncludeDir = getenv('BCI_INCLUDE');

    addpath([Dragonfly_BaseDir '/lang/matlab']);
    addpath([App_SourceDir '/Common/matlab']);

    if ~exist( 'ConfigFile', 'var') || isempty(ConfigFile) || strcmpi(ConfigFile, 'none')
        error( 'Missing ConfigFile argument');
    end

    COMMAND_LINE_ARGUMENTS.ConfigFile = ConfigFile;

    % Run Dragonfly Module
    ModuleID = 'EXEC_MOD';
    MessageConfigFile = [App_IncludeDir '/Dragonfly_config.mat'];
    MessageTypes = {...
            'KEYBOARD'...
            'AM_APP_NAME'...
            'TIMED_OUT'...
            'TIMER_EXPIRED'...
            'JOYPAD_R1'...
            'JOYPAD_X' ...
            'XM_START_SESSION'...
            'XM_ABORT_SESSION'...
            'PROCEED_TO_Failure'...
            'PROCEED_TO_NextState'...
            'APP_ERROR'...
	        'READY_BUTTON' ...
            'PAUSE_EXPERIMENT' ...
            'RESUME_EXPERIMENT' ...
            'PS3_BUTTON_PRESS' ...
            'PS3_BUTTON_RELEASE' ...
            'EXIT' ...
            'JUDGE_VERDICT'...
            'MESSAGE_LOG_SAVED' ...
            'XM_START_SESSION' ...
            'PING' ...
            };

    ConnectArgs = {ModuleID, '', MessageConfigFile};
    if exist('mm_ip','var') && ~isempty(mm_ip)
        ConnectArgs{end+1} = ['-server_name ' mm_ip];
    end
    ConnectToMMM(ConnectArgs{:})
    Subscribe(MessageTypes{:})

    DF_runtime.EventHook = @EventHook;

    SetupSession();

    %SendModuleVersion('executive');

    % run until all reps are done
    while (1)

        % run until all targets are done
        while(1)
            SetupTrial();

%            if ~XM.pausing_experiment
                num_task_states = length(XM.config.task_state_config.state_names);
                ts = 1;
                while ( ts <= num_task_states )
                    %try
                        task_state_config = GetTaskStateConfig( ts);

                        fprintf('|%s| ', task_state_config.state_names);

                        if( task_state_config.skip_state == 1),
                            fprintf('skipped\n');
                            ts = ts + 1;
                            continue;
                        end

                        MoveDensoToPresentationPos( task_state_config);
                        [target, cori, judge_target] = DecideWhatTheCurrentTargetIs( task_state_config);
                        RunTaskState( task_state_config, target, cori);
                        ConfigureTaskStateEvents( task_state_config);
                        ConfigureSimpleJudge( ts, task_state_config, judge_target, cori);

                    %catch ME
                    %    fprintf('\n>>> ERROR: %s\n', ME.message);
                    %    fprintf('\nPlease fix the problem and hit ENTER to continue\n');
                    %    pause;
                    %    ts = num_task_states + 1;   % start a brand new trial
                    %end

                    if (ts <= num_task_states)
                        %try
                            RcvEvent = [];
                            if ( ~isempty(fieldnames(EVENT_MAP)))
                                ExpectedEvents = fieldnames( EVENT_MAP);
                                RcvEvent = WaitFor( ts, ExpectedEvents{:});
                            end

                            if( XM.aborting_session)
                                disp('Aborting session..');
                                break;
                            end

                            [outcome, next_state] = HandleTaskStateEnded( ts, RcvEvent, task_state_config);

                            % check task_state_config.goto
                            if isfield(task_state_config, 'goto')
                                switch(outcome)
                                    case 0  % failed
                                        if isfield(task_state_config.goto, 'f')
                                            val = str2num(task_state_config.goto.f);
                                            if ~isempty(val)
                                                next_state = val;
                                            end
                                        end

                                    case 1  % success
                                        if isfield(task_state_config.goto, 's')
                                            val = str2num(task_state_config.goto.s);
                                            if isnumeric(val)
                                                next_state = val;
                                            end
                                        end
                                end
                            end

                            if (next_state > 0)
                                ts = next_state;
                            else
                                ts = ts + 1;
                            end

                        %catch ME
                        %    fprintf('\n>>> ERROR: %s\n', ME.message);
                        %    fprintf('\nPlease fix the problem and hit ENTER to continue\n');
                        %    pause;
                        %    ts = num_task_states;  % skip to InterTrial state
                        %end
                    end
                end
%            end

            InterTrial();

            if( isempty( XM.combos_to_be_tried) || XM.aborting_session), break;  end

        end

        if( (XM.rep_num >= XM.config.num_reps) || XM.aborting_session)
            disp('Finished all reps, will quit now (or someone aborted session)');
            %--- Stop Analog Stream
            SendSignal IO_STOP_STREAM;
            break;
        end
    end
    DoExit();



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% finger codes t=thumb, i=index, m=middle, r=ring, l=little
% f=force (from GROBOT_SEGMENT_PERCEPTS, see below)
% t=torque (from GROBOT_RAW_FEEDBACK.j_trq - lower priority)
%
% GROBOT_SEGMENT_PERCEPTS: ind_force mid_force rng_force lit_force thb_force
%
function mask = get_dims_mask(dims)

    global DF;

    dim_tags = {'pos0', 'pos1', 'pos2', 'pos3', 'pos4', 'pos5', 'pos6', ...
                'pos7', 'pos8', 'pos9', 'ifx', 'ify', 'ifz', 'mfx', ...
                'mfy', 'mfz', 'rfx', 'rfy', 'rfz', 'lfx', 'lfy', 'lfz', ...
                'tfx', 'tfy', 'tfz'};

    mask = false(1, DF.defines.MAX_HAND_DIMS);
    for d = 1 : length(dims)
        mask = mask | ~cellfun(@isempty,strfind(dim_tags, dims{d}));
    end


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [TargetPos, CoriMatrix, JudgeTargetPos] = DecideWhatTheCurrentTargetIs( task_state_config)

    global XM;
    global DF;

    %
    % Determine target
    %

    mpl_tgt_cfg = sprintf('config_%s', task_state_config.reach_target);
    mpl_tgt_idx = 1;
    if (size(task_state_config.target_configurations.(mpl_tgt_cfg).targets, 1) > 1)
        mpl_tgt_idx = task_state_config.target_configurations.combos.(task_state_config.reach_target)(XM.active_combo_index);
    end
    tgt = task_state_config.target_configurations.(mpl_tgt_cfg).targets(mpl_tgt_idx,:);

    %fprintf('MPL target  : %s,  idx: %d\n', task_state_config.reach_target, mpl_tgt_idx);

    hand = zeros(1,DF.defines.MAX_HAND_DIMS);
    if isfield(task_state_config, 'hand_target')
        hand_cfg = sprintf('config_tool_%d', XM.active_tool_id);
        hand_raw = task_state_config.target_configurations.(hand_cfg).(task_state_config.hand_target);
        if iscell(hand_raw)
            non_num_idx = strcmp(hand_raw, '-');
            if sum(non_num_idx>0) == 0
                error(['Hand target "' (task_state_config.hand_target) '" has invalid entry']);
            end
            hand_raw{non_num_idx} = '0.0';
            hand_raw = cellfun(@str2num, hand_raw);
        end

        dims = task_state_config.target_configurations.(hand_cfg).dimensions;
        dims_mask = get_dims_mask(dims);
        hand(dims_mask) = hand_raw;
    end

    TargetPos = [tgt(1:3) 0 tgt(4:6) 0 hand];

    JudgeTargetPos = TargetPos;
    if isfield(task_state_config, 'separate_judge_target') && ~strcmp(task_state_config.separate_judge_target, '-')
        judge_tgt_cfg = sprintf('config_%s', task_state_config.separate_judge_target);
        judge_tgt_idx = 1;
        if (size(task_state_config.target_configurations.(judge_tgt_cfg).targets, 1) > 1)
            judge_tgt_idx = mpl_tgt_idx;
        end
        judge_tgt = task_state_config.target_configurations.(judge_tgt_cfg).targets(judge_tgt_idx,:);
        JudgeTargetPos(1:3) = judge_tgt(1:3);
        %fprintf('Judge target  : %s,  idx: %d\n', task_state_config.separate_judge_target, mpl_tgt_idx);
    end

	tgt_ori_rot_mat = ypr2mat(tgt(4:6));
	if isfield(task_state_config, 'use_grasp_ori_offset') && ~strcmp(task_state_config.use_grasp_ori_offset, '-')
        grasp_orientation_offset = task_state_config.target_configurations.(hand_cfg).grasp_orientation_offset;
		offset_ori_rot_mat = ypr2mat(grasp_orientation_offset);
		tgt_ori_rot_mat = tgt_ori_rot_mat * offset_ori_rot_mat;
	end
	CoriMatrix = tgt_ori_rot_mat';
	CoriMatrix = CoriMatrix(:)';


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function ConfigureSimpleJudge( id, task_state_config, target, cori)

    global DF;
    global XM;

    % Determine timeout
    %
    Timeout = CalcTaskStateTimeout( task_state_config);


    % Determine thresholds
    %
    trans_threshold = nan;
    trans_judging_polarity = 1; % = "<" (default)
    if isfield(task_state_config, 'trans_threshold') 
        if ~strcmp(task_state_config.trans_threshold, '-')
            if ~isempty(strfind(task_state_config.trans_threshold, '>'))
                trans_judging_polarity = 2;
            end
            trans_threshold = str2num(regexprep(task_state_config.trans_threshold, '(<|>)', ''));
        end
    end

    trans_threshold_f = nan;
    trans_f_judging_polarity = 1; % = "<" (default)
    if isfield(task_state_config, 'trans_threshold_f')
        if ~strcmp(task_state_config.trans_threshold_f, '-')
            if ~isempty(strfind(task_state_config.trans_threshold_f, '>'))
                trans_f_judging_polarity = 2;
            end
            trans_threshold_f = str2num(regexprep(task_state_config.trans_threshold_f, '(<|>)', ''));
        end
    end

    ori_threshold = nan;
    ori_judging_polarity = 1; % = "<" (default)
    if isfield(task_state_config, 'ori_threshold')
        if ~strcmp(task_state_config.ori_threshold, '-')
            %ori_threshold = str2num(task_state_config.ori_threshold) * (pi/180);
            if ~isempty(strfind(task_state_config.ori_threshold, '>'))
                ori_judging_polarity = 2;
            end
            ori_threshold = str2num(regexprep(task_state_config.ori_threshold, '(<|>)', '')) * (pi/180);
        end
    end
    
    ori_threshold_f = nan;
    ori_f_judging_polarity = 1; % = "<" (default)
    if isfield(task_state_config, 'ori_threshold_f')
        if ~strcmp(task_state_config.ori_threshold_f, '-')
            if ~isempty(strfind(task_state_config.ori_threshold_f, '>'))
                ori_f_judging_polarity = 2;
            end
            ori_threshold_f = str2num(regexprep(task_state_config.ori_threshold_f, '(<|>)', ''));
        end
    end

    % figure out idle_target if any
    idle_target = nan(1, DF.defines.MAX_CONTROL_DIMS);
    if isfield(task_state_config, 'idle_target') && ~strcmp(task_state_config.idle_target, '-')
        idle_tgt_cfg = sprintf('config_%s', task_state_config.idle_target);
        idle_tgt_idx = 1;
        if (size(task_state_config.target_configurations.(idle_tgt_cfg).targets, 1) > 1)
            idle_tgt_idx = task_state_config.target_configurations.combos.(task_state_config.idle_target)(XM.active_combo_index);
        end
        tgt = task_state_config.target_configurations.(idle_tgt_cfg).targets(idle_tgt_idx,:);
        idle_target = target;   % keep same hand target
        idle_target(1:length(tgt)) = tgt;
    end
    
    
    % ------------
    % Figure out finger thresholds in target.config file
    % ------------
    % NaN: don't judge, else: threshold
    finger_threshold = nan(1, DF.defines.MAX_HAND_DIMS);
    % ------------
    % 1=target less than threshold [<] (default)
    % 2=target greater than threshold [>]
    finger_threshold_judging_polarity = ones(1, DF.defines.MAX_HAND_DIMS);
    % ------------
    % 1=distance (default), 2=absolute
    finger_threshold_judging_method = ones(1, DF.defines.MAX_HAND_DIMS);
    
    if isfield( task_state_config, 'hand_target')
        hand_cfg = sprintf('config_tool_%d', XM.active_tool_id);
        hand_tgt_j = sprintf('%s_j', task_state_config.hand_target);
        hand_j_raw = XM.config.task_state_config.target_configurations.(hand_cfg).(hand_tgt_j);

        dims = task_state_config.target_configurations.(hand_cfg).dimensions;
        dims_mask = get_dims_mask(dims);

        hand_judging = repmat({'-'}, 1, DF.defines.MAX_HAND_DIMS);
        hand_judging(dims_mask) = hand_j_raw;

        task_state_config.finger_threshold = regexprep(hand_judging, '(abs|dist)', '');

        task_state_config.finger_threshold_judging_method = repmat({'dist'}, 1, DF.defines.MAX_HAND_DIMS); % defaults
        %{'dist', 'dist', 'dist', 'dist'};
        idx_abs = ~cellfun(@isempty,strfind(hand_judging, 'abs'));
        idx_abs = find(idx_abs==true);
        if ~isempty(idx_abs)
            task_state_config.finger_threshold_judging_method(idx_abs) = repmat({'abs'}, 1, length(idx_abs));
        end

        tsc_ft = task_state_config.finger_threshold;
        if ischar(task_state_config.finger_threshold),  tsc_ft = {task_state_config.finger_threshold};   end
        i1 = ~cellfun(@isempty,strfind(tsc_ft, '>'));
        finger_threshold(i1) = cellfun(@str2num,(strrep(tsc_ft(i1), '>', '')));
        finger_threshold_judging_polarity(i1) = 2;
        i2 = ~cellfun(@isempty,strfind(tsc_ft, '<'));
        finger_threshold(i2) = cellfun(@str2num,(strrep(tsc_ft(i2), '<', '')));
        i3 = ~cellfun(@isempty,strfind(tsc_ft, '-')) & cellfun(@(x) length(x)==1, tsc_ft);
        i4 = ~(i1 | i2 | i3);
        finger_threshold(i4) = cellfun(@str2num,tsc_ft(i4));


        tsc_ftjm = task_state_config.finger_threshold_judging_method;
        if ischar(task_state_config.finger_threshold_judging_method),  tsc_ftjm = {task_state_config.finger_threshold_judging_method};   end
        i1 = ~cellfun(@isempty,strfind(tsc_ftjm, 'abs'));
        finger_threshold_judging_method(i1) = 2;
        i2 = ~cellfun(@isempty,strfind(tsc_ftjm, 'dist'));
        invalid = ~(i1 | i2);
        if ~isempty(find(invalid))
            fprintf('\n--> WARNING: Invalid finger_threshold_judging_method found at index: ');
            fprintf('%d ', find(invalid));
            fprintf('\n"distance" will be used instead..\n\n');
        end
    end

    relax_arm = 0;
    if isfield(task_state_config, 'relax_arm')
        if isnumeric(task_state_config.relax_arm)
            if (task_state_config.relax_arm == 1), relax_arm = 1;  end
        else
            if strcmpi(task_state_config.relax_arm, '1'), relax_arm = 1;   end
        end
    end

    reach_offset = 0;
    if isfield(task_state_config, 'reach_offset')
        if isnumeric(task_state_config.reach_offset)
            if (task_state_config.reach_offset > 0), reach_offset = 1;  end
        else
            if strcmpi(task_state_config.reach_offset, '1'), reach_offset = 1;  end
        end
    end

    idle_timeout = nan;
    if isfield(task_state_config, 'idle_timeout')
        if isnumeric(task_state_config.idle_timeout)
           idle_timeout = task_state_config.idle_timeout;
        else
            if ~strcmpi(task_state_config.idle_timeout, '-')
                idle_timeout = str2num(task_state_config.idle_timeout);
            end
        end
        if (idle_timeout == 0), idle_timeout = nan; end
    end

    idle_gateable = 0;
    if isfield(task_state_config, 'idle_gateable')
        idle_gateable = task_state_config.idle_gateable;
    end

    msg = DF.MDF.TASK_STATE_CONFIG;
    msg.id = int32(id);
    msg.rep_num = int32(XM.rep_num);
    msg.use_for_calib = int32(task_state_config.use_for_calibration(1));
    msg.target_combo_index = int32(XM.active_combo_index);
    msg.timed_out_conseq = int32(task_state_config.timed_out_conseq);
    msg.reach_offset = int32(reach_offset);
    msg.relax_arm = int32(relax_arm);
    msg.idle_gateable = int32(idle_gateable);
    msg.ts_time = GetAbsTime( );
    msg.target = target;
    msg.idle_target = idle_target(1:DF.defines.MAX_CONTROL_DIMS);
    msg.coriMatrix = cori;
    msg.idle_timeout = idle_timeout;
    msg.trans_threshold = trans_threshold;
    msg.trans_threshold_judging_polarity = int32(trans_judging_polarity);
    msg.ori_threshold = ori_threshold;
    msg.ori_threshold_judging_polarity = int32(ori_judging_polarity);
    msg.trans_threshold_f = trans_threshold_f;
    msg.trans_threshold_f_judging_polarity = int32(trans_f_judging_polarity);
    msg.ori_threshold_f = ori_threshold_f;
    msg.ori_threshold_f_judging_polarity = int32(ori_f_judging_polarity);
    msg.finger_threshold = finger_threshold;
    msg.finger_threshold_judging_method = int32(finger_threshold_judging_method);
    msg.finger_threshold_judging_polarity = int32(finger_threshold_judging_polarity);
    
    msg.timeout = double(Timeout);

    if isfield(task_state_config, 'tags')
        tags = task_state_config.tags;
        if iscell(tags)
            tags(2:end) = cellfun(@(x) sprintf(' %s',x), tags(2:end), 'un', false);
            tags = cell2mat(tags);
        end
        msg.tags(1:length(tags)) = tags;
    end

    SendMessage( 'TASK_STATE_CONFIG', msg);



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function ConfigureTaskStateEvents(task_state_config)

    global XM;
	global EVENT_MAP;

    %
	% EVENT_MAP.<event name> = <outcome> (0=failure, 1=success)
	%
	EVENT_MAP = struct();

    % Placeholder so we can receive the message, actual outcomes are
    % setup in HandleTaskStateEnded()
    EVENT_MAP.JUDGE_VERDICT     = [];


    events = [];
    if isfield(task_state_config, 'event_mappings')
        events = fieldnames(task_state_config.event_mappings);
        for i = 1 : length(events)
            event = events{i};

            if (strcmp(event, 'DENSO_MOVE_COMPLETE') && ~XM.config.enable_denso),  continue;   end

            if( strcmpi(task_state_config.event_mappings.(event), 's'))
                 EVENT_MAP.(event) = 1;
            elseif( strcmpi(task_state_config.event_mappings.(event), 'f'))
                 EVENT_MAP.(event) = 0;
            end
        end
    end

    switch( upper(task_state_config.manual_proceed))
        case '-'  % means not configured for manual proceed, so do not add any mapping
        case 'A'  % means manual proceed allowed, so add a mapping for it
			EVENT_MAP.PROCEED_TO_NextState = 1;
        case 'R'  % means manual proceed REQUIRED, so replace all other mappings
			EVENT_MAP = struct();
			EVENT_MAP.PROCEED_TO_NextState = 1;
		otherwise
            error( 'Invalid value for task_state_config.manual_proceed');
    end

    switch( upper(task_state_config.manual_cancel))
        case '-'  % means not configured for manual cancel, so do not add any mapping
		case 'A'  % means manual cancel allowed, so add a mapping for it
			EVENT_MAP.PROCEED_TO_Failure = 0;
		otherwise
            error( 'Invalid value for task_state_config.manual_cancel');
    end

    % in case 'r' was specified, we need to handle 'PAUSE_EXPERIMENT' as a special case
    for i = 1 : length(events)
        event = events{i};
        if strcmp(event, 'PAUSE_EXPERIMENT')
            if ( strcmpi(task_state_config.event_mappings.(event), 's'))
                 EVENT_MAP.(event) = 1;
            elseif( strcmpi(task_state_config.event_mappings.(event), 'f'))
                 EVENT_MAP.(event) = 0;
            end
        end
    end


    if ( ~isempty(fieldnames(EVENT_MAP)))
    	EVENT_MAP.XM_ABORT_SESSION = 0;
    end


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [outcome, next_state] = HandleTaskStateEnded( id, rcv_event, task_state_config)

    global XM;
	global EVENT_MAP;
    global DF;

    next_state = 0;

    if (isempty(rcv_event))
        return;
    end

	%fprintf('\n[HandleTaskStateEnded]: %i %s %i\n', id, rcv_event.msg_type, EVENT_MAP.(rcv_event.msg_type));

    EVENT_MAP.JV_TIMED_OUT      = task_state_config.timed_out_conseq;
    EVENT_MAP.JV_THRESHOLD      = 1;
    EVENT_MAP.JV_THRESHOLD_FAIL = 0;
    EVENT_MAP.JV_IDLE_TIMEOUT   = 0;
    if (strcmp(rcv_event.msg_type, 'JUDGE_VERDICT'))
        %fprintf('JV: %s\n', rcv_event.data.reason);
        rcv_event.msg_type = sprintf('JV_%s', rcv_event.data.reason);
    end

    msg = DF.MDF.END_TASK_STATE;
    msg.id = int32(id);
    msg.outcome = int32(EVENT_MAP.(rcv_event.msg_type));
    text = rcv_event.msg_type;
    msg.reason = [int8(str2num(sprintf('%d ', text))) zeros(1, 64-length(text))];
    SendMessage( 'END_TASK_STATE', msg);

	% if task state failed and denso was moving, halt it immediately
    if( XM.config.enable_denso && task_state_config.use_denso )
		if (EVENT_MAP.(rcv_event.msg_type) == 0)
			if ~strcmp(task_state_config.present_target, '-')
				HaltDenso( );
			end
		end
	end

    task_state_config.reward = [];
    if isfield(task_state_config, 'reward')
        [task_state_config.reward, valid] = CalculateReward(task_state_config.reward);
        if ~valid, fprintf('WARNING: task_state_config.reward is invalid!\n'); end
    end

    task_state_config.consolation = [];
    if isfield(task_state_config, 'consolation')
        [task_state_config.consolation, valid] = CalculateReward(task_state_config.consolation);
        if ~valid, fprintf('WARNING: task_state_config.consolation is invalid!\n'); end
    end

    switch(EVENT_MAP.(rcv_event.msg_type))
        case 0  % failed
            outcome = 0;
            if (XM.runtime.cancel_button_pressed == 1) || strcmpi(rcv_event.msg_type, 'JV_IDLE_TIMEOUT')
                FailedToStart_state();
            else
                XM.penalty_time = task_state_config.time_penalty;

                % Implement a per task state consolation reward
                if task_state_config.consolation
                    GiveReward( task_state_config.consolation);
                end

                if( XM.trial_started)
                    Failed_state();
                else
                    FailedToStart_state();
                end

                if isfield(task_state_config, 'play_sound') && ...
                   (strcmpi(task_state_config.play_sound, 'f') || strcmpi(task_state_config.play_sound, 'sf') )
                    msg = DF.MDF.PLAY_SOUND;
                    msg.id = int32(1);
                    SendMessage( 'PLAY_SOUND',msg);
                end
            end
            next_state = SkipToTaskEndState();

        case 1  % success/completion
            outcome = 1;

            % A trial is considered to begin for real when we succeed in a task state
            % that has been marked "trial_begins"
            if( task_state_config.trial_begins)
                if( ~XM.trial_started)
                    XM.trial_started = true;
                    fprintf('\n Trial started\n');
                end
            end

            % A trial is considered complete after we complete the task state that
            % has been configured as "trial_complete"
            if( task_state_config.trial_complete)
                fprintf('\n Trial complete\n');
                Success_state();
            end

            % Implement a per task state reward
            if task_state_config.reward
                GiveReward( task_state_config.reward);
            end
            
            if isfield(task_state_config, 'play_sound') && ...
               (strcmpi(task_state_config.play_sound, 's') || strcmpi(task_state_config.play_sound, 'sf') )
                msg = DF.MDF.PLAY_SOUND;
                msg.id = int32(2);
                SendMessage( 'PLAY_SOUND',msg);
            end
    end


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function idx = SkipToTaskEndState()
    global XM;
    idx = find(XM.config.task_state_config.task_end_state == 1, 1, 'first');

