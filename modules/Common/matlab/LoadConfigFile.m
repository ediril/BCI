function config = LoadConfigFile( filename)

config = [];
num_lines_read = 0;

if( ~exist( filename, 'file'))
    error(['Could not find configuration file: ' filename]);
else
    f = fopen( filename, 'rt');

    while( true)

        % Read next line
        line = fgetl( f); num_lines_read = num_lines_read + 1;

        if( ~isempty( line))
            remaining_line = line;
            
            % Get Varname
            [tokens, endidx] = regexp( remaining_line, '^(?<VarName>\w+)', 'names', 'end');
            if( isempty( tokens)) error( ['Incorrect formatting for VarName at line ' num2str( num_lines_read)]); end
            varname = tokens.VarName;
            remaining_line(1:endidx) = [];
            
            % Figure out if multi-line field
            endidx = regexp( remaining_line, '\s*:', 'end');
            if( isempty( endidx))
                simple_line = true;
            else
                simple_line = false;
                remaining_line(1:endidx) = [];
            end
            
            if( simple_line)
                value = str2num( remaining_line);
                if( isempty( value)) value = mv_deblank( remaining_line); end
            else
                num_field_lines = str2num( remaining_line);
                value = [];
                for i = 1 : num_field_lines
                    data_line = fgetl( f); num_lines_read = num_lines_read + 1;
                    value(end+1,:) = str2num( data_line);
                end
            end
            config = setfield( config, varname, value);
        end
        
        % If this is the end of the file, then quit
        if( feof( f))
            break;
        end

    end

    fclose( f);
end

