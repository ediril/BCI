function SendDebugVector( TheVector)

% SendDebugVector( TheVector)
%
% Sends a DEBUG_VECTOR message with TheVector as its payload. Try using
% this in conjunction with the SimpleDebugDisplay module to get a live plot
% of any data values. The DEBUG_VECTOR message can accomodate up to 32
% elements in the vector. If you input TheVector with more than 32 elements
% then the extra elements will be chopped off.


    global DF;
    debug_data = DF.MDF.DEBUG_VECTOR;
    L = min( length(TheVector), length( debug_data.data));
    debug_data.data(1:L) = TheVector(1:L);
    SendMessage( 'DEBUG_VECTOR', debug_data);
