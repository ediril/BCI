function matrix = make_yrot_mat( theta_rad)

% matrix = make_yrot_mat( theta)
%
% Makes a 3x3 rotation matrix for rotating around the Y axis by theta
% radians.

S = sin( theta_rad);
C = cos( theta_rad);
matrix = [
    C   0   S;
    0   1   0;
   -S   0   C;
    ];
