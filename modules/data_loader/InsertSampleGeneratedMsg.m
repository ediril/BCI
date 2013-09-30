function [QL] = InsertSampleGeneratedMsg(QL)

    %
    % Headers
    %
    hdr_fields = fields(QL.Headers.SAMPLE_GENERATED);
    for h = 1 : length(hdr_fields)
        field = hdr_fields{h};
        new_field = QL.Headers.SAMPLE_GENERATED.(field);
        new_field = [new_field(1) new_field];
        QL.Headers.SAMPLE_GENERATED.(field) = new_field;
    end
    QL.Headers.SAMPLE_GENERATED.send_time(1) = QL.Headers.SAMPLE_GENERATED.send_time(1) - 0.02;
    QL.Headers.SAMPLE_GENERATED.recv_time(1) = QL.Headers.SAMPLE_GENERATED.recv_time(1) - 0.02;
    QL.Headers.SAMPLE_GENERATED.msg_count(1) = QL.Headers.SAMPLE_GENERATED.msg_count(1) - 2;

    %
    % Data
    %
    tstmp = QL.Data.SAMPLE_GENERATED.source_timestamp(1) - 0.02;
    QL.Data.SAMPLE_GENERATED.source_timestamp = [tstmp QL.Data.SAMPLE_GENERATED.source_timestamp];
    
    shdr_fields = fields(QL.Data.SAMPLE_GENERATED.sample_header);
    for h = 1 : length(shdr_fields)
        field = shdr_fields{h};
        new_field = QL.Data.SAMPLE_GENERATED.sample_header.(field);
        new_field = [new_field(1) new_field];
        QL.Data.SAMPLE_GENERATED.sample_header.(field) = new_field;
    end
    if (QL.Data.SAMPLE_GENERATED.sample_header.SerialNo(1) > 1)
        QL.Data.SAMPLE_GENERATED.sample_header.SerialNo(1) = QL.Data.SAMPLE_GENERATED.sample_header.SerialNo(1) - 1;
    else
        QL.Data.SAMPLE_GENERATED.sample_header.SerialNo(1) = 1;
    end
    
    
    %
    % SequenceNo
    %
    QL.SequenceNo.SAMPLE_GENERATED = [1 QL.SequenceNo.SAMPLE_GENERATED];

    %
    % FileIndex
    %
    QL.FileIndex.SAMPLE_GENERATED = [1 QL.FileIndex.SAMPLE_GENERATED];

