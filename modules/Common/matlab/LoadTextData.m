% LoadTextData( FILENAME)
% DATA = LoadTextData( FILENAME)
%
% Load matlab data from a structured text file FILENAME. The
% file can contain a description of (almost) any type of matlab variables,
% including numeric matrix, char string, struct or cell array. Struct and
% cell arrays can have any level of nesting. Without a return argument, the
% function loads the variables from the file, and creates variables in the
% caller's workspace, just like the matlab "save" function. If a return
% argument is specified, then the variables from the file become members of
% the structure DATA.
%
% Meel Velliste
% 5/13/2006
%
%
% Structured Text Data File format v1.0 specification:
%
%    String data or numeric row vectors written on a single line. Numbers
%    are separated by spaces.
%
%    Numeric matrices begin with "[" followed by a newline. The following
%    lines specify the rows of the matrix (numbers separated by spaces).
%    The matrix ends with "]" on a line by itself. Only 2-dimensional
%    matrices are supported.
%
%    Structures begin with ":" followed by a newline. The following lines
%    specify the fields and the structure ends with a ";" on a line by
%    itself. Each field line begins with the name of the field (optionally
%    indented for readability), followed by the field data. String or row
%    vector data can follow the field name on the same line. More complex
%    datatypes begin with their format specifier on the same line as the
%    field name.
%
%    Cell arrays begin with "{" followed by a newline. The following lines
%    specify the elements of the cell array, one element per line for row
%    vectors or strings. Elements can also be nest cell arrays of
%    structures, following the same formatting recursively.
%
%    Example:
%
%    var1 {
%        John Smith
%        11.0 12.8 -1.2
%        {
%            5 8 2 1 1 2
%            3 2 2
%            8 9 0 2 2 1 1 2 3
%        }
%        :
%            DelayTime    120
%            ReactionTime 304
%            Config :
%                RunTime  110
%                StopTime 2000
%            ;
%        ;
%    }
%    var2 Some string value
%    var3 34.231
%    var4 [
%          34.2  12.3 4.22
%          89.3 -12.2 3.21
%    ]
%

function varargout = LoadTextData( filename)

    %
    % Open the file
    %
    f = fopen( filename, 'rt');
    if( f < 0)
        error( ['Could not open the file "' filename '" for reading']);
    end
    
    %
    % Check the format version, if correct format, use this function,
    % otherwise find the appropriate older function and use that. This way
    % older formats will be read in trasparent backward compatible manner.
    %
    THIS_VERSION = 'v1.2';
    data_version = ReadHeader( f);
    if( strcmp( data_version, THIS_VERSION))
        first_level = 1;
        data = ReadStruct( f, first_level);
        CheckForExtraneousData( f);
        fclose( f);        
    else
        fclose( f);
        data = CallBackwardCompatibleFunction( filename, data_version);        
    end
    
    % If no output argument, then assign variables to caller's workspace
    switch( nargout)
        case 0
            var_names = fieldnames( data);
            num_vars = length( var_names);
            for v = 1 : num_vars
                var_name = var_names{v};
                assignin( 'caller', var_name, data.(var_name));
            end
        case 1
            varargout{1} = data;
        otherwise
            error( 'LoadTextData: incorrect number of output arguments');
    end


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function data = CallBackwardCompatibleFunction( filename, data_version)

    file_suffix = data_version;
    file_suffix(find( data_version == '.')) = '_';
    older_format_function = ['LoadTextData_' file_suffix];
    if( exist( older_format_function, 'file'))
        data = feval( older_format_function, filename);
    else
        error( ['Cannot find a function to read Structured Text Data ' data_version]);
    end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Read the header that specifies the version of the data format. This way,
% if it is an older data format, we know not to use this file to read it,
% but rather call a function that implements reading the older version.
function data_version = ReadHeader( f)

    line = GetNextLine( f);
    tokens = regexp( line, '^\s*StructuredTextData\s+(?<version>v[0-9]+\.[0-9]+)\s*$', 'names');
    if( isempty( tokens))
        error( 'The file does not have the expected header: "StructuredTextData vX.Y", where X and Y are the major and minor version number');
    else
        data_version = tokens.version;
    end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Figure out what kind of data we are dealing with, then call the
% appropriate function to read the data
function [data] = ReadData( line, f)

    tokens = regexp( line, '^\s*(?<format_specifier>[\[\{\:])\s*$', 'names');
    
    if( isempty( tokens))
        data = ReadDataLine( line);
    else
        switch( tokens.format_specifier)
            case '[', data = ReadNumericMatrix( f);
            case ':', data = ReadStruct( f);
            case '{', data = ReadCell( f);
            otherwise, error( ['Unrecognized formatting specifier "' tokens.format_specifier '"']);
        end
    end
 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Read single line data (i.e. scalar or vector or string)
function data = ReadDataLine( line)

    data = str2number( line);
    if( isempty( data))
        data = remove_spaces( line);
        if( isempty( data))
            data = '';
        end
    else
        CheckForInvalidChars(line);
    end

    
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Check for invalid characters in numeric data sequences
function CheckForInvalidChars(line)
    line = strrep(line, 'inf', ''); % remove 'inf's, they are allowed
    line = strrep(line, 'nan', ''); % remove 'nan's, they are allowed
    chk_valid = regexp(line, '[^0-9\-\.\s]+', 'once');
    if (~isempty(chk_valid))
        error('Found invalid character: "%c"\nLine: %s',line(chk_valid), line);
    end


    
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Read a numeric matrix row-by-row
function data = ReadNumericMatrix( f)

    data = [];
    while( 1)
        % Read a line
        line = GetNextLine( f);
        if (line == -1), break;  end  % check for eof

        % Check for end of matrix marker
        endidx = regexp( line, '^\s*\]', 'end');
        if( isempty( endidx))
            if ~isempty(line)
                % If not end, read row
                row = str2number( line);
                if( isempty( row))
                    error('Found invalid numeric matrix row');
                else
                    CheckForInvalidChars(line);
                end
                data = [data; row];
            end
        else
            % Check for extraneous stuff at the end of line after end of
            % matrix marker
            remaining_line = line(endidx+1:end);
            if( ~isempty( remaining_line))
                if( regexp( remaining_line, '\S', 'once'))
                    error( 'Extraneous text found after end-of-matrix marker');
                end
            end
            % Matrix done, so exit
            break;
        end
    end
    
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Read a struct
function [data] = ReadStruct( f, first_level)

    if( ~exist( 'first_level', 'var'))
        first_level = 0;
    end

    data = [];
    while( 1)
        
        % Read a line
        line = GetNextLine( f);
        if (line == -1), break;  end  % check for eof
        
        %
        % Check for end of struct
        %
        if( first_level)
            if( isempty( strtok( line))) % if empty line
                break; % struct is done, exit
            end
        end
        endidx = regexp( line, '^\s*;', 'end');
        if( endidx) % If end-of-struct marker ";"
            % Check for extraneous stuff at the end of line after end of
            % struct marker
            remaining_line = line(endidx+1:end);
            if( ~isempty( remaining_line))
                if( regexp( remaining_line, '\S', 'once'))
                    error( 'Extraneous text found after end-of-struct marker');
                end
            end
            break; % Struct done, so exit
        end
        
        %
        % Not end of struct yet, so read a field
        %
        [token, remaining_line] = strtok( line);
        if( isempty( token))
            continue;
        end
        field_data = ReadData( remaining_line, f);
        if (strcmp(class(field_data),'char') == 1)
            list = regexp( field_data, '\S+', 'match');
            if (length(list) > 1), field_data = list; end 
        end
        data = setfield( data, token, field_data);
    end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Read a cell array
function [data] = ReadCell( f)

    data = {};
    idx = 1;
    while( 1)
        % Read a line
        line = GetNextLine( f);
        if (line == -1), break;  end  %eof?

        % Check for end of cell marker
        endidx = regexp( line, '^\s*\}', 'end');
        if( isempty( endidx))
            % If not end, read element
            element = ReadData( line, f);
            if ( isempty( element))
                continue;
            end
            data{idx,1} = element;
            idx = idx + 1;
        else
            % Check for extraneous stuff at the end of line after end of
            % cell marker
            remaining_line = line(endidx+1:end);
            if( ~isempty( remaining_line))
                if( regexp( remaining_line, '\S', 'once'))
                    error( 'Extraneous text found after end-of-cell marker');
                end
            end
            % Cell done, so exit
            break;
        end
    end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Print the correct amount of indenting for the given recursion level
function PrintIndent( f, recursion_level)

if( recursion_level == 1)
    indent_size = 1;
else
    indent_size = 4 * (recursion_level - 1);
end
indent = repmat( ' ', [1 indent_size]);
fprintf( f, indent);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function clean_str = remove_spaces( str)

str = deblank( str);
str = flipdim( str, 2);
str = deblank( str);
clean_str = flipdim( str, 2);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function line = GetNextLine( f)

line = fgetl( f);
%switch( line)
%    case -1
%        line = '';
%    otherwise
if (line ~= -1)
        i = strfind(line, '#');  % remove comments
        if ~isempty(i), line(i(1):end)=[]; end
        if( isempty(deblank(line))), line = '';  end
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function CheckForExtraneousData( f)

remaining_text = char( fread( f, [1 inf], 'char'));
if( ~isempty( remaining_text))
    if( regexp( remaining_text, '\S', 'once'))
        error( 'Unexpected text found at the end of data. Incorrect formatting?');
    end
end
