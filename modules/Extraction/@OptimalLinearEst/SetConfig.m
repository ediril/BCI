function this = SetConfig( this, varargin)

% PV = SetConfig( PV, Config)
% PV = SetConfig( PV, PropertyName1, PropertyValue1, PropertyName2, PropertyValue2, ...)
%
% If a Config struct is provided, then replaces the entire config with
% that. If Value/Property pairs are provided, then adds those to the
% existing config.

% Set the config
nargs = length( varargin);
if( nargs == 1)
    this.Members.Config = varargin{1};
else
    for i = 1 : 2 : nargs
        prop_name = varargin{i};
        prop_value = varargin{i+1};
        this.Members.Config.(prop_name) = prop_value;
    end
end

% Recalculate member variables based on new config
if( isfield( this.Members.Config, 'Gain'))
    gain_idx = this.Members.Config.Gain ~= 0;
    this.Members.Gain = this.Members.Config.Gain(gain_idx);
else
    %this.Members.Gain = 1;
    disp ('Warning: Invalid Gain option, keeping the old value')
end
if( isfield( this.Members.Config, 'TuningFunctions'))
    comp1 = this.Members.Config.TuningFunctions.Components{1};
    if( strcmp( comp1, '1')), has_constant_offset = true; else has_constant_offset = false; end
    this.Members.Config.Dimensions = this.Members.Config.TuningFunctions.Components;
    if( has_constant_offset)
        this.Members.Config.Dimensions(1) = [];
    end
    this.Members.H = this.Members.Config.TuningFunctions.Coeff(this.Members.Config.TuningFunctions.PredictiveCellsMask, :);
    if( ~has_constant_offset)
        this.Members.H(:,2:end+1) = this.Members.H; % Shift columns right
        this.Members.H(:,1) = 0; % Insert 0 offset value
    end
    %if( isscalar( this.Members.Gain))
    %    ProcessDims = size( this.Members.H, 2) - 1;
    %    this.Members.Gain = repmat( this.Members.Gain, [1 ProcessDims]);
    %end
end
%if( isfield( this.Members.Config, 'MeasurementMask'))
%    this.Members.MeasurementMask = this.Members.Config.MeasurementMask;
%else
%    MeasurementDims = size( this.Members.H, 1);
%    this.Members.MeasurementMask = true( MeasurementDims, 1);
%end
