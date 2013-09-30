function ProcessRawData(config_file, project)

%
% For processing single session, call ProcessRawData({'Gigantor', 229})
%

    SRC_DIR = getenv('ROBOTSRC');
    DATA_DIR = getenv('ROBOTDATA');
    last_file = 'BatchProcessRawData_Last.txt';
    batch_mode = true;
    project = 'rg2';


    if (nargin == 0)
        config_file = 'BatchProcessRawData.conf';

    elseif (nargin == 1)
        if ~iscell(config_file)
            if strcmp(config_file, '') || isempty(config_file)
                error('Please specify a valid config file');
            end
        end

    elseif (nargin == 2)
        if ~iscell(config_file)
            if strcmp(config_file, '') || isempty(config_file)
                config_file = 'BatchProcessRawData.conf';
            end
        end

        %if ~strcmpi(project, 'rg2')
        %    [ret, hostname] = system('hostname');
        %
        %    if strncmpi(hostname, 'hermi', 5)
        %        SRC_DIR = strrep(SRC_DIR, 'rg2', project);
        %        DATA_DIR = strrep(DATA_DIR, 'rg2', project);
        %
        %        PROJ_DIR = strrep(getenv('ROBOTAPP'), 'rg2', project);
        %        last_file = [PROJ_DIR '/scripts/' last_file];
        %        config_file = [PROJ_DIR '/scripts/' config_file];
        %
        %    else
        %        error( sprintf(['\nYou need to be running on "hermi" ', ...
        %                        'to be able to specify an alternate project\n']));
        %    end
        %end
    end

    addpath([SRC_DIR '/data_loader']);

    if iscell(config_file)
        proc_folders = {config_file{1}};
        last_folder_id = config_file{2};
        batch_mode = false;
    else
        proc_folders = textread(config_file, '%s');
    end

    if batch_mode
        if exist(last_file, 'file')
            [last_folders last_folder_id] = textread(last_file, '%s\t%d');
        else
            last_folders = proc_folders;
            last_folder_id = 0;
        end
    end

    folder_cnt = 0;
    error_cnt = 0;
    fprintf('=========================================================\n\n');
    fprintf('--> Start: %s %s\n', datestr(now, 23), datestr(now, 13));
    for f = 1 : length(proc_folders)
        fprintf('\n# %s\n', proc_folders{f});
        basedir = [DATA_DIR '/' proc_folders{f}];

        % check if output folders exist, if not create them
        Intermediate_Folder = [basedir '/Intermediate/'];
        if ~exist(Intermediate_Folder, 'dir'), mkdir(Intermediate_Folder); end

        Formatted_Folder = [basedir '/Formatted/'];
        if ~exist(Formatted_Folder, 'dir'), mkdir(Formatted_Folder); end

        if batch_mode
            f_idx = find(strcmp(last_folders, proc_folders{f})==1);
            if isempty(f_idx),
                f_idx = f;
                last_folder_id(f) = 0;
                last_folders(f) = proc_folders(f);
            end
        end

        files = dir([basedir '/Raw/' proc_folders{f} '*']);
        c_id = regexp({files.name}, ['^' proc_folders{f} '\.D?K?\.?(\d+)'], 'tokens');
        id = cellfun(@(x) str2num(x{1}{1}), c_id, 'un', false);
        id = [id{:}];

        if batch_mode
            ix = find(id > last_folder_id(f_idx));
        else
            ix = find(id == last_folder_id);
            if isempty(ix), error('ERROR: id is invalid');   end
        end

        for r = ix
            proc_dir = [basedir '/Raw/' files(r).name];
            fprintf('> %s', proc_dir);
            try
                iD_out_file = [Intermediate_Folder strrep(files(r).name, 'DK.', '') '.mat'];
                new_iD_available = false;
                if ~exist( iD_out_file, 'file')
                    Data = Raw2Intermediate(proc_dir);

                    % apply any fixes to intermediate data
                    Data = apply_fix(proc_dir, 'fix_idata', Data);

                    sz = whos('Data');
                    if (sz.bytes <= 2147483647), save(iD_out_file, 'Data', '-v7'); % save compressed when possible
                    else save(iD_out_file, 'Data', '-v7.3'); end
                    new_iD_available = true;
                end

                iF_out_file = [Formatted_Folder strrep(files(r).name, 'DK.', '')  '.mat'];
                if ~exist( iF_out_file, 'file') || new_iD_available
                    if ~exist('Data', 'var'), load(iD_out_file); end

                    % apply any fixes to formatted data
                    Data = apply_fix(proc_dir, 'fix_fdata', Data);

                    Data = Intermediate2Formatted(Data);
                    sz = whos('Data');
                    if (sz.bytes <= 2147483647), save(iF_out_file, 'Data', '-v7'); % save compressed when possible
                    else save(iF_out_file, 'Data', '-v7.3'); end

                    folder_cnt = folder_cnt + 1;
                end

                fprintf('\n');

            catch ME
                fprintf(' ... [error]\n');
                fprintf('ERROR: %s\n\n', ME.message);
                error_cnt = error_cnt + 1;
            end

            clear Data;
        end

        if (batch_mode && ~isempty(ix)), last_folder_id(f_idx) = id(ix(end)); end
    end

    fprintf('\n--> End: %s %s\n\n', datestr(now, 23), datestr(now, 13));
    fprintf('Total number of processed folders: %d\n', folder_cnt);
    fprintf('Total number of errors: %d\n\n', error_cnt);

    if batch_mode
        fid = fopen(last_file, 'w');
        for f = 1 : length(last_folders)
            fprintf(fid, '%s\t%d\n', last_folders{f}, last_folder_id(f));
        end
        fclose(fid);
    end



function rData = apply_fix(raw_folder, fix_filename_base, Data)

    fix_files = dir([raw_folder '/' fix_filename_base '*.m']);

    if length(fix_files) > 0

        addpath(raw_folder);

        fix_file = fix_files(1).name;

        if length(fix_files) > 1
            fprintf('  *Warning* There is more than one "fix_idata" files in the Raw folder! Applying "%s"\n', fix_file);
        else
            fprintf('Applying "%s"', fix_file);
        end

        [pathstr, fname] = fileparts(fix_file);

        exec_func = str2func(fname);

        rData = exec_func(Data);

        rmpath(raw_folder);
    else
        rData = Data;

    end
