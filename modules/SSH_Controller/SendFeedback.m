function SendFeedback(sample_header, Pf_transl, Pf_orient, Pf_hand, Vf_transl, Vf_orient, Vf_hand, Pf_R)

    global RTMA;

    % Assemble position and velocity vectors for output
    reserved = nan;
    elbow_swivel = nan;
    pos_vector = [ Pf_transl(:)', ...
                   reserved, ...
                   Pf_orient(:)', ...
                   elbow_swivel, ...
                   Pf_hand(:)' ];
    
    vel_vector = [ Vf_transl(:)', ...
                   reserved, ...
                   Vf_orient(:)', ...
                   elbow_swivel, ...
                   Vf_hand(:)' ];
    
    % Transpore the orientation matrix, so it would be output in
    % column-major order instead of matlab's default row-major order
    cori_matrix = Pf_R';


    feedback = RTMA.MDF.ROBOT_CONTROL_SPACE_ACTUAL_STATE;
    feedback.sample_header = sample_header;
    feedback.pos(1:length(pos_vector)) = pos_vector;
    feedback.vel(1:length(vel_vector)) = vel_vector;
    feedback.CoriMatrix(:) = cori_matrix(:)';

    SendMessage( 'ROBOT_CONTROL_SPACE_ACTUAL_STATE', feedback); 
