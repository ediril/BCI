function AbsoluteDir = GetAbsoluteDir( RelativeDir)

% AbsoluteDir = GetAbsoluteDir( RelativeDir)
%
% Get absolute directory path given a relative path (relative to 
% present working directory).

PresentWorkingDirectory = pwd( );
cd( RelativeDir);
AbsoluteDir = pwd( );
cd( PresentWorkingDirectory);
