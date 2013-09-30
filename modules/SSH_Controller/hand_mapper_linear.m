function high = hand_mapper( low, HM)

% high = hand_mapper( low, HM)
%
% Maps from low dof hand shape to high-dof finger joint angles
% low is Mx1 and high is Nx1
%
% HM is a struct containing a field "config"
% where config is a struct containing the field "fmap"
% fmap is a MxN matrix for linear transformation of low -> high
%

M = size( HM.config.fmap, 1); % number of low dofs
N = size( HM.config.fmap, 2); % number of high dofs

if( size( low, 1) ~= M)
    error('hand_mapper(): "low" must be Mx1 or MxS, where "map" is MxN');
end

high = HM.config.fmap' * low + HM.config.foff';
