function matrix = make_zrot_mat( theta_rad)

% matrix = make_zrot_mat( theta)
%
% Makes a 3x3 rotation matrix for rotating around the Z axis by theta
% radians

S = sin( theta_rad);
C = cos( theta_rad);
matrix = [
    C  -S   0;
    S   C   0;
    0   0   1;
    ];
