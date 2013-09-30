%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function SaveData( )

    global DF;
    global XM;

    pause(0.25);  % pause for a bit to let all messages arrive at QL

    % Construct datafile name
    file_num_str = ['.' num2str(XM.file_num,'%.4d')];

    % Save XM data file
    XM_FilePath = [XM.session_datafile_basepath 'XM' file_num_str '.mat'];
    save( XM_FilePath, 'XM');

    % Tell QuickLogger module to save its data
    QL_FilePath = [XM.session_datafile_basepath 'QL' file_num_str '.bin'];
    saveinfo = DF.MDF.SAVE_MESSAGE_LOG;
    saveinfo.pathname(1:length(QL_FilePath)) = uint8(QL_FilePath);
    saveinfo.pathname_length = int32( length(QL_FilePath));
    SendMessage( 'SAVE_MESSAGE_LOG', saveinfo);

    fprintf('Saving trial data... ');
    ExpectedEvents = {'MESSAGE_LOG_SAVED'};
    WaitFor( 100, ExpectedEvents{:});
    fprintf('done\n');
    
    SendSignal TRIAL_DATA_SAVED;     

    XM.file_num = XM.file_num + 1;
