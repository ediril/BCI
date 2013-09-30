function sub_struct = CopyStructFields( orig_struct, field_name_prefix)

% sub_struct = CopyStructFields( orig_struct, field_name_prefix)
%
% Copies fields that begin with FIELD_NAME_PREFIX from ORIG_STRUCT
% to SUB_STRUCT

    F = fieldnames( orig_struct);
    idx = strmatch( field_name_prefix, F);
    sub_struct = struct();
    for i = 1 : length( idx)
        f = F{idx(i)};
        sub_struct.(f) = orig_struct.(f);
    end
    