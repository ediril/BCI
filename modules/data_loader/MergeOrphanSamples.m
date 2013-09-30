function [Log, IncrState] = MergeOrphanSamples( Log, IncrState)

    if isempty(IncrState.OrphanSamples)
        return
    end

    ToBeMerged = [IncrState.OrphanSamples, Log];
    Log = CatStructFields(ToBeMerged, 'horizontal', 'merge-fields');
    IncrState.OrphanSamples = {};
