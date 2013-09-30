% SimpleMonkey
%
% This module generates an "ideal" movement command
% on an instantanous basis.
%
% A note about UNITS: This module works with angles in radians
% internally.

function SimpleMonkey(config_file, mm_ip)

    dbstop if error;

    global DF;

    DragonflyPath = getenv('DRAGONFLY');
    SourcePath = getenv('BCI_MODULES');
	CommonPath = getenv('BCI_COMMON');
    IncludePath = getenv('BCI_INCLUDE');

    addpath([DragonflyPath '/lang/matlab']);
	addpath([CommonPath '/matlab']);

    DFConfigFile = [IncludePath '/Dragonfly_config.mat'];
    ConnectArgs = {'SILICON_MONKEY', '', DFConfigFile};
    if exist('mm_ip','var') && ~isempty(mm_ip)
        ConnectArgs{end+1} = ['-server_name ' mm_ip];
    end
    ConnectToMMM(ConnectArgs{:})

    config = LoadModuleConfigFile(config_file);

    Subscribe SAMPLE_GENERATED
    Subscribe ROBOT_CONTROL_SPACE_ACTUAL_STATE
    Subscribe(config.control_msg)   %ROBOT_CONTROL_CONFIG
    Subscribe RELOAD_CONFIGURATION
    Subscribe EXIT
    Subscribe PING

    Tag = 'silicon_monkey';
    State = InitMonkey( );
    State.config = config;

    disp('SimpleMonkey running...');

    while(1)
        M = ReadMessage( 1);
        if(isempty(M))
            %fprintf('.')
        else
            % Perform message processing specific to SimpleMonkey
            switch( M.msg_type)
                case 'SAMPLE_GENERATED'
                    SampleHeader = M.data.sample_header;
                    State = UpdateMonkeyCommand( State, SampleHeader);
                    SendPlannerMovementCommand( State.command_vel, SampleHeader, Tag, State.config.controlled_dims);
                    SendPlannerState( State, SampleHeader);
                    %fprintf('S');

                case State.config.control_msg     % 'ROBOT_CONTROL_CONFIG'
					State.trial_config = M.data;

                    % add in zeros for percept data
                    State.trial_config.target = [State.trial_config.target zeros(1,15)];

                    % When new target received, then reset movement phase
                    State.movement_phase = '';
                    fprintf(' C ');

				case 'ROBOT_CONTROL_SPACE_ACTUAL_STATE'
					State.fdbk.actual_pos = M.data.pos;
					cori_matrix = reshape( M.data.CoriMatrix, [3 3])';
					State.fdbk.actual_cori = cori_matrix;
                    %fprintf(' F ');

                case 'RELOAD_CONFIGURATION'
                    % We might want to implement reloading on the fly
                    config = LoadModuleConfigFile(config_file);
                    if ~isempty(config)
                        State.config = config;
                    end

                case 'PING'
                    RespondToPing(M, 'SimpleMonkey');

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
function State = InitMonkey( State)
    State = struct();
	State.trial_config = [];
	State.calc = [];
	State.fdbk = [];

    State.ErrorBuffer = [];

    State.fdbk.actual_pos = nan(1,18);
    State.fdbk.actual_cori = nan(3,3);
    State.fdbk.percepts = zeros(1,15);

    State.trial_config.target = nan(1,18); %[-.20  0 -.30 0 0 0 0 zeros(1,11)];
    State.calc.trans_target_distance = 0;
    State.calc.trans_target_direction = [0 0 0];
    State.calc.ori_target_diff_angle = 0;
    State.calc.ori_target_rot_axis = [0 0 0];
    State.calc.finger_target_displacement = [0 0 0 0 0 0 0 0 0];

    State.command_vel = zeros(1,18);
    State.trans_cmd_vel = zeros(1,3);
    State.ori_cmd_vel = zeros(1,3);
    State.finger_cmd_vel = zeros(1,10);
    State.finger_err = zeros(1,10);
    State.movement_phase = '';


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function State = UpdateMonkeyCommand( State, SampleHeader)

    % Don't move if target or current state are unknown
    if( any( isnan( State.fdbk.actual_pos(1:3))) || any( isnan( State.fdbk.actual_cori(:))))
        State.command_vel(:) = 0;
        return
    end

    if( any( isnan( State.trial_config.target)))
        State.command_vel(:) = 0;
        return
    end

    State = UpdateInternalState( State);

    %%%
    %%% TRANSLATION
    %%%
    % Move toward target with a smooth speed profile
    param.acceleration = State.config.translation.acceleration; % m/s/s
    param.max_speed    = State.config.translation.max_speed; % m/s
    param.deceleration = State.config.translation.deceleration; % m/s/s
    param.dt           = SampleHeader.DeltaTime; % s
    param.precision    = .010; % m
    if isfield(State.config.translation, 'precision'), param.precision = State.config.translation.precision; end

    [State.trans_cmd_vel, State.movement_phase] = CalculateCommandVelocity( ...
        State.calc.trans_target_direction, ...
        State.calc.trans_target_distance, ...
        State.trans_cmd_vel, ...
        State.movement_phase, ...
        param);

    %%%
    %%% ORIENTATION
    %%%
    ori_speed_factor = 2.;
    ori_precision = 1*pi/180;
    if isfield(State.config.orientation, 'precision'), ori_precision = State.config.orientation.precision * pi/180; end
    if isfield(State.config.orientation, 'speed_factor'), ori_speed_factor = State.config.orientation.speed_factor; end

    fprintf('ori angle %.1f\n', State.calc.ori_target_diff_angle * 180 / pi);
    if( abs(State.calc.ori_target_diff_angle)>ori_precision)
        ori_cmd_speed = ori_speed_factor * State.calc.ori_target_diff_angle;
        State.ori_cmd_vel = ori_cmd_speed * State.calc.ori_target_rot_axis;
    else
        State.ori_cmd_vel = zeros(size(State.calc.ori_target_rot_axis));
    end
    State.ori_cmd_vel

    %%%
    %%% FINGERS
    %%%
    % Move toward target joint angles with a speed proportional to
    % distance from target
    P  = State.config.hand.pid_gains.P;
    KI = State.config.hand.pid_gains.I;
    err = State.calc.finger_target_displacement(1:10); % leave out percepts

    % filter the error to smooth it out
    [State, err] = FilterError(State, err);
    State.finger_cmd_vel = P * err;

    State.command_vel = [State.trans_cmd_vel 0 State.ori_cmd_vel 0 State.finger_cmd_vel];


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [State, FilteredError] = FilterError(State, Error)

    State = AddToErrorBuffer(State, Error');

    FilteredError = State.ErrorBuffer * State.config.hand.FilterCoeffs';

    FilteredError = FilteredError';


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function State = AddToErrorBuffer(State, Error)

    if isempty(State.ErrorBuffer)
        State.ErrorBuffer = repmat(Error, [1 length(State.config.hand.FilterCoeffs)]);
    else
        State.ErrorBuffer(:,1) = [];
        State.ErrorBuffer(:,end+1) = Error;
    end



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function SendPlannerMovementCommand( Vel, SampleHeader, Tag, controlled_dims)

    global DF;
    msg = DF.MDF.PLANNER_MOVEMENT_COMMAND;

    cdims = logical( controlled_dims);
    if( length(cdims) ~= length( msg.controlledDims))
        error('controlled_dims field of the config needs to be the same length as the one in the MOVEMENT_COMMAND message definition');
    end
    Vel(~cdims(1:length(Vel))) = 0;

    msg.sample_header = SampleHeader;
    msg.tag(1:length(Tag)) = Tag;
    msg.vel(1:length(Vel)) = Vel;
    msg.controlledDims(:) = cdims;
    SendMessage( 'PLANNER_MOVEMENT_COMMAND', msg);


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function SendPlannerState( State, SampleHeader)

    global DF;
    msg = DF.MDF.PLANNER_STATE;
    msg.sample_header = SampleHeader;
    msg.targetPos = State.trial_config.target(1:18); % leave out percepts
    SendMessage( 'PLANNER_STATE', msg);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [CmdVel, MovementPhase] = CalculateCommandVelocity( ...
               TargetDir, TargetDist, PrevCmdVel, PrevMovementPhase, Param)

    % If we are within precision limit of target, then output zero
    % velocity to avoid oscillation at target
    disp(['TargetDist = ' sprintf('%.3f', TargetDist)]);
    if( TargetDist <= Param.precision)
        fprintf('\nAT TARGET\n')
        CmdVel = zeros( size( PrevCmdVel));
        MovementPhase = 'slowing_down';
        return;
    end

    % If we are already slowing down, then do not change. Otherwise
    % evaluate whether to change phase

            % First calculate if we are close enough to target that we
            % should slow down
            velocity_projection_to_target_direction = dot( PrevCmdVel, TargetDir);
            if( velocity_projection_to_target_direction <= 0)
                % We are currently going away from target, so no need to
                % decelerate, instead we will need to accelerate toward target
                fprintf('\nHEADING AWAY FROM TARGET\n');
                MovementPhase = 'speeding_up';
            else
                % We are going toward target, so look at how long it would
                % take to get there
                current_speed = velocity_projection_to_target_direction;
                time_to_target_at_current_speed = TargetDist / current_speed;
                time_needed_to_slow_down = abs( current_speed / Param.deceleration);
                if( time_needed_to_slow_down >= time_to_target_at_current_speed)
                    MovementPhase = 'slowing_down';
                else
                    MovementPhase = 'speeding_up';
                end
            end

    disp(['MovementPhase = ' MovementPhase]);
    InLinPrevCmd = max(dot(PrevCmdVel,TargetDir),0)*TargetDir
    switch( MovementPhase)
        case 'slowing_down'
            % If we are close to target, then limit the command velocity as
            % dictated by the deceleration parameter, so as to linearly
            % ramp down the speed just in time to stop at the target
            decel_vector = -Param.deceleration * TargetDir;
            vel_increment = decel_vector*Param.dt;
            CmdVel = max(dot((InLinPrevCmd + vel_increment),TargetDir),0)*TargetDir;
        case 'speeding_up'
            % If not close to target, then
            % calculate command speed by updating the previous command
            % velocity at the rate allowed by the acceleration parameter
            accel_vector = Param.acceleration * TargetDir;
            vel_increment = accel_vector * Param.dt;
            CmdVel = InLinPrevCmd + vel_increment;

            % Limit the speed to the max_speed parameter
            cmd_speed = sqrt( sum( CmdVel.^2));
            if( cmd_speed > Param.max_speed)
                cmd_dir = CmdVel / cmd_speed;
                CmdVel = Param.max_speed * cmd_dir;
            end
        otherwise
            error('Unrecognized movement phase name');
    end
    CmdVel

    if any(isnan(CmdVel))
        keyboard;
    end
    