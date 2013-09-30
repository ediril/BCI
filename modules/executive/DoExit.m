function Message = DoExit()
    DensoSpeed = 20; SendMessage( 'DENSO_SET_SPEED', struct( 'speed', DensoSpeed));
    MoveDenso Away;
    SendSignal XM_END_OF_SESSION
    SendSignal EXIT_ACK
    DisconnectFromMMM
    exit
