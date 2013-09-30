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

    if isfield(Options, 'NoiseModel')
        NoiseModel = Options.NoiseModel;
    else
        NoiseModel = 'normal';
    end

    if( Options.verbose == 1), disp(['Using noise model "' NoiseModel '"']); end

    if( ~isfield(Options, 'Delay'))
        Options.Delay = 0;
    end

    % Select firing rates from specified cells and samples
    if ~strcmp(NoiseModel, 'normal')
        fprintf('\n\nWARNING: NoiseModel parameter does not match expected value. Using "normal" instead\n\n');
        NoiseModel = 'normal';
    end

    if ( isfield(Options, 'type') && strcmp(Options.type, 'rate'))
        FiringRate = Data.FiringRate;
    else
        FiringRate = FilterSpikeCounts(Data, Options.AdaptationFilterCoeffs);
    end
    
    if( isfield(Options, 'CellMask') && ~isempty(Options.CellMask))
        FR = FiringRate(Options.CellMask,:);
    else
        FR = FiringRate;
    end

    % Assume model to be a string of the form, e.g. "1+avx+avy+avz" meaning
    % that it has a constant term, and additive terms for actual velocity x,y
    % and z components
    [additive_components, Components, constant] = GetComponents(Options.Model);
    num_comps = length( Components);

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
    num_cells = size( FR, 1);
    B = nan( num_cells, num_comps);
    DLY = nan( num_cells, 1);
    R2 = zeros( num_cells, 1);
    SPIKES = zeros( num_cells, sum(Options.SampleMask));
    Qt = Q'; %clear Q;
    if( Options.verbose == 1), disp(['Running regression for ' num2str(num_cells) ' cells:']); end
    for i = 1 : num_cells
        
        % Iterate tuning function estimation a few times to find optimal delay
        bs = [];
        devs = [];
        for delay = Options.Delay
            f = double( FR(i,:));
        
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
        dly = Options.Delay(min_idx);
        rss = min_dev;

        B(i,:) = b';
        DLY(i) = dly;

        f = double( FR(i,:));
        % Delay the firing rates by the specified number of samples
        f = [nan( 1, dly) f(1:end-dly)];
        if( isfield(Options, 'SampleMask') && ~isempty(Options.SampleMask))
            f = f(:,Options.SampleMask);
        end
        SPIKES(i,:) = f;

        mt = nanmean(f);
        dev = nansum((f - mt).^2);        
        R2(i) = rss / dev;
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
    TF.FullB = B;
    TF.Coeff = B;
    TF.Delay = DLY;
    TF.Model = Options.Model;
    TF.Components = Components;
    TF.PredictiveCellsMask = true(1, size(B,1));
    TF.R2 = R2;
    TF.ModDepths = moddepths;
    TF.Data.FRateBuffer = SPIKES;
    TF.Data.TargetBuffer = Qt;
