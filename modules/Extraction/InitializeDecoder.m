function Decoder = InitializeDecoder(DecoderType)

    switch( DecoderType)
        case {'lf','LinearFilter'}
            error('Sorry, LinearFilter not implemented yet1');

        case {'pva','PopulationVector'}
            Decoder = PopulationVector( );

        case {'ole','OptimalLinearEstimator'}
            Decoder = OptimalLinearEst( );
            
        case {'kf','KalmanFilter'}
            error('Sorry, KalmanFilter not implemented yet1');

        case {'pf','ParticleFilter'}
            error('Sorry, ParticleFilter not implemented yet1');

        case {'lgf','LaplaceGaussianFilter'}
            Decoder = LaplaceGaussianFilter( );

        otherwise
            error( ['Unrecognized Decoder type ''' DecoderType '''!']);
    end