function scalar_struct = CatStructFields( struct_array, how_to_cat, varargin)
%
% scalar_struct = CatStructFields( struct_array, how_to_cat, ...)
%
% Take a struct array where fields are expected to have data of a uniform size and type
% and, for each field, concatenate its values across the struct array into a single matrix
% that will be assigned to the same named field in the scalar output struct. In the case
% of nested structs, concatenate the fields recursively, so that the output is always a
% scalar structs where fields that are structs are also scalar.
%
% how_to_cat - a string argument that describes how to concatenate the
% field values:
% 'vertical':    data is concatenated vertically, i.e. along the 1-st dimension
% 'horizontal':  data is concatenated horizontally, i.e. along the 2-nd dimension
%
% Optionally, from the third argument on, the function can take the
% following option strings (in any order):
% 'transpose': transpose the concatenated field values right after concatenating them
% 'merge-fields': merge fields between structs, i.e. if some of the input
%   structs are missing some of the fields, they will be filled in with empty
%   data instead of failing the concatenation.

% Process the "how_to_cat" argument
switch( how_to_cat)
    case 'vertical'
        % If 'vertical', then data is concatenated
        % vertically, i.e. along the 1-st dimension
        cat_dim = 1;
    case 'horizontal'
        % If 'horizontal', then data is concatenated
        % horizontally, i.e. along the 2-nd dimension
        cat_dim = 2;
    otherwise
        error( ['Unrecognized value "' how_to_cat '" for the how_to_cat argument']);
end

% Process the options
options = varargin;
transpose = false;
merge = false;
keep_empty_fields = false;
string_concat = false;
for i = 1 : length( options)
    o = options{i};
    switch( o)
        case 'transpose', transpose = true;
        case 'merge-fields', merge = true;
        case 'keep-empty-fields', keep_empty_fields = true;
		case 'string-concat', string_concat = true;
        otherwise, error( ['Unrecognized option "' o '"']);
    end
end

fields = fieldnames( struct_array);
scalar_struct = [];
for i = 1 : length( fields)
    field_name = fields{i};
    try
        % First try concatenating the current level normally
		concatenated_field = cat( cat_dim, struct_array.(field_name));
		if ischar([struct_array.(field_name)]) && string_concat
			concatenated_field = {struct_array.(field_name)};
			if (cat_dim == 1)
				concatenated_field = concatenated_field';
			end
		end
    catch
        % If concatenation fails, then, if it is a dimension mismatch, give
        % information about what field the problem was with, if it is a
        % struct field mismatch, then again give information and rethrow, 
        % unless 'merge-fields' option defined, then fill in missing fields
        me = lasterror();
        switch me.identifier
            case 'MATLAB:catenate:dimensionMismatch', error( 'CatStructFields:DimensionMismatch', ['Dimension mismatch in concatenating struct field across struct array elements, field name [' field_name ']']);
            case 'MATLAB:catenate:structFieldBad'
                if( merge) % if 'merge-fields' option defined, then try again by filling in missing fields
                    concatenated_field = MergeFields( cat_dim, struct_array.(field_name));
                else % if 'merge-fields' not defined, then we cannot recover from concatenation failure
                    error( 'CatStructFields:FieldNameMismatch', ['Sub-struct field name mismatch in concatenating struct field across struct array elements, field name [' field_name ']']);
                end
            otherwise, error( me.identifier, me.message);
        end
    end
    
    % handle the 'empty matrix' case
    if isempty(concatenated_field) && keep_empty_fields
        concatenated_field = {struct_array.(field_name)};
    end
    
    % Once we have the field concatenated, then get its type, so we can
    % decide whether to just output the result or whether we have to go
    % recursive to concatenate deeper levels of the struct
    field_type = class( concatenated_field);
    switch( field_type)
        case 'struct'
            % Recursively concatenate deeper levels
            scalar_struct.(field_name) = CatStructFields( concatenated_field, how_to_cat, options{:});
        otherwise
            % Optionally transpose the concatenated field
            if( transpose)
                concatenated_field = concatenated_field';
            end
            % Stick concatenated field in the output
            scalar_struct.(field_name) = concatenated_field;
    end
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Concatenates the structs in varargin into a single struct array along
% the dimension "dim" while merging the field names between the structs.
% This is intended to be used for data that has mostly the same field names
% between structs, but where some of the fields are sometimes missing.
% Field names in the output are alphabetically sorted and represent the
% total set of field names that exist across all input structs. When the
% missing fields are filled in, their values are set to empty matrix. Some
% of the input arguments are allowed to be empty matrix, in which case all
% field names are filled in from the other structs, and data values will
% all be empty matrix.
function merged_struct = MergeFields( dim, varargin)

    % Find the unique field names that exist across all structs
    FieldNames = {};
    for i = 1 : length( varargin)
        input_struct = varargin{i};
        if( ~isempty( input_struct))
            field_names = fieldnames( input_struct);
            FieldNames = [FieldNames; field_names];
        end
    end
    UniqueFieldNames = unique( FieldNames);
    
    % Make the fields match
    for i = 1 : length( varargin)
        if( isempty( varargin{i}))
            % If input is empty, fill it in with all the unique field names
            % and assign empty matrix for values
            varargin{i} = cell2struct( repmat({[]},size(UniqueFieldNames)), UniqueFieldNames, 1);
            continue;
        end
        field_names = fieldnames( varargin{i});
        missing_names = setdiff( UniqueFieldNames, field_names);
        % Fill in the missing fields
        for m = 1 : length( missing_names)
            missing_name = missing_names{m};
            varargin{i}.(missing_name) = [];
        end
        % Make sure field names in output are in the same order as
        % UniqueFieldNames (i.e. alphabetic order)
        varargin{i} = orderfields( varargin{i}, UniqueFieldNames);
    end
    
    % Now we can concatenate the structs because we know the field names
    % match
    merged_struct = cat( dim, varargin{:});
    