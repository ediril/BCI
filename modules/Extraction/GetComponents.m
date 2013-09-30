function [additive_components, components, constant] = GetComponents(model)
    
    [si,ei,ext,additive_components] = regexp( model, '[^\+\s]*'); % Capture any non-whitespace strings between plus signs
    %num_comps = length( additive_components);
    constant_term_idx = strmatch( '1', additive_components, 'exact');
    components = additive_components;
    if( isempty( constant_term_idx))
        constant = 'off';
    else
        if( constant_term_idx ~= 1)
            error(['Constant term should be the first in the model: "' model '"']);
        end
        additive_components(constant_term_idx) = [];
        constant = 'on';
    end