function M = WaitFor( id, varargin)

% Message = WaitFor( ExpectedMsgType1, ExpectedMsgType2, ...)
%
% Wait for a message of one of the expected types. The function also
% calls an event hook and checks for common exit messages and acts upon
% them.
%
% Warning: this function is very inefficient due to its use of strmatch.

    % Verify that the requested message_types exist
    for i = 1 : nargin-1
        CheckMessageTypeExist( varargin{i});
        CheckSubscribed( varargin{i});
    end
    
    % Wait for message
    M = [];
    while( isempty( M))
        M = ReadMessage( 'blocking');
        M = PreprocessMessage( id, M, varargin);
    end
