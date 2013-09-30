function [iData, IncrState] = Raw2Intermediate_v2( RawDataDir, IncrState)

% Load raw QL (QuickLogger) and XM (Executive Module) files and
% convert to intermediate format

    if( RawDataDir(end) == '/' || RawDataDir(end) == '\')
        basedir = RawDataDir;
    else
        basedir = [RawDataDir '/'];
    end

    RTMAFiles = dir([basedir '*.RTMA.mat']);
    RTMADataFile = [basedir RTMAFiles(1).name];

    % Create stubs (made up if seq nums only) from filenames in the directory 
    % Only one stub per QL/XM file pair
    files = dir([basedir '*.bin']);
    F = regexp({files.name}, '^.+\.QL\.Trial(?<id>\d+\.\d+|\d+)', 'names');
    %F = regexp({files.name}, '^QL\.Trial(?<id>\d+\.\d+|\d+)', 'names');
    F = [F{:}];
    file_stubs = {F.id};

    if (nargin < 2) || (isempty(IncrState))
        % if no prior state, then create incremental state variable 
        IncrState = struct('FileNames', {file_stubs}, ...
                           'LastSequenceNo', 0, ...
                           'LastFileIndex', 0);
    else
        % if there is a prior state, get list of filenames and prune current list
        prune_list = IncrState.FileNames;
        [fnames, iFS, iPL] = intersect(file_stubs, prune_list);
        % keep only filenames we'll process during this iteration
        IncrState.FileNames = file_stubs;
        IncrState.FileNames(iFS)=[];    
    end

    
    if ~isempty(IncrState.FileNames)
        %process the QL files:
        [QL, RTMA, IncrState] = LoadQLSessionData(basedir, RTMADataFile, IncrState);

        %process the XM files: load them all into a cell array
%         prefix = RawDataDir;
%         XMfiles = cellfun(@(x) sprintf('%s.XM.Trial%s.mat',prefix,x), IncrState.FileNames, 'un', false);
%         for a = 1:length(XMfiles)
%             x = load([basedir XMfiles{a}]);
%             XM(a) = x.XM; 
%         end
%         %reformat to be easier to access
%         XM = StructArray2StructOfCellArrays( XM);
        XM = [];

        iData = struct( 'QL', QL, 'RTMA', RTMA, 'XM', XM, 'Version', 'v1');
    else
        % No new files since last incremental run
        iData = [];
    end
        
    % send back a list of all the files that have been processed so far
    IncrState.FileNames = file_stubs;
    IncrState.LastFileIndex = length(file_stubs);

    
function out = StructArray2StructOfCellArrays(in)

    f = fieldnames(in);
    for a = 1:length(f)
        if isstruct([in.(f{a})])
            %recurse:
            out.(f{a}) = StructArray2StructOfCellArrays([in.(f{a})]);
        else
            out.(f{a}) = {in.(f{a})}; %keeping as a cell array prevents having to define which dimension we 'cat' along
        end
    end
