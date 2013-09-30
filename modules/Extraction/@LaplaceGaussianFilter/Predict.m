function [this, ProcessStateEst] = Predict( this, Measurement, OffsetState)

% [Decoder, ProcessStateEst] = Predict( Decoder, Measurement)
%
% Perform an update/predict step for the Laplace-Gaussian Filter. Measurement
% is the observed data. The output ProcessStateEst represents the estimated
% state of the process. No smoothing is performed on the Measurement. If
% smoothing is desired, it should be done externally prior to passing the
% Measurement to this function.

% Meel Velliste 9/19/2009

% Calculate a dynamic offset for the tuning function based on the state
% variable OffsetState, and its corresponding configured tuning function
if( exist( 'OffsetState', 'var'))
    TFOffset = this.Members.Config.OffsetTF * OffsetState;
end

% Estimate current process state based on measurement
NumSamples = size( Measurement, 2);
if( NumSamples == 1)
    this = DoSmartVar( this);
    if( exist( 'TFOffset', 'var'))
        [ProcessStateEst, this.Members.lgf] = lgf_predict(this.Members.lgf, Measurement', TFOffset');
    else
        [ProcessStateEst, this.Members.lgf] = lgf_predict(this.Members.lgf, Measurement');
    end
else
    ProcessStateEst = nan( this.Members.ProcessDims, NumSamples);
    for i = 1 : NumSamples
        this = DoSmartVar( this);
        measurement = Measurement(:,i);
        if( exist( 'TFOffset', 'var'))
            tf_offset = TFOffset(:,i);
            [process_state_est, this.Members.lgf] = lgf_predict(this.Members.lgf, measurement', tf_offset');
        else
            [process_state_est, this.Members.lgf] = lgf_predict(this.Members.lgf, measurement');
        end
        ProcessStateEst(:,i) = process_state_est;
        if( mod( i, 6000)==0), fprintf('%d\n', i); end
    end
end
