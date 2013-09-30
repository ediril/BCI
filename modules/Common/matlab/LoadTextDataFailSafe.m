function c = LoadTextDataFailSafe( filename)
    
    done = false;
    
    while ~done
        try
            c = LoadTextData( filename);
            done = true;
        catch ME
            fprintf('\n>>> Please correct the following error(s) in config file: %s\n', filename);
            fprintf('%s\n\nWhen finished, hit ENTER to try reloading config file\n', ME.message);
            pause;
        end
    end

    
