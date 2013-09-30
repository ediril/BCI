function [CM, Decoder] = InitializeCMSession(confFileFullPath)

    CM = struct();
    CM.DataFilePath = [];
    CM.AdaptRepRange = [];
    CM.DecoderConfig = [];
    CM.CurrentRepID = 1;

    % read config file
    if ischar(confFileFullPath)
        c = LoadTextDataFailSafe(confFileFullPath);
    else
        c = confFileFullPath;
    end

    CM.config = c.config.calibration;

    if ~isfield(c.config, 'verbose')
        CM.config.verbose = 1;
    else
        CM.config.verbose = c.config.verbose;   
    end

    CM.decoder_type = c.config.decoder.type;
    
    Decoder = InitializeDecoder(CM.decoder_type);  