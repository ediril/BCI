% SimpleJudge
%
% This module judges whether a task event has occurred
% on an instantanous basis, such as whether the target has been
% achieved.
%
% A note about UNITS: This module works with angles in radians
% internally.

function SimpleJudge(config_file, mm_ip)

    dbstop if error;

    global DF;

    DragonflyPath = getenv('DRAGONFLY');
    SourcePath = getenv('BCI_MODULES');
	CommonPath = getenv('BCI_COMMON');
    IncludePath = getenv('BCI_INCLUDE');

    addpath([DragonflyPath '/lang/matlab']);
	addpath([CommonPath '/matlab']);

    DragonflyConfigFile = [IncludePath '/Dragonfly_config.mat'];
    ConnectArgs = {'TASK_JUDGE', '', DragonflyConfigFile};
    if exist('mm_ip','var') && ~isempty(mm_ip)
        ConnectArgs{end+1} = ['-server_name ' mm_ip];
    end
    ConnectToMMM(ConnectArgs{:})

	Subscribe SAMPLE_GENERATED
    Subscribe TASK_STATE_CONFIG
    Subscribe ROBOT_CONTROL_SPACE_ACTUAL_STATE
    Subscribe GROBOT_SEGMENT_PERCEPTS
    Subscribe IDLE
    Subscribe EXIT
    Subscribe PING

    State = InitJudge();

    IdleState = 0;

    disp('SimpleJudge running...');

    while(1)
        M = ReadMessage( 1);
        if(isempty(M))
            %fprintf('.')
        else
			switch( M.msg_type)

                case 'IDLE'
                    IdleState = M.data.idle;

				case 'SAMPLE_GENERATED'
					if( ~State.event_occurred && ~isempty(State.trial_config))
                        timestep = M.data.sample_header.DeltaTime * 1000;

                        if ~isnan(State.trial_config.idle_timeout) && (IdleState == 1)
                            State.trial_config.idle_timeout = State.trial_config.idle_timeout - timestep;
                        else
                            State.trial_config.timeout = State.trial_config.timeout - timestep;
                        end

                        if (State.trial_config.idle_timeout <= 0)
                            msg = DF.MDF.JUDGE_VERDICT;
                            msg.id = State.trial_config.id;
                            text = 'IDLE_TIMEOUT';
                            msg.reason = [int8(str2num(sprintf('%d ', text))) zeros(1, 64-length(text))];
                            SendMessage( 'JUDGE_VERDICT', msg);
                            State = ResetState(State);
                            fprintf('%s\n', text);

                        elseif (State.trial_config.timeout <= 0)
                            msg = DF.MDF.JUDGE_VERDICT;
                            msg.id = State.trial_config.id;
                            text = 'TIMED_OUT';
                            msg.reason = [int8(str2num(sprintf('%d ', text))) zeros(1, 64-length(text))];
                            SendMessage( 'JUDGE_VERDICT', msg);
                            State = ResetState(State);
                            fprintf('%s\n', text);
                        end
                    end

				case 'TASK_STATE_CONFIG'
					State.trial_config = M.data;
					State.event_occurred = false;
 					fprintf('\nC(%i,tout=%.0f)\n', M.data.id, M.data.timeout);

                case 'GROBOT_SEGMENT_PERCEPTS'
                    %if( ~State.event_occurred && ~isempty(State.trial_config) )
                        State.fdbk.percepts = [M.data.ind_force M.data.mid_force M.data.rng_force M.data.lit_force M.data.thb_force];
                    %end

				case 'ROBOT_CONTROL_SPACE_ACTUAL_STATE'
                    if( ~State.event_occurred && ~isempty(State.trial_config) )
                        State.fdbk.actual_pos = M.data.pos;
                        cori_matrix = reshape( M.data.CoriMatrix, [3 3])';
                        State.fdbk.actual_cori = cori_matrix;
                        State = UpdateInternalState( State);
                        State = JudgeWhetherEventOccurred( State);
                    end

                case 'PING'
                    RespondToPing(M, 'SimpleJudge');

                case 'EXIT'
                    if (M.dest_mod_id == GetModuleID()) || (M.dest_mod_id == 0)
                        SendSignal EXIT_ACK
                        break;
                    end

			end
        end
    end
    DisconnectFromMMM
    exit


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function State = ResetState(State)
    State.event_occurred = true;
    State.trial_config = [];
    State.calc = [];
    State.fdbk = [];
    State.fdbk.percepts = zeros(1,15);


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function State = InitJudge()
    State = struct();
    State = ResetState(State);

    % finger_threshold_judging_method:
    % 1=distance (default), 2=absolute
    State.ftjm = {'finger_target_distance', 'finger_target_absolute'};

    % threshold_judging_polarity:
    % 1=target less than threshold [<] (default)
    % 2=target greater than threshold [>]
    State.tjp = {'less_than', 'greater_than'};

    State.config = [];

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function State = JudgeWhetherEventOccurred( State)

    global DF;

    reason = [];

    finger_dofs_to_judge = find(~isnan(State.trial_config.finger_threshold)>0);
    finger_disp_to_judge = [];
    for d = 1 : length(finger_dofs_to_judge)
        ii = finger_dofs_to_judge(d);
        judging_method = State.ftjm{State.trial_config.finger_threshold_judging_method(ii)};
        finger_disp_to_judge(d) = State.calc.(judging_method)(ii);
    end

    num_thresholds = 2 + length(finger_dofs_to_judge); % trans + ori + fingers

    targets = [ State.calc.trans_target_distance ...
                State.calc.ori_target_diff_angle ...
                finger_disp_to_judge ];

    %
    % Judging success
    %
	judge_s = zeros(1, num_thresholds);
    ignore_s = logical(judge_s);

    thresh_s = [State.trial_config.trans_threshold ...
                State.trial_config.ori_threshold ...
                State.trial_config.finger_threshold(finger_dofs_to_judge) ];

    judging_s_polarity = {State.tjp{State.trial_config.trans_threshold_judging_polarity}, ...
                          State.tjp{State.trial_config.ori_threshold_judging_polarity}, ...
                          State.tjp{State.trial_config.finger_threshold_judging_polarity(finger_dofs_to_judge)} };

    for j = 1 : num_thresholds
        fh = str2func(judging_s_polarity{j});
		if (isnan(thresh_s(j)))
            judge_s(j) = 1;
            ignore_s(j) = 1;
		elseif ( fh(targets(j), thresh_s(j)) )
			judge_s(j) = 1;
		else
			judge_s(j) = 0;
		end
	end

    % do we have at least one dimension to judge?
    if (sum(ignore_s) ~= num_thresholds)
        judge_s(ignore_s) = 0;
        num_judged = length(find(ignore_s == 0));

        if (sum(judge_s) == num_judged)
            reason = 'THRESHOLD';
        end
    end


    %
    % Judging failure
    %
    judge_f = zeros(1, num_thresholds);
    ignore_f = logical(judge_f);
    thresh_f = [State.trial_config.trans_threshold_f ...
                State.trial_config.ori_threshold_f ...
                nan(1, num_thresholds-2)];

    f_polarity_fill = repmat({'less_than'}, 1, num_thresholds-2);
    judging_f_polarity = {State.tjp{State.trial_config.trans_threshold_f_judging_polarity}, ...
                          State.tjp{State.trial_config.ori_threshold_f_judging_polarity}, ...
                          f_polarity_fill{:}};

    for j = 1 : num_thresholds
        fh = str2func(judging_f_polarity{j});
        if isnan(thresh_f(j))
            ignore_f(j) = 1;
        else
            judge_f(j) = fh(targets(j), thresh_f(j));
        end
    end

    % do we have at least one dimension to judge?
    if (sum(ignore_f) ~= num_thresholds)
        if any(judge_f)
            reason = 'THRESHOLD_FAIL';
        end
    end

    % display info
    res = repmat({''}, 1, num_thresholds);
    iii = find(ignore_s==0);
    suc_ = find(judge_s(iii)>0);
    suc = iii(suc_);
    pol.less_than = '<';
    pol.greater_than = '>';
    if ~isempty(suc), res(suc) = repmat({'S'}, 1, length(suc));  end
    jjj = find(ignore_s==1 & ignore_f==1);
    res(jjj) = repmat({'-'}, 1, length(jjj));
    fprintf('\n-------------------------------\n');
    fprintf('dist     =>   '); fprintf(' %-7.3f   ', targets);  fprintf('\n');

    fprintf('thresh_s =>   ');
    for i = 1 : num_thresholds
        s_polarity = pol.(judging_s_polarity{i});
        if ignore_s(i), s_polarity = ' '; end
        fprintf('%s%-7.3f   ', s_polarity, thresh_s(i));
    end;

    fprintf('\nthresh_f =>   ');
    for i = 1 : num_thresholds
        f_polarity = pol.(judging_f_polarity{i});
        if ignore_f(i), f_polarity = ' '; end
        fprintf('%s%-7.3f   ', f_polarity, thresh_f(i));
    end;

    fprintf('\njudging  =>   ');
    for i = 1 : num_thresholds, fprintf('    %s     ', res{i});   end;
    fprintf('\nverdict  =>   %s\n', reason);

    fprintf('\nTO: %.0f  ', State.trial_config.timeout);
    fprintf('IDTO: %.0f\n\n', State.trial_config.idle_timeout);


    % Inform XM if judging is done
    if ~isempty( reason)
        msg = DF.MDF.JUDGE_VERDICT;
        msg.id = State.trial_config.id;
        msg.reason(1:length(reason)) = int8(reason);
        SendMessage( 'JUDGE_VERDICT', msg);

        State = ResetState(State);

        fprintf('%s\n', reason);
    end



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function res = less_than(target, threshold)
    res = target < threshold;


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function res = greater_than(target, threshold)
    res = target > threshold;
