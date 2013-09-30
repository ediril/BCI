function mats = Rodrigues( vecs)

    % Takes an Nx3 matrix VECS that represents rotation vectors, and turns it
    % into 3x3 rotation matrices, output as a 3x3xN matrix. The resulting
    % matrix is applied by putting a row vector in front of it; or
    % transpose it and then you can put a column vector behind it.

    mags = sqrt( sum( vecs.^2, 2));
    small_ones = mags < eps;
    unit_vecs = vecs ./ repmat( mags, [1 3]);
    unit_vecs(small_ones,:) = repmat( [1 0 0], [sum(small_ones) 1]);
    N = size( vecs, 1);
    mats = zeros( 3, 3, N);
    for i = 1 : N
        mats(:,:,i) = rodrigues_rot( eye(3), unit_vecs(i,:), mags(i));
    end
    