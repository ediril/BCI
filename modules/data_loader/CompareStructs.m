%======================================================================
%
% Compares two structs; fields of S1 are compared against S2's. If S2
% has missing fields, it will be reported, but if S2 has more fields,
% those will not be discovered (try swapping them to find those)
%
%======================================================================
function CompareStructs(S1, S2)

    s1_name = inputname(1);
    if isempty(s1_name), s1_name = '<S1>'; end
    
    fprintf('%s', s1_name);
    
    DiffCnt = 0;
    DiffCnt = CompareField( S1, S2, DiffCnt, 1);
    
    if (DiffCnt > 0)
        fprintf('\n\n%d differences were found\n', DiffCnt);
    end
    fprintf('\n');

    
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [DiffCnt, Result] = CompareField( S1, S2, DiffCnt, level)

%
% ::Return values::
% Result = 1: different
% DiffCnt, keeps track of number of differences
%

    FieldType = class( S1);
    switch( FieldType)
        case 'struct'
            % if struct is empty 
            if isempty(fieldnames(S1))
                if isempty(fieldnames(S2))
                    Result = 1;
                else
                    Result = 0;
                    DiffCnt = DiffCnt + 1;
                end
                return;
            end            
            
            % If the data is nested, then iterate fields and go recursive to each subfield
            SubFieldNames = fieldnames( S1);
            for i = 1 : length( SubFieldNames)
                SubFieldName = SubFieldNames{i};
                
                fprintf('\n');
                for t = 1 : level, fprintf('\t'); end
                fprintf('.%s', SubFieldName);

                if (isfield(S2,SubFieldName))
                    D1 = S1.(SubFieldName);
                    D2 = S2.(SubFieldName);
                    [DiffCnt, Result] = CompareField( D1, D2, DiffCnt, level+1);

                    if (Result == 0)
                        fprintf('\t\t\t\t\t<<<<<********* (different)');
                        DiffCnt = DiffCnt + 1;
                        Result = 1;  % count & report once!
                    end
                else 
                    fprintf('\t\t\t\t\t<<<<<********* (missing in input2)');
                    DiffCnt = DiffCnt + 1;
                end

            end
            
        case 'cell'
            for i = 1 : length( S1)
                D1 = S1{i};
                D2 = S2{i};
                [DiffCnt, Result] = CompareField( D1, D2, DiffCnt, level+1);
                if (Result == 0)
                    break;
                end
            end

        otherwise
            Result = 0;  %assume something is wrong
            
            if (isempty(S1) && isempty(S2))
                Result = 1;
            elseif (~isempty(S1) && ~isempty(S2))
                if (length(S1) == length(S2))
                    % cmp data
                    res = S1 - S2;
                    res(isnan(res)) = 0;

                    if isempty(find(res ~= 0))
                        Result = 1;
% else
%     disp('yey');
                    end
                end
            end
    end    
    