function Extraction(confFileFullPath, mm_ip)

    dbstop if error

    global DF;

    Dragonfly_BaseDir = getenv('DRAGONFLY');
    App_BaseDir = getenv('BCI_MODULES');
    %Config_BaseDir = getenv('BCI_CONFIG');
    %Data_BaseDir = getenv('BCI_DATA');
    App_IncDir = getenv('BCI_INCLUDE');

    addpath([App_BaseDir '/Common/matlab']);
    addpath([Dragonfly_BaseDir '/lang/matlab']);

    MessageTypes = { ...
                    'SPM_SPIKECOUNT', ...
                    'SESSION_CONFIG', ...
                    'EM_END_SESSION', ...
                    'EM_DECODER_CONFIGURATION', ...
                    'RELOAD_CONFIGURATION', ...
                    'SPM_FIRINGRATE', ...
                    'EM_UPDATE_DRIFT_CORRECTION' ...
                    'EXIT' ...
                    'PING' ...
                   };

    if(~exist(confFileFullPath))
       disp(['conf file ' confFileFullPath ' does not exists']);
       return;
    end

    ConnectArgs = {'EXTRACTION_MOD', Dragonfly_BaseDir, [App_IncDir '/Dragonfly_config.mat']};
    if exist('mm_ip','var') && ~isempty(mm_ip)
        ConnectArgs{end+1} = ['-server_name ' mm_ip];
    end    
   
    ConnectToMMM(ConnectArgs{:});
    Subscribe( MessageTypes{:})
    SendModuleReady( );
     
    EM = InitializeEMSession(confFileFullPath);
    MeasurementBuffer = [];

% % ------ debug ----------------------------------------------------------
% load 'EMDecoderConfig.mat'
% TF = EMDecoderConfig; clear EMDecoderConfig;
% EM = AcceptNewDecoderConfig(EM, TF);
% % ------ debug ----------------------------------------------------------

    disp 'Extraction running..'

    while(1)
        M = ReadMessage( 'blocking');
        if(isempty(M))
            %fprintf('.')
        else
            switch(M.msg_type)
                
                case 'SPM_FIRINGRATE'
                    rates = M.data.rates';
                    PredictSendMovementCommand(EM, rates, M.data.sample_header);
                
                case 'SPM_SPIKECOUNT'
                    %fprintf(1,'!');
                    counts = double(M.data.counts');
                    if(find(isnan(counts))), disp('nans');   end

                    % apply filter
                    Measurement = [];
                    switch(EM.config.measurement.type)
                        case 'rate'     %pva, ole
                            MeasurementBuffer = AddToMeasurementBuffer(EM, MeasurementBuffer, counts);

                            if ischar( EM.config.measurement.options.Dt) && ...
                                       strcmp(EM.config.measurement.options.Dt, 'SPM_SPIKECOUNT')
                                EM.config.Dt = M.data.sample_header.DeltaTime;
                            end

                            Measurement = (MeasurementBuffer / EM.config.Dt) * EM.Filter;

                        case 'count'    %lgf
                            Measurement = counts;
                    end
                    PredictSendMovementCommand(EM, Measurement, M.data.sample_header);
                    SendDriftCorrection(EM, M.data.sample_header);
                    
                  
                case 'RELOAD_CONFIGURATION'
                    %fprintf('R\n');
                    EM = LoadEMConfigFile(EM, confFileFullPath);
                    if EM.hasTF
                        EM.Decoder = SetConfig(EM.Decoder, EM.config.decoder.options);
                    end
                    
                case 'SESSION_CONFIG'
                    fprintf('Received SESSION_CONFIG\n');
                    EM.dataFilePath = deblank(char(M.data.data_dir));
                    fprintf('EM.dataFilePath is %s\n', EM.dataFilePath);

                case 'EM_DECODER_CONFIGURATION'
                    fprintf('D\n');
                    TF = ReceiveEMDecoderConfig(M);
                    EM = AcceptNewDecoderConfig(EM, TF);

                case 'EM_UPDATE_DRIFT_CORRECTION'
                    EM.DriftCorrection = M.data.drift_correction;
                    fprintf('Received EM_UPDATE_DRIFT_CORRECTION: ');
                    fprintf('%.2f  ', EM.DriftCorrection);
                    fprintf('\n');
                    
                case 'EM_END_SESSION' 
                    break;
                
                case 'PING'
                    RespondToPing(M, 'Extraction');
                    
                case 'EXIT'
                    if (M.dest_mod_id == GetModuleID()) || (M.dest_mod_id == 0)
                        SendSignal EXIT_ACK
                        break;
                    end

            end         
        end
    end
    DisconnectFromMMM
    exit




%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function MeasurementBuffer = AddToMeasurementBuffer(EM, MeasurementBuffer, Measurement)

    if isempty(MeasurementBuffer)
        MeasurementBuffer = repmat(Measurement, [1 length(EM.Filter)]);
    else
        MeasurementBuffer(:,1) = [];
        MeasurementBuffer(:,end+1) = Measurement;
    end
    

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function SendDriftCorrection(EM, sample_header)    
    
    global DF;

    dc = DF.MDF.EM_DRIFT_CORRECTION;
    dc.sample_header = sample_header;
    dc.drift_correction = EM.DriftCorrection;
    SendMessage( 'EM_DRIFT_CORRECTION', dc); 

    
    
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function PredictSendMovementCommand(EM, Measurement, sample_header)

    prediction.vel = zeros(EM.config.NumDimensions,1)';
    prediction.pos = zeros(EM.config.NumDimensions,1)';

    if EM.hasTF
        comp_index_lookup = 'xyz-ijk-abcd';
        [EM.Decoder new_prediction] = Predict(EM.Decoder, Measurement(EM.PredictiveChannels));
        dims_idx = find(EM.config.decoder.options.Gain ~= 0);
        for d = 1 : length(EM.Components)
            comp = EM.Components{d};
            pr = new_prediction(d);
            i = strfind(comp_index_lookup, comp(3));
            if comp(2) == 'p'
                prediction.pos(i) = pr;
            elseif comp(2) == 'v'
                pr = pr + EM.DriftCorrection(dims_idx(d));
                prediction.vel(i) = pr;
            end
        end
    end

    SendMovementCommand(EM, prediction, sample_header);
