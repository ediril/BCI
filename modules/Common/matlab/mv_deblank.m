function clean_string = mv_deblank( string)
% clean_string = mv_deblank( string)
%
% A better deblank that removes leading spaces in addition to trailing ones
clean_string = flipdim(deblank(flipdim(deblank(string),2)),2);
