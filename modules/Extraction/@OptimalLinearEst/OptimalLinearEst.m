function this = OptimalLinearEst( Config)

this.Members.Config = struct();

% Instantiate a PopulationVector object
this = class( this, 'OptimalLinearEst');

if( exist( 'Config', 'var'))
    this = SetConfig( this, Config);
end
