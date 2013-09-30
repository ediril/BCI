function num_vector = str2number( string)

if( ~ischar( string))
    error( ['str2number is supposed to get char data, got "' class(string) '" instead']);
end

num_vector = [];
remaining_string = string;
while( 1)
    delimiters = sprintf( ' ,\t\r\n');
    [token, remaining_string] = strtok( remaining_string, delimiters);
    if( isempty( token))
        break;
    end
    number = str2double( token);
    if( isnan( number))
        num_vector = [];
        return;
    end
    num_vector(:,end+1) = number;
end
