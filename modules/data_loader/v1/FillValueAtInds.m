function [ filled ] = FillValueAtInds( values, inds, bins, start, default)
%FillValueAtInds Makes a vector `samples` long with values 
% taken incrementally from `values`, incrementing at `inds`.
% Values are filled from each `ind` to the next `ind`.
% Now works for 1- and 2-d.
%
% Examples
% --------
% values = [0 1 3 4  5  7  7  9]
% inds   = [1 3 5 9 10 13 15 17]
% bins   = 20
% FillValueAtInds( values, inds, bins) = ...
%       [0 0 1 1 3 3 3 3 4  5  5  5  7  7  7  7  9  9  9  9]
% inds=( 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 )
%
% values = [[0 1 3 4]; [0 2 1 9]]
% inds   = [1 4 5 7]
% bins   = 8
% FillValueAtInds( values, inds, bins) = ...
%       [[0 0 0 1 3 3 4 4]; [0 0 0 2 1 1 9 9]]
% inds=(  1 2 3 4 5 6 7 8)
%
% values = [[0 1 3 4]; [0 2 1 9]]
% inds   = [2 3 5 7]
% bins   = 8
% FillValueAtInds( values, inds, bins) = ...
%       [[Nan 0 1 1 3 3 4 4]; [Nan 0 2 2 1 1 9 9]]
% inds=(    1 2 3 4 5 6 7 8)

    if ~exist('default', 'var'); default=nan; end
    
    % get rid of any nans in inds
    inds = inds(~isnan(inds));
    
    if inds(1) > 1
        values = [repmat(default, [size(values, 1) 1]) values];
    end
        
    lookup = zeros(1, bins);
    % need to make inds suitable for indexing along last
    % dimension of lookup
    lookup(inds) = 1;
    lookup(1) = 1; % make first value 1 so that indices never have 0 values
    lookup = cumsum(lookup);
    filled = values(:,lookup);
    
    % fill in values for trailing empty spots (that was supposed to
    % extend if the previous run had continued)
    if exist('start', 'var')
        if ~isempty(start)
            if isinteger(values(1))
                idx = find(filled(1,:)==0);
            else
                idx = find(isnan(filled(1,:))==1);
            end
            
            for c = 1 : length(idx)
                filled(:, c) = start;
            end
        end
    end

