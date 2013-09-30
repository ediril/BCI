
function data = load_QL_bin(path)

    RP3_SRC_DIR = getenv('ROBOTSRC');
    addpath([RP3_SRC_DIR '/data_loader/v3']);

    RTMA_DIR = getenv('RTMA');
    addpath([RTMA_DIR '/src/modules/QuickLogger/LogReader']);
    addpath([RTMA_DIR '/lang/matlab']);

    if isdir(path)
        dir_path = path;
    else
        dir_path = fileparts(path);
    end
    
    load ([dir_path '/RTMA_config.mat'])

    if isdir(path)
        files = dir([path '/*.bin']);
        data = LoadMessageLogs(path, {files.name}, RTMA);
    else
        data = LoadMessageLog(path, RTMA);
    end