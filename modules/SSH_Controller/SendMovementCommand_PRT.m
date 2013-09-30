function SendMovementCommand_PRT(sample_header, transl_vel, orient_vel, finger_vel)

    global RTMA;

    elbow_swivel = 0;
    vel_cmd_vector = [ transl_vel(:)', 0, ...
                       orient_vel(:)', ...
                       elbow_swivel, ...
                       finger_vel(:)'];

    %pos_cmd_vector = [ 0 0 0 0 0 0 0 0 ...
    %                   finger_pos(:)'];

    command = RTMA.MDF.ROBOT_MOVEMENT_COMMAND;
    command.sample_header = sample_header;
    command.vel(1:length(vel_cmd_vector)) = vel_cmd_vector;
    %command.pos(1:length(pos_cmd_vector)) = pos_cmd_vector;

    SendMessage( 'ROBOT_MOVEMENT_COMMAND', command);
