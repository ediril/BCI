% Simplified LGF implementation based on old MatlabEM.  Link function is always
% exp, model is always poisson.
%
% one-step filtering
% <input>
% fx0[1,d]: filtered state of previous time-step. (d: state dimension)
% fV0[d,d]: filtered covariance of previous time-step.
% y[1,N]: current spike count observation. (N: number of cells)
% dt: time bin
% var, F, prefdirs, baseline: from param.lgf
% <output>
% fx1[1,d], fV1[d,d]: filtered state and covariance of current time-step. (should be
% used for estimation)
%
function [fx1,fV1] = filter_1step(fx0,fV0,y,dt,var,F,prefdirs,baseline,regressor_func)

maxstep = 3; % a few (even one) iteration may be enough in practice  
eps = 0.0001; % precision for Newton's method <-- Bad!!!! hardcoded absolute value will be inappropriate when scale of inputs changes. MV

dim = length(fx0);
Q = var;

% one step prediction
px1=fx0*F';
pV1=F*fV0*F'+Q;
%Why does Q change to ident
%Why does F change at all, should be static transition matrix

% one step filtering
step=0; err=eps*10;
x0=px1; 

while step<maxstep && err>eps
    J = jacobian(x0,regressor_func);
    bt= J*prefdirs;
    h = baseline+regressor_func(x0)*prefdirs;
    a = exp(h)*dt;
    dl=(y-a)*bt'-(x0-px1)*(pV1^-1)';
    F = repmat(a,dim,1).*bt*bt';
    fV1 = (F+pV1^-1)^-1;
    fx1 = x0 + dl*fV1';
    err = sum(abs(x0-fx1))/dim;
    x0=fx1;
    step=step+1;
end;


%%%%%%%%%%%%%%%%%%%%%%%
% numerical Jacobian
function J = jacobian(x,regressor_func)

h = 0.0001; % precision of numerical calc. <-- Bad!!!! hardcoded absolute value will be inappropriate when scale of inputs changes. MV
d = length(x);

z = regressor_func(x);
m = length(z);
J = zeros(d,m);
for i=1:d
    dx=zeros(1,d); dx(i)=h;
    zz = regressor_func(x+dx);
    J(i,:) = (zz-z)/h;
end
