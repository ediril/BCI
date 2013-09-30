function file_name = VerifyFileExists( given_file_name)
% file_name = VerifyFileExists( given_file_name)
% 
% Verifies that given_file_name exists. The first name of the file that 
% exists will be returned in file_name

if( ~exist( given_file_name, 'file'))
	caller_name = GetCallerName( );
	error( [caller_name '(): file "' given_file_name '" does not exist!']);
end
