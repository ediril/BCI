function matrix = make_xrot_mat( theta_rad)

% matrix = make_xrot_mat( theta)
%
% Makes a 3x3 rotation matrix for rotating around the X axis by theta 
% radians.

S = sin( theta_rad);
C = cos( theta_rad);
matrix = [
    1   0   0;
    0   C  -S;
    0   S   C;
    ];
