function [Q, MEAN, STD] = GetQuantity( Data, RawQuantityDescriptor, SampleMask)

% Q = GetQuantity( Data, QuantityDescriptor, SampleMask)
% 
% Gets a specified quantity out of the Data where Data is the standard data
% structure output by the Import*.m scripts and QuantityDescriptor is a
% string that specifies the quantity of interest, e.g. 'avx' for
% x-component of actual velocity or 'cpz' for z-component of command
% position, or 'pc1' for principal component 1 of the neural data. The
% output Q is a 1xN vector of the requested quantity over N sample points.
% If you append a space and a 'z' at the end of the string, it causes
% the output Q to be z-scored,
% (e.g. 'avg z' for actual gripper velocity z-scored). Z-scoring is done
% based on the whole data, not just the part selected by SampleMask.

% Find out if z-scoring requested
DoZScoring = false;
[QuantityDescriptor, remainder] = strtok( RawQuantityDescriptor);
Option1 = strtok( remainder);
if( isequal( Option1, 'z'))
    DoZScoring = true;
end

if( isequal( QuantityDescriptor, 'tim'))
    % If "time" selected, calculate time in seconds relative to each trial beginning
    sample_period = 0.030;
    trial_nos = unique( Data.TrialNo);
    q = nan( size( Data.TrialNo));
    for tn = trial_nos
        trial_mask = Data.TrialNo == tn;
        num_timepoints = sum( trial_mask);
        discrete_time = 0 : num_timepoints-1;
        trial_time = discrete_time * sample_period;
        q(trial_mask) = trial_time;
    end
elseif( isequal( QuantityDescriptor, 'atm'))
    % if "absolute time" selected, calculate time in seconds since first
    % trial
    sample_period = 0.030;
    num_timepoints = length( Data.TrialNo);
    discrete_time = 0 : num_timepoints-1;
    abs_time = discrete_time * sample_period;
    q = abs_time;
elseif( isequal( QuantityDescriptor, 'pro'))
    % if "progress" selected, calculate a progress measure 0..1 for each trial
    trial_nos = unique( Data.TrialNo);
    q = nan( size( Data.TrialNo));
    for tn = trial_nos
        trial_mask = Data.TrialNo == tn;
        num_timepoints = sum( trial_mask);
        trial_progress = linspace( 0, 1, num_timepoints);
        q(trial_mask) = trial_progress;
    end
elseif( isequal( QuantityDescriptor, 'pra'))
    % if "progress aligned" selected, calculate a progress measure 0..1 for each trial
    % with zero starting at the end of InitialHold and 1 at the beginning
    % of TargetHold (negative before InitialHold and greater than 1 after
    % TargetHold)
    trial_nos = unique( Data.TrialNo);
    q = nan( size( Data.TrialNo));
    for tn = trial_nos
        trial_mask = Data.TrialNo == tn;
        AlignBegin_index = find( GetTaskSegmentMask( Data, Data.TaskSegmentCodes.InitialHold, tn, []));
        AlignEnd_index = find( GetTaskSegmentMask( Data, Data.TaskSegmentCodes.TargetHold, tn, []));
        if( isempty( AlignBegin_index) || isempty( AlignEnd_index)), continue; end
        zero_index = AlignBegin_index(end);
        one_index = AlignEnd_index(1);
        num_timepoints = one_index - zero_index + 1;
        middle_trial_progress = linspace( 0, 1, num_timepoints);
        Trial_index = find( trial_mask);
        begin_index = Trial_index(1);
        end_index = Trial_index(end);
        num_early_time_points = zero_index - begin_index;
        num_late_time_points = end_index - one_index;
        step_size = middle_trial_progress(2) - middle_trial_progress(1);
        early_trial_progress = -step_size*num_early_time_points : step_size : -step_size;
        late_trial_progress = 1 + (step_size : step_size : step_size*num_late_time_points);
        trial_progress = [early_trial_progress middle_trial_progress late_trial_progress];
        q(trial_mask) = trial_progress;
    end

elseif( isequal( QuantityDescriptor(1:2), 'pc'))
    % If principal components of neural data requested
    PC_Num = str2double( QuantityDescriptor(3:end));
    q = Data.Traj(PC_Num,:);
else

    % If kinematic quantity requested
    Char = QuantityDescriptor(2);
    switch( Char)
        case 'p', temp = Data.Position;
        case 'v', temp = Data.Velocity;
        otherwise, error( ['Unrecognized character ''' Char ''' in QuantityDescriptor: ''' QuantityDescriptor '''']);
    end
    Char = QuantityDescriptor(1);
    switch( Char)
        case 'a', kin = temp.Actual;
        case 'c', kin = temp.Control;
        case 'd', kin = temp.Decoded;
        case 'p', kin = temp.Planner;
        otherwise, error( ['Unrecognized character ''' Char ''' in QuantityDescriptor: ''' QuantityDescriptor '''']);
    end
    % Get the specific quantity (q) as the basis for binned data
    Char = QuantityDescriptor(3);
    switch( Char)
        case 'x', q = kin(1,:);
        case 'y', q = kin(2,:);
        case 'z', q = kin(3,:);
        case 'v', q = kin(4,:);
        case 'i', q = kin(5,:);
        case 'j', q = kin(6,:);
        case 'k', q = kin(7,:);
        case 'w', q = kin(8,:);
        case 'a', q = kin(9,:);
        case 'b', q = kin(10,:);
        case 'c', q = kin(11,:);
        case 'd', q = kin(12,:);
        otherwise, error( ['Unrecognized character ''' Char ''' in QuantityDescriptor: ''' QuantityDescriptor '''']);
    end
end

MEAN = nanmean( q, 2);
STD = nanstd( q, 0, 2);
if( isempty( SampleMask))
    Q = q;
else
    Q = q(SampleMask);
end

% Perform z-scoring if requested
if( DoZScoring)
    Q = (Q-MEAN)/STD;
end
