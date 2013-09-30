%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [session_num, session_dir, session_basepath, last_session_num] = DetermineSessionNumber( )

global XM;

% Create a file name pattern that matches all DoorKnob project data files
% for this subject
subject_basepath = [XM.data_dir '/' XM.subject_name '/Raw/' XM.subject_name '.DK'];
data_file_pattern = [subject_basepath '.*'];
DisplayMessageToUser(['DetermineSessionNumber: Looking for last session number in data files: ' data_file_pattern]);

% Get a directory listing of existing files
D = mv_dir( data_file_pattern);

if( isempty( D))
    last_session_num = [];
    session_num = 1;
    DisplayMessageToUser(['DetermineSessionNumber: There are no prior data files']);
else
    % Get session numbers of the files and find the latest one
    unique_session_nums = get_unique_session_nums( XM.subject_name, D);
    last_session_num = max( unique_session_nums);
    DisplayMessageToUser(['DetermineSessionNumber: Last session number in existing data files is ' num2str(last_session_num)]);
    session_num = last_session_num + 1;
end
DisplayMessageToUser(['DetermineSessionNumber: This session will be number ' num2str( session_num)]);

session_num_str = num2str(session_num,'%.5d');
session_dir = [subject_basepath '.' session_num_str];
%session_lastdir = [XM.subject_name '.DK.' session_num_str];
session_basepath = [session_dir '/']; % XM.subject_name '.DK.' session_num_str];

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function unique_session_nums =  get_unique_session_nums( subject_name, file_list)
    filename_array = strvcat( file_list);
    session_num_char_begin = length( subject_name) + 5; % Subject name plus '.DK.'
    session_num_char_end = session_num_char_begin + 4;
    session_num_chars = filename_array(:,session_num_char_begin:session_num_char_end);
    session_nums = str2num( session_num_chars);
    unique_session_nums = unique( session_nums);
