function this = PopulationVector( Config)

% PV = PopulationVector( TF, Config)
%
% Constructs a PopulationVector decoder object. Config is a struct that contains configuration parameters:
% TuningFunctions - the output from one of the tuning function estimators
% InitialState - Initial state of the process (Px1)
% Gain - (Px1) output gain

% Meel Velliste 9/18/2009

this.Members.Config = struct();

% Instantiate a PopulationVector object
this = class( this, 'PopulationVector');

if( exist( 'Config', 'var'))
    this = SetConfig( this, Config);
end
