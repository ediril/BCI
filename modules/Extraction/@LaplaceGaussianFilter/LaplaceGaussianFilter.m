function this = LaplaceGaussianFilter( Config)

% LGF = LaplaceGaussianFilter( TF, Config)
%
% Constructs a Laplace-Gaussian Filter decoder object. In the underlysing belly of the beast it uses
% Shinsuke Koyama's LGF implementation. Config is a struct that contains configuration parameters:
% TuningFunctions - the output from one of the tuning function estimators
% InitialState - Initial state of the process (Px1)


% Meel Velliste 6/15/2010

this.Members.Config = struct();

% Instantiate a PopulationVector object
this = class( this, 'LaplaceGaussianFilter');

if( exist( 'Config', 'var'))
    this = SetConfig( this, Config);
end
