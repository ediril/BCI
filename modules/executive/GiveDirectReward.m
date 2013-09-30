function GiveDirectReward(level)

global DF;

reward_data = DF.MDF.GIVE_REWARD;
reward_data.duration_ms =level;
reward_data.num_clicks = 1;
SendMessage( 'GIVE_REWARD', reward_data);