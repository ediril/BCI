% (nonlinear) transformation from the state to the regressor
%
% change this file to design the tuning function 
%
% <input>
% x[1,d]: state such as the hand velocity (d: state dimension)
% <output>
% z[1,zdim]: regressor. 
% 
% Note that the log firing rate is assumed to have the following form,
%   log(firing rate) = theta_0 + theta_1z_1 + ... + theta_mz_m
%
function z = regressor( x)

    z=x;
