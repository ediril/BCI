function KF = KalmanFilter( M, N, Config)

% KF = KalmanFilter( M, N, Config)
%
% Constructs a KalmanFilter object with number of measurement dimensions M
% and number of process dimensions N. Config is a struct that contains
% configuration parameters:
% InitialState - Initial state of the process (Nx1)
% ProcessErrorCov - Initial value of process error covariance (NxN)
% GenMatrix - Generating matrix, i.e. one that produces the expected value
%             of measurement given a process state (MxN)
% StateTrans - State transition matrix, specifying how state evolves from 
%              one time-step to the next (NxN)
% ProcessCov - Covariance of the process state (NxN)
% MeasurementCov - Covariance of measurement residuals (i.e. of
%                  measurements with the expected value subtracted) (MxM)

% Meel Velliste 9/18/2009

if( ~exist( 'Config', 'var')), Config.dummy = []; end

% Assign initial value of process state estimate
if( isfield( Config, 'InitialState'))
    Size = size( Config.InitialState);
    if( length( Size) > 2 || Size(1) ~= N || Size(2) ~= 1), error( 'Config.InitialState should be an Nx1 matrix'); end
    KF.x = Config.InitialState;
else
    KF.x = zeros( N, 1);
end

% Assign initial value of process error covariance
if( isfield( Config, 'ProcessErrorCov'))
    Size = size( Config.ProcessErrorCov);
    if( length( Size) > 2 || Size(1) ~= N || Size(2) ~= N), error( 'Config.ProcessErrorCov should be an NxN matrix'); end
    KF.P = Config.ProcessErrorCov;
else
    KF.P = zeros( N, N);
end

% Assign initial value of generative model matrix
if( isfield( Config, 'GenMatrix'))
    Size = size( Config.GenMatrix);
    if( length( Size) > 2 || Size(1) ~= M || Size(2) ~= N), error( 'Config.GenMatrix should be an MxN matrix'); end
    KF.H = Config.GenMatrix;
else
    KF.H = zeros( M, N);
end


% Assign initial value of state transition matrix
if( isfield( Config, 'StateTrans'))
    Size = size( Config.StateTrans);
    if( length( Size) > 2 || Size(1) ~= N || Size(2) ~= N), error( 'Config.StateTrans should be an NxN matrix'); end
    KF.A = Config.StateTrans;
else
    KF.A = eye( N);
end

% Assign process co-variance
if( isfield( Config, 'ProcessCov'))
    Size = size( Config.ProcessCov);
    if( length( Size) > 2 || Size(1) ~= N || Size(2) ~= N), error( 'Config.ProcessCov should be an NxN matrix'); end
    KF.Q = Config.ProcessCov;
else
    KF.Q = eye( N);
end

% Assign measurement residual co-variance
if( isfield( Config, 'MeasurementCov'))
    Size = size( Config.MeasurementCov);
    if( length( Size) > 2 || Size(1) ~= M || Size(2) ~= M), error( 'Config.MeasurementCov should be an MxM matrix'); end
    KF.R = Config.MeasurementCov;
else
    KF.R = eye( M);
end

% Initialize Kalman gain to zero
KF.K = zeros( N, M);

% Instantiate a KalmanFilter object
KF = class( KF, 'KalmanFilter');
