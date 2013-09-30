%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%	
function [filled] = FillStateAtInds(ix, ref_inds, bins, start)

    filled = false(1, bins);

    if exist('start', 'var')
        upto_idx = ref_inds(1);
        if (~isempty(ix) && (ix(1) < ref_inds(1))), upto_idx = ix(1); end
        filled(1:upto_idx-1) = start;
    end
    
    if (~isempty(ix))
        for k = 1 : length(ix)
            if (ix(k) == ref_inds(end))
                filled(ix(k):bins) = 1;
            else     
                i = find(ix(k)==ref_inds, 1, 'last');
                filled(ix(k):ref_inds(i+1)-1) = 1;
            end
        end
    end
    