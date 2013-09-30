%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function EM = AcceptNewDecoderConfig(EM, TF)
    EM.PredictiveChannels = TF.ActiveChannelIndex(TF.PredictiveCellsMask);
    disp(['Decoder is using ' num2str(length(EM.PredictiveChannels)) ' out of ' num2str(length(TF.ActiveChannelIndex)) ' units as "good"']);
    EM.config.decoder.options.TuningFunctions = TF;
    EM.Decoder = SetConfig(EM.Decoder, EM.config.decoder.options);
    EM.Components = TF.Components(2:end);
    EM.hasTF = true;

