function [QL, RTMA, IncrState] = LoadQLSessionData( RawDataDir, RTMADataFile, IncrState)

% [QL, RTMA] = LoadQLSessionData( RawDataDir, QL_LogFiles, RTMADataFile)
%
% Loads messages saved by QuickLogger during an RP3 experiment

    % Add RTMA components to the path
    if( ~exist('LoadMessageLogs','file'))
        RTMA_dir = getenv('RTMA');
        if( isempty( RTMA_dir))
            error('RTMA environment variable not set, you must manually set the path for where to find the LoadMessageLogs function')
        else
            thisPaths = { [RTMA_dir '/src/modules/QuickLogger/LogReader']; [RTMA_dir '/lang/matlab']};
            for i = 1:length(thisPaths)
                if(isempty(strfind(path, thisPaths{i})))
                    addpath(thisPaths{i});
                end
            end
        end
    end
    
    % Load the RTMA message definitions
    r = load(RTMADataFile);
    RTMA = r.RTMA;
    
    % Get the concatenated log data for the session
    prefix = RawDataDir(1:end-1);
    QL_LogFiles = cellfun(@(x) sprintf('%s.QL.Trial%s.bin',prefix,x), IncrState.FileNames, 'un', false);
    [QL, IncrState] = LoadMessageLogs(RawDataDir, QL_LogFiles, RTMA, IncrState);
    
    % Separate messages of the same type from multiple modules
    QL = SeparateMultiModMessages(QL, RTMA);
    
