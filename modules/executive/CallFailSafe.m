function CallFailSafe(funcname, varargin)

    done = false;
    while (~done)
        try
            feval(funcname, varargin{:});
            done = true;
        catch ME
            fprintf('\n>>> %s', ME.message);
            fprintf('\nPlease correct the error and hit ENTER to retry\n');
            pause;
        end
    end
