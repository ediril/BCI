function EventIndices = GetEventIndices( QL, EventMsgName, ReferenceMsgName)

% EventIndices = GetEventIndices( QL, EventMsgName, ReferenceMsgName)
%
% Extracts indices in the continuously sampled data that come right
% after each occurrence of a named asynchronous event.
%
% INPUTS:
%  EventMsgName     - Name of the asynch event message whose indices
%                     you want to find
%  ReferenceMsgName - Name of a periodically sampled message
%                     (i.e. one that has a sample_header) to be
%                     used as the reference for determining the
%                     event indices
%  QL               - The data log from the Intermediate format that contains the
%                     actual data
%
% OUTPUTS:
%  EventIndices     - Indices into the aligned sampled data at
%                     which the event occurred

    reference_sequence_nos = QL.SequenceNo.(ReferenceMsgName);
    event_sequence_nos = QL.SequenceNo.(EventMsgName);
    EventIndices = nan( size( event_sequence_nos));
    % For each event occurrence, find where its sequence number
    % falls within the reference message sequence numbers
    for i = 1 : length( event_sequence_nos)
        ev_seq_no = event_sequence_nos(i);
        idx = find( reference_sequence_nos > ev_seq_no);
        if( length( idx) > 0)
            event_idx = idx(1);
        else
            event_idx = nan;
        end
        EventIndices(i) = event_idx;
    end
    