function c = LoadValidateConfigFile(file_path, fields_to_check)
    c = [];
    
    [pathstr, fname, ext] = fileparts(file_path);
    config_file = [fname ext];
    
    while (1)
        num_valid = 0;
        c = LoadTextDataFailSafe(file_path);
        
        if length(fields_to_check) > 0
            for r = 1 : length(fields_to_check)
                fields = split(fields_to_check{r}, '.');   
                if ~CheckFields( c, fields)
                    break;
                else
                    num_valid = num_valid + 1;
                end
            end
            
            if (num_valid < length(fields_to_check)) 
                fprintf('Please fix ''%s'' and hit ENTER to continue\n', config_file);
                pause;
            else
                break;
            end
        else
            break;
        end
    end    


function valid = CheckFields( c, fields)
    valid = false;
    num_valid = 0;
    full_field_path = '';

    for f = 1 : length(fields)
        sub_fields = split(fields{f}, ',');   
        num_sub_field = 0;
        for s = 1 : length(sub_fields)
            sub_field = sub_fields{s};
            
            if ~isfield(c, sub_field)
                fprintf('>>> ERROR: ''%s%s'' section is missing\n', full_field_path, sub_field);
                break;
            else
                num_sub_field = num_sub_field + 1;
            end
        end
        
        if (num_sub_field < length(sub_fields))
            break;
        else
            num_valid = num_valid + 1; 
        end

        if (f <= length(fields)-1)
            full_field_path = [full_field_path fields{f} '.'];
            c = c.(fields{f});
        end
    end

    if (num_valid == length(fields)), valid = true; end



function l = split(S, D)
%L=SPLIT(D,S) splits a string S delimited by characters in D.  Meant to
%             work roughly like the PERL split function (but without any
%             regular expression support).  Internally uses STRTOK to do 
%             the splitting.  Returns a cell array of strings.

l = {};
while (length(S) > 0)
    [t,S] = strtok(S,D);
    if ~isempty(t)
        l = {l{:}, t};
    end
end
