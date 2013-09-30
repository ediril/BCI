function RespondToPing(M, module_name)        

    global DF;
    
    inp_module_name = deblank(char(M.data.module_name))

    if (strcmp(inp_module_name, module_name) || strcmp(inp_module_name, '*') || M.dest_mod_id == GetModuleID())
        pa = DF.MDF.PING_ACK;
        pa.module_name(1:length(module_name)) = int8(module_name);
        SendMessage('PING_ACK', pa);
    end   
