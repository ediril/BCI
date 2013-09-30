function EM = InitializeEMSession(ConfigFilename)

    EM = struct;
    EM.dataFilePath = [];
    
    EM = LoadEMConfigFile(EM, ConfigFilename);

    EM.Decoder = InitializeDecoder(EM.config.decoder.type);
    EM.hasTF = false;
    EM.DriftCorrection = zeros( 1, EM.config.NumDimensions);

