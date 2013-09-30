function M = WaitForAsync( id, timeout, varargin)

% Message = WaitFor( ExpectedMsgType1, ExpectedMsgType2, ...)
%
% Wait for a message of one of the expected types. The function also
% calls an event hook and checks for common exit messages and acts upon
% them.
%
% Warning: this function is very inefficient due to its use of strmatch.

    % Verify that the requested message_types exist
    for i = 1 : nargin-2
        CheckMessageTypeExist( varargin{i});
        CheckSubscribed( varargin{i});
    end
    
    % Wait for message
    while( 1)
        M = ReadMessage( 0.1);
        if isempty(M)
            timeout = timeout - 1;
            if timeout == 0
                error('ERROR: Unable to flush QuickLogger');
            end
        else
            M = PreprocessMessage( id, M, varargin);
            if ~isempty(M), break; end
        end
    end
