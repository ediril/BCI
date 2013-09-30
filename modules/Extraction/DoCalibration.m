function [CM, EMDecoderConfig] = DoCalibration(CM, Data, Decoder)

    if(CM.config.NumAdaptReps < 0)
        CM.AdaptRepRange = 1 : CM.CurrentRepID;
    else
        CM.AdaptRepRange = (CM.CurrentRepID - CM.config.NumAdaptReps + 1) : CM.CurrentRepID;
        % remove nonsensical repIDs
        CM.AdaptRepRange(CM.AdaptRepRange<1) = [];
    end

    if (CM.config.verbose == 1)
        fprintf('reps used: '); fprintf('%d ', CM.AdaptRepRange);  fprintf('\n');
    end

    mask = false(1, length(Data.BlockNo));
    for r = 1 : length(CM.AdaptRepRange)
        mask = mask | (Data.BlockNo == CM.AdaptRepRange(r));
    end

    %%if ~isfield(Data,'Idle') || isempty(fieldnames(Data.Idle))
    %    CM.config.SampleMask = mask & Data.OtherMasks.UsedForCalib;
    %%else
    %%    CM.config.SampleMask = mask & Data.OtherMasks.UsedForCalib & ~Data.Idle.idle;
    %%end
    mask = mask & Data.OtherMasks.UsedForCalib;
    if isfield(CM.config, 'ExcludeIdle') && (CM.config.ExcludeIdle == 1)
        if isfield(Data,'Idle') && ~isempty(fieldnames(Data.Idle))
            mask = mask & ~Data.Idle.idle;
        end
    end
    CM.config.SampleMask = mask;

    if (CM.config.verbose == 1)
        fprintf('Using %d out of %d bins for calibration\n', sum(CM.config.SampleMask), length(CM.config.SampleMask));
    end

    [Decoder EMDecoderConfig] = Calibrate(Decoder, Data, CM.config);

    EMDecoderConfig.ActiveChannelIndex = find(Data.ActiveChannelMask > 0);
