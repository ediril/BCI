function FR = FilterSpikeCounts(Data, Filter)
    RawFR = double(Data.SpikeCount) / Data.Dt;
    FR = filter( Filter, 1, RawFR, [], 2);
