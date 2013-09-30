function Calibration(confFileFullPath, mm_ip)

    dbstop if error

    global DF;

    Dragonfly_BaseDir = getenv('DRAGONFLY');
    App_BaseDir = getenv('BCI_MODULES');
    App_IncDir = getenv('BCI_INCLUDE');

    addpath([App_BaseDir '/Common/matlab']);
    addpath([Dragonfly_BaseDir '/lang/matlab']);
    addpath([App_BaseDir '/data_loader']); 

    MessageTypes = {...
                    'TRIAL_DATA_SAVED', ...
                    'SESSION_CONFIG', ...
                    'TASK_STATE_CONFIG', ...
                    'LOAD_DECODER_CONFIG', ...
                    'EXIT' ...
                    'PING' ...
                   };

    if(~exist(confFileFullPath))
       disp(['conf file ' confFileFullPath ' does not exists']);
       return;
    end

    ConnectArgs = {'CALIBRATION', Dragonfly_BaseDir, [App_IncDir '/Dragonfly_config.mat']};
    if exist('mm_ip','var') && ~isempty(mm_ip)
        ConnectArgs{end+1} = ['-server_name ' mm_ip];
    end

    ConnectToMMM(ConnectArgs{:});
    Subscribe( MessageTypes{:})
    SendModuleReady( );

    % initialize data stucts
    [CM, Decoder] = InitializeCMSession(confFileFullPath);
    Data = [];
    DL.IData = [];
    DL.IncrState_R2I = [];

    disp 'Calibration running..'

    while(1)
        M = ReadMessage( 1);
        if(isempty(M))
            %fprintf('.')
        else
            switch(M.msg_type)
                
                case 'LOAD_DECODER_CONFIG'
                    fprintf('Received LOAD_DECODER_CONFIG\n');
                    
                    calib_file_path = deblank(char(M.data.full_path));
                    fprintf('Calibration file path: %s\n', calib_file_path);
                    
                    datafilepath = CM.DataFilePath;
                    load(calib_file_path);

                    % keep our own datafilepath
                    CM.DataFilePath = datafilepath; 
                    
                    EMDecoderConfig = CM.EMDecoderConfig;
                    SendEMDecoderConfig(EMDecoderConfig);

                    save([CM.DataFilePath '/CM.rep.' num2str(CM.CurrentRepID) '.mat'], 'CM');

                    %% Advance CurrentRepID to past the calibration rep
                    %CM.CurrentRepID = CM.config.AdaptationSchedule(end)+1;

                    % we're done calibrating, so stop processing these messages
                    Unsubscribe 'TASK_STATE_CONFIG';
                    Unsubscribe 'TRIAL_DATA_SAVED';

                    fprintf('Calibration file is loaded\n');
                    
                    
                case 'TRIAL_DATA_SAVED'  % keep incrementally loading data files
                    [Data, DL] = ReadMergeData(CM.DataFilePath, Data, DL);
                    
                    
                case 'TASK_STATE_CONFIG'     
                    RepNum = M.data.rep_num;  
 
                    if ~isempty(Data)
                        % time to do calibration??
                        if (RepNum ~= CM.CurrentRepID) && ismember(CM.CurrentRepID, CM.config.AdaptationSchedule)

                            fprintf('Doing calibration.. (end of rep %d)\n\n', CM.CurrentRepID);
                            
                            [CM, EMDecoderConfig] = DoCalibration(CM, Data, Decoder);
                            
                            CM.EMDecoderConfig = EMDecoderConfig;
                            save([CM.DataFilePath '/CM.rep.' num2str(CM.CurrentRepID) '.mat'], 'CM');
            
                            % remove Data field before sending
                            EMDecoderConfig = rmfield(EMDecoderConfig, 'Data');
                            SendEMDecoderConfig(EMDecoderConfig);
                            
                            % if we're done calibrating, stop collecting data and processing messages
                            if (RepNum > CM.config.AdaptationSchedule(end))
                                Unsubscribe 'TASK_STATE_CONFIG';
                                Unsubscribe 'TRIAL_DATA_SAVED';
                                clear Data;
                                Data = [];
                                disp('Done calibrating');
                            end
                        end

                        CM.CurrentRepID = RepNum;
                    end

                case 'SESSION_CONFIG'
                    CM.DataFilePath = deblank(char(M.data.data_dir));
                    fprintf('Received DataFilePath: %s\n', CM.DataFilePath);

                case 'PING'
                    RespondToPing(M, 'Calibration');
                    
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
    
