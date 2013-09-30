function [fData, iData, fData_incr_state, iData_incr_state] = Raw2Formatted(dir, fData_incr_state, iData_incr_state)
%RAW2FORMATTED calls raw2intermediate on the data found in the directory
%     argument, loading a structure 'Data' into the workspace.
% 
%     Data = Raw2Formatted(dir)
% 
% Mike Mournighan

    if( exist( 'iData_incr_state', 'var'))
     	[iData, iData_incr_state] = Raw2Intermediate(dir, iData_incr_state);
    else
        iData = Raw2Intermediate(dir);
    end
    if exist(fullfile(dir,'FixIntermediate.m'),'file')
        addpath(dir);
        iData = FixIntermediate(iData);
        rmpath(dir);
    end
    if( isempty( iData))
        fData = [];
    else
        if( exist( 'fData_incr_state', 'var'))
            [fData, fData_incr_state] = Intermediate2Formatted(iData, fData_incr_state);
        else
            fData = Intermediate2Formatted(iData);
        end
    end    
