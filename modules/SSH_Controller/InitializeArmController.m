function c = InitializeArmController( config)


    % Transformations to map from command space to robot space and vice
    % versa

    % The two relevant changes are:
    % (1) a shift in zero orientation caused by the 25deg rotation,
    % (2) changing the axes: x->-x, y<->z
    %
    % In the following notation (consistent with OutputFeedback module):
    %   c    => current position
    %   0    => origin
    %   a    => APL co-ordinate space
    %   p    => Pittsburgh co-ordinate space
    %   h    => some arbitrary vector that orients with the hand,
    %             with the APL zero orientation
    %   g    => same arbitrary vector as h, with Pittsburgh zero orientation
    %   R_a  => cori transformation matrix provided by APL FEEDBACK
    %   R_p  => the desired cori transformation matrix in Pittsburgh space
    %   S_p  => swivel rotation, angle of arm mount as a positive rotation about Pittsburgh z axis
    %   P_pa  => permutation of the axes, from Pittsburgh space to APL space
    %   T_pa => transformation (swivel and permutation) matrix from Pittsburgh to APL space

    c = struct();

%    P_pa = config.xyzmap; % Permuting matrix
%    c.S_p = make_zrot_mat( deg2rad( config.ztheta)); % Arm mount swivel transform
%    c.T_pa = P_pa * c.S_p'; % Transform from Pitt to APL coordinates
%    c.T_ap = c.T_pa';       % Transform from APL to Pitt coordinates

    c.OriTrMat = config.orient_transform;
    c.TrFrame = config.trans_frame;
    c.OriFrame = config.orient_frame;


    % Initialize the stuff for converting raw joint angle feedback into
    % endpoint position/velocity and orientation
    c.feedback_processor = InitializeFeedbackProcessor();
