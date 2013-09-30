function GiveReward( level)
% GiveReward( LEVEL)
%
% Opens the solenoid valve to issue a liquid reward for LEVEL*10ms.
% should be renamed "giverewardorpunishment" or something

global XM;
global DF;

reward_data = DF.MDF.GIVE_REWARD;
reward_data.duration_ms = level(1) * 10;

%fprintf('--------->reward level: %d\n', level);

if(length(level) > 1 || level > 0)
	if(length(level) == 6)
		if(~isfield(XM.runtime, 'reward_countdown') || XM.runtime.reward_countdown == 0)
			addyBit = round(randn(1) * level(6));
			if((addyBit + level(5)) < 1)
				XM.runtime.reward_countdown = 1;
			else	
				XM.runtime.reward_countdown = level(5) + addyBit;
			end
			reward_data.num_clicks = level(3);

		else
			XM.runtime.reward_countdown = XM.runtime.reward_countdown-1;
			reward_data.num_clicks = level(2);
		end			
	elseif(length(level) == 5)
		if(~isfield(XM.runtime, 'reward_countdown') || XM.runtime.reward_countdown == 0)
			XM.runtime.reward_countdown = level(5);
			reward_data.num_clicks = level(3);
		else
			XM.runtime.reward_countdown = XM.runtime.reward_countdown-1;
			reward_data.num_clicks = level(2);
		end
	elseif(length(level) == 4)
	if(~isfield(XM.runtime,'persistent_reward_level'))
		XM.runtime.persistent_reward_level = level(2);	
		else
			if(XM.runtime.persistent_reward_level < level(3))
				XM.runtime.persistent_reward_level = XM.runtime.persistent_reward_level + 1;
			end
		end
		reward_data.num_clicks = XM.runtime.persistent_reward_level;
	elseif(length(level) ==3)
		sample = abs(rand);
		if(sample > 0.9)
			reward_data.num_clicks = level(3);
		else
			reward_data.num_clicks = level(2);
		end	
	elseif(length(level) == 1 && level > 0)
		reward_data.num_clicks = 1;
	end 
	SendMessage( 'GIVE_REWARD', reward_data);
	%fprintf('\nmonkey got some rewards, yeeey!!!\n');
end

