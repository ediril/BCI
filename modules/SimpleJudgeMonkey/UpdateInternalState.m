% State = MJ_UpdateInternalState( State)
%
% Updates the internal state that is common to the SimpleMonkey
% and SimpleJudge, e.g. recalculates its reckoning of distance
% to target, direction to target etc.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function State = UpdateInternalState( State)

    %%%
    %%% TRANSLATION
    %%%
    trans_targ_pos = State.trial_config.target(1:3);
    trans_act_pos = State.fdbk.actual_pos(1:3);
    target_displacement = trans_targ_pos - trans_act_pos;
    target_distance = sqrt( sum( target_displacement.^2));
    target_direction = target_displacement / target_distance;

    State.calc.trans_target_distance = target_distance;
    State.calc.trans_target_direction = target_direction;


    %%%
    %%% ORIENTATION
    %%%
	target_cori_matrix = reshape(State.trial_config.coriMatrix, [3 3])';
    actual_cori_matrix = State.fdbk.actual_cori;
    % These matrices apply to Column vectors
    cori_diff_matrix = target_cori_matrix * actual_cori_matrix';
    [diff_rotaxis, diff_angle] = rotmat2rotvec( cori_diff_matrix);

    State.calc.ori_target_diff_angle = diff_angle;
    State.calc.ori_target_rot_axis = diff_rotaxis;

    if isfield(State.config, 'orientation')
        if isfield(State.config.orientation, 'frame') && ...
           strcmpi(State.config.orientation.frame, 'local')
               % rotate diff_rotaxis to local coordinate frame
               State.calc.ori_target_rot_axis = (actual_cori_matrix' * diff_rotaxis')';
        end
    end

    %%%
    %%% FINGERS
    %%%
    finger_targ_pos = State.trial_config.target(9:end);
    finger_act_pos = [State.fdbk.actual_pos(9:end) State.fdbk.percepts];
    finger_displacement = finger_targ_pos - finger_act_pos;
    State.calc.finger_target_displacement = finger_displacement;
    State.calc.finger_target_distance = abs(finger_displacement);
    State.calc.finger_target_absolute = finger_act_pos;
