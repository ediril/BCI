function Q = GetQuantities( Data, Traj, QuantityDescriptors, SampleMask)

% Q = GetQuantities( Data, Traj, QuantityDescriptors, SampleMask)
% 
% Gets a specified quantity out of the Data where Data is the standard data
% structure output by the Import*.m scripts and QuantityDescriptors is a 1xD
% cell array of strings that specifies the quantities of interest, e.g. 'avx' for
% x-component of actual velocity or 'cpz' for z-component of command
% position, or 'pc1' for principal component 1 of the neural data. The
% output Q is a DxN matrix of the requested quantities over N sample points.
% If principal components requested, then the third argument Traj must be
% given the contains a neural trajectory (from GetNeuralTraj.m).

if( ~exist( 'SampleMask', 'var'))
    SampleMask = [];
end

D = length( QuantityDescriptors);
if( isempty( SampleMask))
    N = length( Data.TrialNo);
else
    N = sum( SampleMask);
end
Q = nan( D, N);
for d = 1 : D
    quantity_descriptor = QuantityDescriptors{d};
    if( isequal( quantity_descriptor(1:2), 'pc'))
        data = Traj;
    else
        data = Data;
    end
    q = GetQuantity( data, quantity_descriptor, SampleMask);
    Q(d,:) = q;
end
