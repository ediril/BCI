%function SimulatorState = InitializeSpikeSimulator(nUnits, nDims, noiseLevel, b0, md, norm2real, freq)
function SimulatorState = InitializeSpikeSimulator(config)

  if ~exist('idle', 'var'),  idle = 0;  end

  gduparams.nUnits = config.number_of_units;
  gduparams.nDims = config.number_of_dims;
  gduparams.meanRates = config.b0 * ones(gduparams.nUnits,1);
  gduparams.moddepth = config.md * ones(gduparams.nUnits, 1);
  gduparams.floor = 0.0 * ones(gduparams.nUnits, 1);
  gduparams.ceiling = gduparams.meanRates + (10 * config.md * ones(gduparams.nUnits, 1));
  SimulatorState.Units = generateDistributedUnits(gduparams);
  SimulatorState.BinTime = 1 / config.freq;
  SimulatorState.NoiseLevel = config.noise_level;
  SimulatorState.norm2real = config.norm2real;
  SimulatorState.limits = config.limits;
  SimulatorState.quantization = config.quantization;
end

function Units = generateDistributedUnits(params)
  Units.params = params;
  Units.id = [0:(params.nUnits)-1]';
  Units.params.modulation = zeros(params.nUnits, params.nDims);
  unitsPerDim = floor(params.nUnits / params.nDims);
  if(mod(unitsPerDim, 2) == 1)
    unitsPerDim = unitsPerDim - 1;
  end

  unitsPerModDir = unitsPerDim / 2;
  for(offset = 0:(params.nDims-1))
    for j=1:unitsPerDim
      if(j > unitsPerModDir)
        posNegMod = -1;
      else
        posNegMod = 1;
      end
      Units.params.modulation(offset * unitsPerDim + j, 1+offset) = posNegMod;
    end
  end
end
