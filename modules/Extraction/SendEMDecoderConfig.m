function SendEMDecoderConfig(data)

    vname = inputname(1);
    
    var.(vname) = data;
    
    filename = [vname '.mat'];
    save (filename, '-struct', 'var');
    
    fid = fopen(filename, 'r');
    rawdata = fread(fid, inf, '*uchar');
    fclose(fid);
    
    SendMessage('EM_DECODER_CONFIGURATION', rawdata);