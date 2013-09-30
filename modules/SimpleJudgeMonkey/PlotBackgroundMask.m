function PlotBackgroundMask( x, mask, ylim, color)

% PlotBackgroundMask( x, mask, ylim, color)
%
% Plots color background patches on the current figure at X positions where
% MASK is true, using the specified COLOR (in the standard colorspec
% format, i.e. a letter, name or RGB values). The height of the patches
% will be from YLIM(1) to YLIM(2). If YLIM is empty, then the patches will
% extend from top to bottom of current view. 
% X must be the same length as MASK.
% Also, X is assumed to a be regularly spaced samples.

% Find starts and ends of contiguous regions of true values in mask because
% we want just one patch object per contiguous region
begin_indices = find( diff( [false mask]) == 1);
end_indices = find( diff( [mask false]) == -1);

% Get DeltaX
dx = mean( diff(x));

% Get YLim if it was not given
if( isempty( ylim))
    ylim = get( gca, 'YLim');
end

% For each continuous region, create one patch object
% Each column of X and Y will correspond to one patch object
X = [];
Y = [];
for i = 1 : length( begin_indices)
    b = begin_indices(i);
    e = end_indices(i);
    xb = x(b) - dx/2;
    xe = x(e) + dx/2;
    X = [X, [xb; xe; xe; xb]]; 
    Y = [Y, [ylim(1); ylim(1); ylim(2); ylim(2)]];
end

% Plot all the patch objects in one fell swoop
patch( X, Y, color, 'EdgeAlpha', 0);
