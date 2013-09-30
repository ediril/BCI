function [c, Vc_transl_robot, Vc_orient_robot, ...
    Pf_transl, Pf_orient, Vf_transl, Vf_orient, Pf_R] = ...
    EvaluateArmControlLaw( c, Vc_transl, Vc_orient, Pf_arm, output_offsets, dt)

    Pf_R = reshape( Pf_arm.R, [3 3])';
    Pf_R = Pf_R * c.OriTrMat;
    Pf_arm.R = Pf_R;

    [c.feedback_processor, ep_pos, ep_vel] = ProcessFeedback( c.feedback_processor, Pf_arm, dt);

    Vc_transl_robot = Vc_transl;

    % if local command, do L->G transform
    if strcmpi(c.TrFrame, 'local')
        Vc_transl_robot = Pf_R * Vc_transl';
    end

	% Secret sauce transform to go from command space to robot space
	Vc_orient_robot = Vc_orient * c.OriTrMat;

    % if global command, do G->L transform
    if strcmpi(c.OriFrame, 'global')
        Vc_orient_robot = Pf_R' * Vc_orient_robot';
    end

    % Transform feedback from Robot Coordinate space to Control Space
    Pf_transl = ep_pos(1:3); %c.T_ap * ep_pos(1:3);
    Vf_transl = ep_vel(1:3); %c.T_ap * ep_vel(1:3);
    Vf_orient = ep_vel(4:6); %c.T_ap * ep_vel(4:6);

    %Pf_orient = zeros(3,1);
    [rotaxis, rotangle] = rotmat2rotvec(Pf_R);
    Pf_orient = rotangle * rotaxis;

    %Pf_R = c.T_ap * R * c.T_pa * c.S_p;

%    % add offsets
%    Pf_transl = Pf_transl - output_offsets.transl_offset';

