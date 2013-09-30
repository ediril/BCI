function this = DoSmartVar( this)

% LGF = DoSmartVar( LGF)
% Calculates state variance "smartly" dynamically

if( isfield( this.Members.Config, 'SmartVar'))
    intercept = this.Members.Config.SmartVar(1);
    slope = this.Members.Config.SmartVar(2);
    % Model the standard deviation as a linear function of the square root of speed
    velocity = this.Members.lgf.x(1:3);
    speed = sqrt( sum(velocity.^2));
    sr_speed = sqrt( speed);
    standard_deviation = intercept + slope * sr_speed;
    variance = standard_deviation^2;
    %the_eye = zeros( length( this.Members.lgf.x));
    %the_eye(1:3,1:3) = eye(3);
    the_eye = eye(length( this.Members.lgf.x));
    VAR = variance * the_eye;
    this.Members.lgf.var = VAR;
end
