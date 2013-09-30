function [iData, IncrState] = Raw2Intermediate_v3( RawDataDir, IncrState)

%    dbstop if error;

% Load raw QL (QuickLogger) and XM (Executive Module) files and
% convert to intermediate format

    if( RawDataDir(end) == '/' || RawDataDir(end) == '\')
        basedir = RawDataDir;
    else
        basedir = [RawDataDir '/'];
    end

    DFDataFile = [basedir 'Dragonfly_config.mat'];

    % Create stubs (made up if seq nums only) from filenames in the directory 
    % (Only one stub per QL/XM file pair)
    % Reorder files based on filenames (ex: 0001 should come before 0001.001)
    % NOTE: this will break data files recorded before executive.bruno (~10/18/2011)
    files = dir([basedir '*.bin']);
    [N M] = regexp({files.name}, '^QL\.(?<pre>\D*)(?<id>\d+\.\d+|\d+)', 'names', 'match');
    N = [N{:}];
    M = [M{:}];
    [Ms ix] = sort(M);
    file_stubs = cellfun(@(x, y) sprintf('%s%s',x, y), {N(ix).pre}, {N(ix).id}, 'un', false);

%     % Reorder files such that .xxx files are later based on file creation time
%     files = dir([basedir '*.bin']);
%     [files_sorted dt_ix] = sort(cell2mat({files.datenum}));
%     filenames = {files.name};
%     filenames = filenames(dt_ix);  % sort by file datetime
%     N = regexp({files.name}, '^QL\.(?<pre>\D*)(?<id>\d+\.\d+|\d+)', 'names', 'match');
%     file_stubs = cellfun(@(x, y) sprintf('%s%s',x, y), {N(ix).pre}, {N(ix).id}, 'un', false);

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
        fprintf('\nQL ');
        [QL, DF, IncrState] = LoadQLSessionData(basedir, DFDataFile, IncrState);

        %process the XM files: load them all into a cell array
        XMfiles = cellfun(@(x) sprintf('XM.%s.mat',x), IncrState.FileNames, 'un', false);
        fprintf('XM ');
        num_chars_disp = 0;
        for a = 1:length(XMfiles)
            fprintf('%s', [sprintf('%c',repmat( char(8), [1 num_chars_disp])) sprintf('%3.0f%%',(100*a/length(XMfiles)))]);
            num_chars_disp = 4;
            x = load([basedir XMfiles{a}]);
            XM(a) = x;
        end
        fprintf('\n');
        
        %reformat to be easier to access
        XM = StructArray2StructOfCellArrays( XM);
        XM = XM.XM;
        
        iData = struct( 'QL', QL, 'DF', DF, 'XM', XM, 'Version', 'v3');
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
        
        % check fieldnames and fill in any missing ones
        name_cnt = [];
        if (isstruct(in(1).(f{a})))
            for p = 1 : length(in), name_cnt = [name_cnt length(fieldnames(in(p).(f{a})))]; end
            [name_cnt_sorted, ix] = sort(name_cnt, 'descend');
            adj_ix = ix(find(name_cnt_sorted ~= name_cnt_sorted(1)));
            if (~isempty(adj_ix))
                %val = nan;
                %if (~isnumeric(in(ix(1)).(f{a}))), val = []; end
                for p = 1 : length(adj_ix)
                    fieldname_diff = setdiff(fieldnames(in(ix(1)).(f{a})), ...
                                             fieldnames(in(adj_ix(p)).(f{a})));
                    for r = 1 : length(fieldname_diff)
                        in(adj_ix(p)).(f{a}).(fieldname_diff{r}) = []; %val;
                    end
                end
            end
        end

        try
            if isstruct([in.(f{a})])
                %recurse:
                out.(f{a}) = StructArray2StructOfCellArrays([in.(f{a})]);
            else
                out.(f{a}) = {in.(f{a})}; %keeping as a cell array prevents having to define which dimension we 'cat' along
            end
        catch ME
            fprintf('WARNING: Error while handling struct field: ''%s'' (it will be discarded)\n', f{a});
            fprintf('MESSAGE: %s\n\n', ME.message);
        end

    end