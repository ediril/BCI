function [QL, DF, IncrState] = LoadQLSessionData( RawDataDir, DFDataFile, IncrState)

% [QL, RTMA] = LoadQLSessionData( RawDataDir, QL_LogFiles, RTMADataFile)
%
% Loads messages saved by QuickLogger during an RP3 experiment

    % Add RTMA components to the path
    if( ~exist('LoadMessageLogs','file'))
        DF_dir = getenv('DRAGONFLY');
        if( isempty( DF_dir))
            error('Dragonfly environment variable not set, you must manually set the path for where to find the LoadMessageLogs function')
        else
            thisPaths = { [DF_dir '/src/utils/LogReader']; [DF_dir '/lang/matlab']};
            for i = 1:length(thisPaths)
                if(isempty(strfind(path, thisPaths{i})))
                    addpath(thisPaths{i});
                end
            end
        end
    end
    
    % Load the RTMA message definitions
    r = load(DFDataFile);
    DF = r.DF;
    
    % Get the concatenated log data for the session
    QL_LogFiles = cellfun(@(x) sprintf('QL.%s.bin',x), IncrState.FileNames, 'un', false);
    [QL, IncrState] = LoadMessageLogs(RawDataDir, QL_LogFiles, DF, IncrState);
    
    % Separate messages of the same type from multiple modules
    QL = SeparateMultiModMessages(QL, DF);
    
