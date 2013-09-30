function Indices = GetRelativeRefIndices(EventSeqNos, ReferenceSeqNos, search_dir)

    % For each event occurrence, find where its sequence number
    % falls within the reference message sequence numbers
    %
    % NOTE: This function will downsample input events using reference
    %       events. Make sure input events have been pre-filtered such
    %       that only unique ones remain between reference events. 
    %       Otherwise, they'll get lost

    search_after = 0; 
    if exist('search_dir', 'var') && strcmp(search_dir, 'after')
        search_after = 1;
    end
    
    Indices.idx = nan( size( EventSeqNos));
    Indices.seqno = nan( size( EventSeqNos));
    Indices.valid = false( size( EventSeqNos));
    
    for i = 1 : length( EventSeqNos)
        ev_seq_no = EventSeqNos(i);
        
        if search_after
            idx = find(ReferenceSeqNos >= ev_seq_no, 1, 'first');
        else
            idx = find(ReferenceSeqNos <= ev_seq_no, 1, 'last');
        end
        
        if( ~isempty(idx))
            if ((i>1) && (Indices.idx(i-1) == idx)), Indices.valid(i-1) = false; end
            Indices.idx(i) = idx;
            Indices.seqno(i) = ReferenceSeqNos(idx);
            Indices.valid(i) = true;
        else
            Indices.idx(i) = nan;
            Indices.seqno(i) = nan;
            Indices.valid(i) = false;
        end
    end
