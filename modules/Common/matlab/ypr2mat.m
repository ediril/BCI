function matrix = ypr2mat( ypr)

% matrix = ypr2mat( ypr)
%
% converts a yaw-pitch-roll rotation specification to a rotation vector

rx = make_xrot_mat( ypr(1));
ry = make_yrot_mat( ypr(2));
rz = make_zrot_mat( ypr(3));

matrix = rz * ry * rx;