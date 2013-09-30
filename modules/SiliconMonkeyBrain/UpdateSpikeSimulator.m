function SimulatorState = UpdateSpikeSimulator(SimulatorState, target)
%   SimulatorState.target = target ./ SimulatorState.norm2real;
%   targMatrix = repmat(target, SimulatorState.Units.params.nUnits, 1);

  target(isnan(target)) = 0;

  targMatrix = repmat(target .* SimulatorState.norm2real, SimulatorState.Units.params.nUnits, 1);

  modulatedPerDimActivity = SimulatorState.Units.params.modulation .* targMatrix ;
  modulatedNormalizedActivity = sum(modulatedPerDimActivity,2);

  modulatedRelativeActivity = modulatedNormalizedActivity .* SimulatorState.Units.params.moddepth;

  modulatedRawActivity = SimulatorState.Units.params.meanRates + modulatedRelativeActivity;

  modulatedActivity = modulatedRawActivity;
  if strcmp(SimulatorState.limits, 'on')
      fastCells = find(modulatedRawActivity > SimulatorState.Units.params.ceiling);
      slowCells = find(modulatedRawActivity < SimulatorState.Units.params.floor);
      %fprintf('fast=%d  slow=%d\n', length(fastCells), length(slowCells));
      modulatedActivity(fastCells) = SimulatorState.Units.params.ceiling(fastCells);
      modulatedActivity(slowCells) = SimulatorState.Units.params.floor(slowCells);
  end

  SimulatorState.spikeRates = modulatedActivity';

  % Add gaussian noise to firing rate
  noise = random( 'Normal', 0, SimulatorState.NoiseLevel, size( SimulatorState.spikeRates));
  SimulatorState.spikeRates = SimulatorState.spikeRates + noise;


  if strcmp(SimulatorState.quantization, 'narrow')
      spikeCount = floor(SimulatorState.spikeRates * SimulatorState.BinTime);
      remainder = SimulatorState.spikeRates * SimulatorState.BinTime - spikeCount;
      randSample = rand(1, SimulatorState.Units.params.nUnits);
      firedCells = find(randSample < remainder);
      spikeCount(firedCells) = spikeCount(firedCells) + 1;

  elseif strcmp(SimulatorState.quantization, 'poisson')
      spikeCount = poissrnd(SimulatorState.spikeRates * SimulatorState.BinTime);
  end

  SimulatorState.curSampleSpikeCount = spikeCount;

end
