function magnitude = mag( vector)

    if (size(vector,1) < 2)
        magnitude = vector;
        return;
    end

    magnitude = sqrt( sum( vector.^2));
