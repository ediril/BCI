% Decodes dim using spike counts.
function [prediction, lgf] = lgf_predict(lgf, counts, tf_offset)
    amask = lgf.activity_mask>0;
    
    baseline = lgf.baseline(amask);
    if( exist( 'tf_offset', 'var'))
        tf_offset = tf_offset(amask);
        if( any( isnan( tf_offset)))
            % don't add the offset if it's nan
        else
            baseline = baseline + tf_offset;
        end
    end
    
    % Timestep length is always the same so we just use 1.
    [lgf.x, lgf.V] = filter_1step(lgf.x,...
                                   lgf.V,...
                                   double(counts(amask))...
                                   ,1,...
                                   lgf.var,...
                                   lgf.F,...
                                   lgf.prefdirs(:,amask),...
                                   baseline,...
                                   lgf.regressor_func);
    
    prediction = lgf.x;
end
