function Data = MergeIntermediateData(pre_data, post_data)

    pre_data.Version = '';
    pre_data.DF = [];

    ToBeMerged = [pre_data, post_data];
    Data = CatStructFields(ToBeMerged, 'horizontal', 'merge-fields');
