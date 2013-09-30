function dir_list = mv_dir( pattern, type)

% DIR_LIST = MV_DIR( PATTERN)
% DIR_LIST = MV_DIR( PATTERN, TYPE)
% 
% Returns a cell array containing a directory listing that matches PATTERN.
% TYPE is an optional argument that specifies 'file' or 'dir' to list only
% file or directories respectively. TYPE 'any' will list all entries and
% this is the default when type is not specified.
%
% MV 7/31/2003
% Updated MV 4/7/2004

if( nargin < 2)
    type = 'any';
end
if( nargin < 1)
    pattern = '*';
end

     % Get Directory listing
     d = dir( pattern);
     N = length(d);
     if( N < 1)
         dir_list = {};
         return;
     end

     % Choose directories or regular files if need be
     switch type
         case 'file',
             bad_ones = find([d.isdir]);
             d(bad_ones) = [];
         case 'dir',
             bad_ones = find(~[d.isdir]);
             d(bad_ones) = [];
         case 'any',
         otherwise,
             error('TYPE should be ''file'', ''dir'' or ''any''');
     end

     % Put it in a cell array of strings
     dir_list = {d.name}';
     
     % Get rid of '.' and '..'
     i = strmatch('.',dir_list,'exact');
     ii = strmatch('..',dir_list,'exact');
     dir_list([i ii]) = [];

     % Sort the entries
     dir_list = sort( dir_list);
