function SiliconMonkeyBrain(config_filename, mm_ip)

  global DF;

   if(~exist('ModuleID','var'))
    ModuleID = 'SILICON_MONKEY_BRAIN';
   end

   Dragonfly_BaseDir = getenv('DRAGONFLY');
   App_IncludeDir = getenv('BCI_INCLUDE');
   CommonPath = getenv('BCI_COMMON');

   MessageTypes = { ...
                    'PLANNER_MOVEMENT_COMMAND'...
                    'EXIT' ...
                    'PING' ...
                  };

   addpath([Dragonfly_BaseDir '/lang/matlab']);
   addpath([CommonPath '/matlab']);


   %
   % Make sure config file exists and load it
   %
   config = [];
   if( exist( 'config_filename', 'var'))
       if( ~exist( config_filename, 'file'))
           error(['Cannot find config file: ' config_filename]);
       end
       config = LoadTextData( config_filename);
   end

   ConnectArgs = {'SILICON_MONKEY_BRAIN', Dragonfly_BaseDir, [App_IncludeDir '/Dragonfly_config.mat']};
   if exist('mm_ip','var') && ~isempty(mm_ip)
     ConnectArgs{end+1} = ['-server_name ' mm_ip];
   end

   while(1)
     ConnectToMMM(ConnectArgs{:});
     if isempty(config)
        config = struct();
        config.number_of_units = length(DF.MDF.SPM_SPIKECOUNT.counts);
        config.number_of_dims = length(DF.MDF.PLANNER_MOVEMENT_COMMAND.vel);
        config.noise_level = 0;
        config.b0 = 6400;
        config.md = 3200;
        config.norm2real = repmat(1, 1, config.number_of_dims);
        config.freq = 50;
        config.output = 'count';
        config.limits = 'on';
        config.quantization = 'poisson';
     end

     SimulatorState = InitializeSpikeSimulator(config);
     SimulatorState.idle = 0;

     save ('SMB.mat', 'SimulatorState');

     Subscribe( MessageTypes{:})
     SendModuleReady( );

     disp 'SiliconMonkeyBrain running..'

     SimulatorState = UpdateSpikeSimulator(SimulatorState, DF.MDF.PLANNER_MOVEMENT_COMMAND.vel);

%      % send calibration info to EM
%      EMDecoderConfig = struct();
%      mod_idx = logical(norm2real);
%      offsets = SimulatorState.Units.params.meanRates;
%      modulation = SimulatorState.Units.params.modulation(:, mod_idx);
%      moddepth = repmat(SimulatorState.Units.params.moddepth, 1, sum(mod_idx)) * (nUnits/nDims);
%      prefdirs = modulation ./ moddepth;
%      EMDecoderConfig.Coeff = [offsets prefdirs];
%      EMDecoderConfig.Components = {'1'};
%      SendEMDecoderConfig(EMDecoderConfig);

     if strcmp(config.output, 'count')
         msg = DF.MDF.SPM_SPIKECOUNT;
         msg.source_timestamp = 0.0;
         msg.count_interval = SimulatorState.BinTime;
         nUnits = length(SimulatorState.curSampleSpikeCount);
         msg.counts(1:nUnits) = SimulatorState.curSampleSpikeCount;
         SendMessage('SPM_SPIKECOUNT', msg);
     elseif strcmp(config.output, 'rate')
         msg = DF.MDF.SPM_FIRINGRATE;
         msg.source_timestamp = 0.0;
         msg.count_interval = SimulatorState.BinTime;
         nUnits = length(SimulatorState.curSampleSpikeCount);
         msg.rates(1:nUnits) = SimulatorState.spikeRates;
         SendMessage('SPM_FIRINGRATE', msg);
     else
         DisconnectFromMMM
         exit
     end

     while(1)

       M = [];
       while( isempty( M))
         M = ReadMessage( 'blocking');
         if(isscalar(M) && ~isstruct(M) && M == -1)
           disp('FUUUUUUUUUUUUU');
           break;
         end

         SimulatorState = ProcessMessage(M, config, SimulatorState);

       end
    end

   end

end


function [SimulatorState] = ProcessMessage(M, config, SimulatorState)

  global DF;
  persistent serialNumber;

  if(isempty(serialNumber))
    serialNumber = 1;
  else
    serialNumber = serialNumber + 1;
  end


  switch(M.msg_type)

    case 'EXIT'
        if (M.dest_mod_id == GetModuleID()) || (M.dest_mod_id == 0)
            SendSignal EXIT_ACK
            DisconnectFromMMM
            exit
        end    
    
    case 'PING'
        RespondToPing(M, 'SiliconMonkeyBrain');
    
    case 'PLANNER_MOVEMENT_COMMAND'
        target = M.data.vel;
        SimulatorState = UpdateSpikeSimulator(SimulatorState, target);
        fprintf(1, '?');

        if strcmp(config.output, 'count')
            msg = DF.MDF.SPM_SPIKECOUNT;
            msg.sample_header = M.data.sample_header;
            msg.source_timestamp = 0.0;
            msg.count_interval = SimulatorState.BinTime;
            nUnits = length(SimulatorState.curSampleSpikeCount);
            msg.counts(1:nUnits) = SimulatorState.curSampleSpikeCount;
            SendMessage('SPM_SPIKECOUNT', msg);
        else
            msg = DF.MDF.SPM_FIRINGRATE;
            msg.sample_header = M.data.sample_header;
            msg.source_timestamp = 0.0;
            msg.count_interval = SimulatorState.BinTime;
            nUnits = length(SimulatorState.curSampleSpikeCount);
            msg.rates(1:nUnits) = SimulatorState.spikeRates;
            SendMessage('SPM_FIRINGRATE', msg);
        end

        fprintf(1, '!');
  end

end

