function [C, Pc, Pe, Ve] = Evaluate_EKF_fc( C, Vc, Pc, Pf, dt)

% [C, Pc, Pe, Ve] = Evaluate_EKF_fc( C, Vc, Pc, Pf, dt)
%
% Implements a Kalman Filter velocity/position controller on top of a 
% position-controlled device. It effectively implements two controllers 
% simultaneously:
% 1) A closed-loop position controller to keep the high-DoF output device
%    on a manifold that represents a low-DoF control space
% 2) An open-loop velocity controller in the low-DoF control space, 
%    allowing the device to move at the commanded velocity on the manifold
%
% Considers both desired velocity and feedback position to be noisy
% measurements.
%
% Inputs:
%  C - controller struct
%  Vc - command velocity in low-DoF control space
%  Pc - command position in low-DoF control space (not yet implemented)
%  Pf - feedback position in high-DoF actuator space
%  dt - delta time
%
% Outputs:
%  C - controller struct
%  Pc - command position in high-DoF actuator space
%  Pe - estimated current position in low-DoF space
%  Ve - estimated current velocity in low-DoF space

    %%% Prepare Kalman Filter variables
    Q = C.Q;
    R = C.R;
    Df = C.Df;
    Dc = C.Dc;
    L = Df + 1 + Dc; % L is the length of history we need to keep
    M = C.M;
    N = C.N;
    L2H = C.L2H;
    MM = M + L*M;
    NN = N + L*M;

    F = eye(MM);
    F(1:M,M+(1:M)) = eye(M) * dt;

    if( isfield( C, 'x'))
        x__ = C.x;
        P__ = C.P;
    else
        x__ = [C.P0; repmat( C.V0, [L 1])];
        P__ = zeros( MM);
    end

    if( ~isfield( C, 'Vc_history'))
        C.Vc_history = zeros( M, L);
    end
    C.Vc_history = [C.Vc_history(:,2:end) Vc];
    z = [Pf; C.Vc_history(:)];

    % The equations below are straight from the Extended Kalman Filter Wikipedia page

    %%% Predict
    x_ = F * x__;          % Predicted state estimate
    P_ = F * P__ * F' + Q; % Predicted estimate covariance

    %%% Update
    y = z - h(x_,L2H,M,dt);    % Innovation
    H = jacobian(x_,L2H,M,dt); % Derivative of predicted measurement with respect to x_
    S = H * P_ * H' + R;  % Innovation covariance
    K = P_ * H' * S^-1;   % Kalman gain (optimal for least-squares estimate)
    x = x_ + K * y;       % Updated state estimate
    I = eye(MM);
    P = (I - K * H) * P_; % Updated estimate covariance

    %%% Extract the position command from Kalman prediction
    %%% The command is taken to be the estimated position in the future at
    %%% the control delay Dc
    estimated_pos_at_Df = x(1:M);
    estimated_vels = reshape( x(M+1:end), [M L]);
    estimated_pos_at_Dc = estimated_pos_at_Df + sum( estimated_vels, 2)*dt;
    Pc = L2H.G( estimated_pos_at_Dc, L2H);

    %%% Extract the estimate of current position and velocity
    estimated_pos_at_0 = estimated_pos_at_Df + sum( estimated_vels(:,1:Df+1), 2)*dt;
    estimated_vel_at_0 = estimated_vels(:,Df+1);
    Pe = estimated_pos_at_0;
    Ve = estimated_vel_at_0;
    
    %%% Remember state for next time
    C.x = x;
    C.P = P;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% mapper function for converting a state estimate to measurement space
function z = h( x, L2H, M, dt)

    L = length(x)/M - 1;
    
    % Position elements can be mapped directly
    pos = x(1:M);
    pos2 = L2H.G(pos, L2H);
    vels = reshape( x(M+1:end), [M L]);

    % Velocity elemnts have to be converted to a series of positions
    % relative to first position, then mapped to high-DoF, and then
    % converted back to velocities
    % ACTUALLY, this is only needed if we have feedback velocities in
    % the measurement
%     POS = repmat( pos, [1 L]);
%     poss = POS + cumsum( vels*dt);
%     posss = [pos poss];
%     posss2 = G(posss);
%     vels2 = diff( posss2, 1, 2) / dt;
    
    % Now put the position and velocity elements back together
    z = [pos2; vels(:)];
    
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function J = jacobian(x,L2H,M,dt)

    step_size = 0.00001; % precision of numerical calc. <-- Bad!!!! hardcoded absolute value will be inappropriate when scale of inputs changes. MV
    % You want this to be neither too large, nor too small. Too small runs into
    % numerical accuracy problems in distinguishing x from x+dx, whereas too
    % large means the derivative is not accurate if the function is highly
    % non-linear.


    z = h(x,L2H,M,dt);
    MM = length(x);
    NN = length(z);
    J = zeros(NN,MM);
    for i=1:MM
        dx=zeros(MM,1); dx(i)=step_size;
        zz = h(x+dx,L2H,M,dt);
        J(:,i) = (zz-z)/step_size;
    end
