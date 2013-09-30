function Connect(host)

    global DF;

    if ~exist('host', 'var')
        host = 'localhost:7111';
    end
    
    server = sprintf('%s', host)

    DFPath = getenv('DRAGONFLY');
    addpath([DFPath '/lang/matlab']);

    ConnectToMMM( 0, '', [getenv('BCI_INCLUDE') '/Dragonfly_config.mat'], ['-server_name ' server])

    disp('Ready');
