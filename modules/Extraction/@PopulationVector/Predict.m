function [this, ProcessStateEst] = Predict( this, Measurement)

% [PVD, ProcessStateEst] = Predict( PVD, Measurement)
%
% Perform an update/predict step for the Population Vector Decoder. Measurement
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

% Estimate current process state based on measurement
ProcessDims = size( H, 2) - 1;
ModulationDepth = sqrt( sum( H(:,2:end).^2, 2));
PreferredDirection = H(:,2:end) ./ repmat( ModulationDepth, [1 ProcessDims]);

NormalizedMeasurement = Measurement - Offset;

GAIN = repmat(Gain, [MeasurementDims 1]);
ProcessStateEst = (ProcessDims / MeasurementDims) * (GAIN .* PreferredDirection)' * NormalizedMeasurement;
