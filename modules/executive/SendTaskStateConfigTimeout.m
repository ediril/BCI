function SendTaskStateConfigTimeout(id, timeout)

    global DF;
    global XM;

    msg = DF.MDF.TASK_STATE_CONFIG;
    msg.id = int32(id);
    msg.rep_num = int32(XM.rep_num);
    msg.ts_time = GetAbsTime( );
    msg.idle_timeout = inf;
    msg.trans_threshold = nan;
    msg.ori_threshold = nan;
    msg.trans_threshold_f = nan;
    msg.ori_threshold_f = nan;
    msg.trans_threshold_judging_polarity = int32(1);
    msg.ori_threshold_judging_polarity = int32(1);
    msg.trans_threshold_f_judging_polarity = int32(1);
    msg.ori_threshold_f_judging_polarity = int32(1);
    msg.finger_threshold = nan(1, DF.defines.MAX_HAND_DIMS);
    msg.timeout = double(timeout);
    SendMessage( 'TASK_STATE_CONFIG', msg);