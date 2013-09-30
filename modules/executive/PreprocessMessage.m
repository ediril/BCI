function M = PreprocessMessage( id, M, ExpectedMessageTypes)

% M = PreprocessMessage( M, ExpectedMessageTypes)
%
% Proprocess a message when it is received from the Module's pipe, so as to
% call an event hook, act on common exit signals and deal with timer
% messages

% Meel Velliste, April 2006
    
    global DF_runtime;

    % Call event hook
    if( isfield( DF_runtime, 'EventHook'))
        M = feval( DF_runtime.EventHook, M);
    end
    
    if( ~isempty( M))
        switch( M.msg_type)
			case 'JUDGE_VERDICT'
                if (id ~= M.data.id)
                    M = [];
                    return;
                else
                    M.data.reason = deblank(char(M.data.reason));
                end
        end
        isAnExpectedMessage = ~isempty( strmatch( M.msg_type, ExpectedMessageTypes, 'exact'));
        if( ~isAnExpectedMessage)
            M = [];
            %return;
        end
    end
