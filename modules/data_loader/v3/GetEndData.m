function EndData = GetEndData( Data)


    Fields = fieldnames(Data);
    
    for f = 1 : length(Fields)
        Field = Fields{f};
        FieldData = Data.(Field);
        EndData.(Field) = GetFieldEndData(FieldData);
    end

    
function EData = GetFieldEndData( FieldData)

    FieldType = class( FieldData);
    
    switch( FieldType)
        case 'struct'
            % If the data is nested, then iterate fields and go recursive to remove data in each field
            EData = [];
            SubFieldNames = fieldnames( FieldData);
            for i = 1 : length( SubFieldNames)
                SubFieldName = SubFieldNames{i};
                SubFieldData = FieldData.(SubFieldName);
                ESubData = GetFieldEndData( SubFieldData);
                EData.(SubFieldName) = ESubData;
            end
        otherwise
            % If it's regular data then go ahead and do the remove. 
            if (isempty(FieldData))
                EData = [];
            else
                EData = FieldData(:, end);
            end
    end    