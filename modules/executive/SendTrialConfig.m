function SendTrialConfig( )
% SendTrialConfig( )
%
% Send out informational message that says how this trial is configured (for anyone that cares)

global XM;
global DF;

if iscell(XM.config.task_state_config.reward)
    % count "not zero" & "not invalid characters/values"
    cnt_rewards = sum(~strcmp(XM.config.task_state_config.reward, '0') & ...
                    ~cellfun(@isempty, (regexp(XM.config.task_state_config.reward, '^[e]*\d+$', 'match'))));
else
    cnt_rewards = sum(XM.config.task_state_config.reward > 0);
end

tc = DF.MDF.TRIAL_CONFIG;
tc.rep_no(1) = XM.rep_num;
tc.trial_no(1) = XM.trial_num;
tc.num_reward_states(1) = int32(cnt_rewards);
SendMessage( 'TRIAL_CONFIG', tc);
