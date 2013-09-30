function Log = SeparateMultiModMessages( Log, RTMA)

% Log = SeparateMultiModMessages( Log, RTMA)
%
% Take continuous data message types where the same message type is
% sent by multiple different modules, and promote the messages from
% different modules to their own independent message types with the
% module name appended to the message name. The purpose of this is
% to separate independent data streams that would otherwise be seen
% as one.

% Meel Velliste 4/5/2010


% Identify message types that are "continuous" data
ContTypes = {};
MessageTypes = fieldnames( Log.Data);
for mt = 1 : length( MessageTypes)
    MT = MessageTypes{mt};
    if( isfield( Log.Data.(MT), 'sample_header'))
        ContTypes = [ContTypes; {MT}];
    end
end

% Find which continuous datma types have multiple source module ID-s
HighLevelFields = fieldnames( Log);
for mt = 1 : length( ContTypes)
    MT = ContTypes{mt};
    SID = Log.Headers.(MT).src_mod_id;
    USID = unique( SID);
    NUSID = length( USID);
    if( NUSID > 1)
        % Found message type with multiple source module ID-s!
        % Now, go forth and separate the messages as if they were
        % a separate message type from each module
        for i = 1 : NUSID
            sid = USID(i);
            source_name = GetModName_by_MID( sid, RTMA);
            new_MT = [MT '_' source_name];
            source_mask = (SID == sid);
            for h = 1 : length( HighLevelFields)
                high_level_field = HighLevelFields{h};
                old_stuff = Log.(high_level_field).(MT);
                Log.(high_level_field).(new_MT) = ApplyMask( old_stuff, source_mask);
            end
        end
        % Delete the old message type
        for h = 1 : length( HighLevelFields)
            high_level_field = HighLevelFields{h};
            Log.(high_level_field) = rmfield( Log.(high_level_field), MT);
        end
    end
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function ModName = GetModName_by_MID( MID, RTMA)
% ModName = GetModName_by_MID( MID, RTMA)
%
% Finds the name of a module in the RTMA struct
% given a numeric module ID (MID)

ModNames = fieldnames( RTMA.MID);
MIDss = struct2cell( RTMA.MID);
MIDs = [MIDss{:}];
index = find( MIDs == MID);
if ~isempty(index)
    ModName = ModNames{index};
else
    ModName = ['MID_' num2str(MID)];
end
    
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Applies at end of every branch in struct tree
function data = ApplyMask( data, mask)

    data_type = class( data);
    switch( data_type)
        case 'struct'
            FieldNames = fieldnames( data);
            for i = 1 : length( FieldNames)
                fn = FieldNames{i};
                data.(fn) = ApplyMask( data.(fn), mask);
            end
        otherwise
            data = data(:,mask);
    end
    