function [this, TF] = Calibrate(this, Data, Options)
% TF = CalcTuningFunctions( Data, Options)
%
% Calculates tuning functions from Data, where data is the common data
% format returned by the Import*.m scripts. Returns a reference to the
% modified object (because it remembers the tuning functions for further
% analysis) and the tuning functions TF, a struct containing the fields:
% Model - a string representing the model for the tuning function
% Coeff - calibrated model coefficients

    if ~isfield(Options, 'verbose')
        Options.verbose = 1;
    end

    if( isfield(Options, 'NoiseModel'))
        NoiseModel = Options.NoiseModel;
    else
        NoiseModel = 'normal';
    end

    if( Options.verbose == 1), disp(['Using noise model "' NoiseModel '"']); end

    if( ~isfield(Options, 'Delay'))
        Options.Delay = 0;
    end

    % Select firing rates from specified cells and samples
    switch (NoiseModel)
        case 'normal'
            FiringRate = FilterSpikeCounts(Data, Options.AdaptationFilterCoeffs);
        case 'poisson'
            FiringRate = Data.SpikeCount;
    end
    
    if( isfield(Options, 'CellMask') && ~isempty(Options.CellMask))
        F = FiringRate(Options.CellMask,:);
    else
        F = FiringRate;
    end

    % Assume model to be a string of the form, e.g. "1+avx+avy+avz" meaning
    % that it has a constant term, and additive terms for actual velocity x,y
    % and z components
    [si,ei,ext,additive_components] = regexp( Options.Model, '[^\+\s]*'); % Capture any non-whitespace strings between plus signs
    num_comps = length( additive_components);
    constant_term_idx = strmatch( '1', additive_components, 'exact');
    Components = additive_components;
    if( isempty( constant_term_idx))
        constant = 'off';
    else
        if( constant_term_idx ~= 1)
            error(['Constant term should be the first in the model: ''' Options.Model '''']);
        end
        additive_components(constant_term_idx) = [];
        constant = 'on';
    end

    RawQ = GetQuantities( Data, [], additive_components);
    
    % filter the quantities to match the filtering delay of the firing rates
    if ( isfield(Options, 'type') && strcmp(Options.type, 'rate'))
        Q = RawQ;
    else
        Q = filter( Options.TargetFilterCoeffs, 1, RawQ, [], 2);
    end

    if( isfield(Options, 'SampleMask') && ~isempty(Options.SampleMask))
        Q = Q(:, Options.SampleMask);
    end
    

    % Do the regression on each cell
    num_cells = size( F, 1);
    B = nan( num_cells, num_comps);
    D = nan( num_cells, 1);
    Qt = Q'; %clear Q;
    if( Options.verbose == 1), disp(['Running regression for ' num2str(num_cells) ' cells:']); end
    for i = 1 : num_cells

        % Iterate tuning function estimation a few times time find optimal delay
        bs = [];
        devs = [];
        for delay = Options.Delay
            f = double( F(i,:));

            % Delay the firing rates by the specified number of samples
            f = [nan( 1, delay) f(1:end-delay)];

            if( isfield(Options, 'SampleMask') && ~isempty(Options.SampleMask))
                f = f(:,Options.SampleMask);
            end

            [b, dev, stats] = glmfit( Qt, f', NoiseModel, 'constant', constant);
            bs = [bs b];
            devs = [devs dev];
        end
        % Pick the best delay based on deviance, and take the b coefficients
        % for that delay
        [min_dev, min_idx] = min( devs);
        b = bs(:,min_idx);
        d = Options.Delay(min_idx);

        B(i,:) = b';
        D(i) = d;

        %fprintf(' [');
        %fprintf(' %.0f', devs);
        %fprintf('] %i\n', d);
        %fprintf('.%i', d)
    end
    if( Options.verbose == 1), disp('Done!'); end

    % % Calculate mean and std of training data for later reference
    % switch( class( F))
    %     case 'double'
    %         MeanF = nanmean( F, 2);
    %         StdF = nanstd( F, 0, 2);
    %     otherwise
    %         MeanF = nanmean( double(F), 2);
    %         StdF = nanstd( double(F), 0, 2);
    % end

    % Create structured output
    TF = [];
    TF.FullB = [];
    TF.Coeff = B;
    TF.Delay = D;
    TF.Model = Options.Model;
    TF.Components = Components;
    TF.PredictiveCellsMask = true(1, size(B,1));
    %TF.Data.FRateBuffer = SPIKES;
    TF.Data.TargetBuffer = Qt;
    %TF.Data.TargetNormalizeMags = targetNormalizeMags;
    %TF.Data.invSigmaMatrix = invSigmaMatrix;
