function [KF, ProcessStateEst] = Predict( KF, Measurement, ProcessStateUpdate)

% [KF, ProcessStateEst] = Predict( KF, Measurement, ProcessStateUpdate)
%
% Perform a update/predict step for the KalmanFilter KF. Measurement
% is the observed data for updating the filter. The output ProcessStateEst
% represents the estimated state of the process. ProcessStateUpdate is an
% optional update to the process state when process state is externally changed.

% Meel Velliste 9/18/2009

% Project the state ahead from previous time step through the state
% transition matrix
if( exist( 'ProcessStateUpdate', 'var'))
    x_ = ProcessStateUpdate;
else
    x_ = KF.A * KF.x;
end

% Project the error covariance ahead from previous time step
P_ = KF.A * KF.P * KF.A' + KF.Q;

% Calculate the Kalman gain K
KF.K = P_ * KF.H' * inv( KF.H * P_ * KF.H' + KF.R);

% Update the estimate of current process state based on measurement
z = Measurement;
KF.x = x_ + KF.K * (z - KF.H * x_);
ProcessStateEst = KF.x;

% Update the process error covariance
I = eye( size( P_));
KF.P = (I - KF.K * KF.H) * P_;
