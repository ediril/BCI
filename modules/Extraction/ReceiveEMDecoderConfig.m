
function EMDecoderConfig = ReceiveEMDecoderConfig(Msg)

    template = char(zeros(1, Msg.num_data_bytes));
    rawdata = ReadMessageData( template);

    filename = 'em_decoder_config_msg.mat';

    fid = fopen(filename, 'wb');
    fwrite(fid, rawdata);
    fclose(fid);

    load(filename);

    