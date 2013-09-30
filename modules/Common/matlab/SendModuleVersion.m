function SendModuleVersion( module_name, version_string)

    global DF;

    [status, git_version] = system('git rev-parse --short HEAD');
    
    
    if exist('version_string', 'var')
        version_string = sprintf('%s (%s)', strrep(git_version, sprintf('\n'), ''), version_string);
    else
        version_string = git_version;
    end

    if (length(module_name) > 63)
        module_name = module_name(1:63);
    end
    
    if (length(version_string) > 63)
        version_string = version_string(1:63);
    end
    
    msg = DF.MDF.CODE_VERSION;
    msg.module_name = [int8(str2num(sprintf('%d ', module_name))) zeros(1, 64-length(module_name))];    
    msg.version = [int8(str2num(sprintf('%d ', version_string))) zeros(1, 64-length(version_string))]; 
    SendMessage( 'CODE_VERSION', msg);