function Config = GetConfig( this, PropName)

% Config = GetConfig( PV)
% PropertyValue = GetConfig( PV, PropertyName)
%
% Gets the configuration of the Population Vector decoder PV. If a
% property name is specified, then gets only the value of that
% configuration property. Else gets the whole config struct.

if( exist( 'PropName', 'var'))
    Config = this.Members.Config.(PropName);
else
    Config = this.Members.Config;
end
