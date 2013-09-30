function SendMovementCommand(EM, prediction, sample_header)

    global DF;

    movement_command = DF.MDF.EM_MOVEMENT_COMMAND;
    movement_command.sample_header = sample_header;
    movement_command.pos(1:length(prediction.pos)) = prediction.pos;
    movement_command.vel(1:length(prediction.vel)) = prediction.vel;
    movement_command.tag(1:length(EM.config.tag)) = EM.config.tag;
    movement_command.sample_interval = sample_header.DeltaTime;
    movement_command.controlledDims(1:length(EM.config.ControlledDims)) = EM.config.ControlledDims;
    
    if(EM.config.decoder.SendAuxMovementCommand)
        SendMessage( 'EM_AUX_MOVEMENT_COMMAND', movement_command);
    else
        SendMessage( 'EM_MOVEMENT_COMMAND', movement_command); 
    end
    
end
