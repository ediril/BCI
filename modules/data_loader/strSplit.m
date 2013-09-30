function l = strSplit(S, D)
%L=SPLIT(D,S) splits a string S delimited by characters in D.  Meant to
%             work roughly like the PERL split function (but without any
%             regular expression support).  Internally uses STRTOK to do 
%             the splitting.  Returns a cell array of strings.

    l = {};
    while (length(S) > 0)
        [t,S] = strtok(S,D);
        if ~isempty(t)
            l = {l{:}, t};
        end
    end