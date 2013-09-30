function this = SetConfig( this, varargin)

% LGF = SetConfig( LGF, Config)
% LGF = SetConfig( LGF, PropertyName1, PropertyValue1, PropertyName2, PropertyValue2, ...)
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
if( isfield( this.Members.Config, 'TuningFunctions'))
    comp1 = this.Members.Config.TuningFunctions.Components{1};
    if( strcmp( comp1, '1')), has_constant_offset = true; else has_constant_offset = false; end
    this.Members.Config.Dimensions = this.Members.Config.TuningFunctions.Components;
    if( has_constant_offset)
        this.Members.Config.Dimensions(1) = [];
    end
    this.Members.H = this.Members.Config.TuningFunctions.Coeff;
    if( ~has_constant_offset)
        this.Members.H(:,2:end+1) = this.Members.H; % Shift columns right
        this.Members.H(:,1) = 0; % Insert 0 offset value
    end
end
if( isfield( this.Members.Config, 'MeasurementMask'))
    this.Members.MeasurementMask = this.Members.Config.MeasurementMask;
else
    MeasurementDims = size( this.Members.H, 1);
    this.Members.MeasurementMask = true( MeasurementDims, 1);
end
if( ~isfield( this.Members.Config, 'Var'))
    Var = .005;
else
    Var = this.Members.Config.Var;
end

TFDims = size( this.Members.H, 2) - 1;
if( isfield( this.Members.Config, 'StateTrans'))
    ProcessDims = size( this.Members.Config.StateTrans, 1);
else
    ProcessDims = TFDims;
end
this.Members.ProcessDims = ProcessDims;
MeasurementDims = size( this.Members.H, 1);
this.Members.lgf = lgf_initial_param(ProcessDims,MeasurementDims,Var);
this.Members.lgf.prefdirs = this.Members.H(:,2:end)';
this.Members.lgf.baseline = this.Members.H(:,1)';
this.Members.lgf.activity_mask = this.Members.MeasurementMask;
if( ~isscalar( Var))
    this.Members.lgf.var = Var;
end
if( isfield( this.Members.Config, 'StateTrans'))
    this.Members.lgf.F = this.Members.Config.StateTrans;
end
if( isfield( this.Members.Config, 'RegressorFunc'))
    this.Members.lgf.regressor_func = this.Members.Config.RegressorFunc;
end
