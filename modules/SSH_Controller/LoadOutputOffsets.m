function output_offsets = LoadOutputOffsets()
            
    offset_config_file = [getenv('ROBOT_CONFIG') '/default/sshc_output_offsets.conf'];
    c = LoadValidateConfigFile( offset_config_file, {'config.transl_offset'});
    output_offsets = c.config;