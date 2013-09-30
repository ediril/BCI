function [this, ProcessStateEst] = Predict( this, Measurement)

% [OLE, ProcessStateEst] = Predict( OLE, Measurement)
%
% Perform an update/predict step for the OLE Decoder. Measurement
% is the observed data. The output ProcessStateEst represents the estimated
% state of the process. No smoothing is performed on the Measurement. If
% smoothing is desired, it should be done externally prior to passing the
% Measurement to this function.

% Meel Velliste 9/19/2009

% Grab stuff from config
H = this.Members.H;
Gain = this.Members.Gain;
MeasurementDims = size( H, 1);
Offset = H(:,1);

if (size(Measurement, 2)>1)
    Offset = repmat(Offset, 1, size(Measurement, 2));
end

PreferredDirection = H(:,2:end);
NormalizedMeasurement = Measurement - Offset;
GAIN = repmat(Gain, [MeasurementDims 1]);
ProcessStateEst = (GAIN .* PreferredDirection)' * NormalizedMeasurement;

