function Message = NewMonkeyKnob_EventHook( Message)

% Message = MonkeyKnob_EventHook( Message)
%
% This function gets called every time when a message is received through
% any of the higher-level functions (i.e. WaitFor, CheckForMessage or
% eventmap). Note that this function does not get called when your code
% uses ReadMessage directly, because ReadMessage is supposed be the raw
% function that just reads the message.
%
% Meel Velliste 8/11/2008

    global DF;
    global XM;

    % seperate switch since MTs can be duplicated in the above switch

    %fprintf('\n\n--->>>msg type: %s\n\n', Message.msg_type);

    switch(Message.msg_type)

        case 'EXIT'
            if (Message.dest_mod_id == GetModuleID()) || (Message.dest_mod_id == 0)
                DoExit();
            end

        case 'PING'
            RespondToPing(Message, 'executive');

        case {'READY_BUTTON'}
            disp('button button button');

        case 'TASK_CONFIG'
            % Task config comes from GUI module
            % We apply the new config in SetupTrial
            XM.new_config = Message.data;

        %case {'DENSO_MOVE_COMPLETE','DENSO_HALTED'}
        %    if( Message.data.movement_id == XM.Denso.CurrentMoveID)
        %        XM.Denso.MoveInProgress = false;
        %    else
        %        Message = []; % If this is a response to a previous move, then ignore it
        %    end

        %case 'DENSO_MOVE_COMPLETE'
        %    if XM.Denso.MoveHalted
        %        Message = [];
        %    end
        %case 'DENSO_HALTED'
        %    XM.Denso.MoveHalted = true;
        %case 'DENSO_MOVE_CONTINUE'
        %    XM.Denso.MoveHalted = false;

        case 'DENSO_MOVE_FAILED'
            error( 'DENSO Move Failed!!!');

        case 'DENSO_MOVE_INVALID'
            error( 'DENSO Move Invalid!!!');

        case 'KEYBOARD'
            keyboard

        case 'CLEAR_FUNCTION'
            template = repmat(' ', [1 double(Message.num_data_bytes)]);
            rogue_function = ReadMessageData( template);
            clear( rogue_function);
            disp( ['---------------------------------------------------------']);
            disp( ['Cleared function "' rogue_function '"']);
            disp( ['---------------------------------------------------------']);

        case {'JOYPAD_R1','JOYPAD_X', 'PS3_BUTTON_PRESS','PS3_BUTTON_RELEASE'}
            Message = MapJoypadEvent(Message);

        case 'APP_ERROR'
            ModIDNames = fieldnames( DF.MID);
            ModIDNums = struct2cell( DF.MID);
            ModName = ModIDNames{[ModIDNums{:}]==Message.src_mod_id};
            template = repmat(' ', [1 double(Message.num_data_bytes)]);
            error_text = ReadMessageData( template);
            error( ['MonkeyKnob_EventHook(): Error reported by Module ' ModName ': ' error_text]);

        case 'XM_ABORT_SESSION'
            XM.aborting_session = true;

        case 'PAUSE_EXPERIMENT'
            XM.pausing_experiment = true;
            disp('PAUSE_EXPERIMENT received');
            disp('ADAPTING...');

        case 'RESUME_EXPERIMENT'
            XM.pausing_experiment = false;
            disp('RESUME_EXPERIMENT received');
    end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function M = MapJoypadEvent(M)
	global XM;
	global DF;

	switch(M.msg_type)
        case 'PS3_BUTTON_PRESS'
           if(M.data.controllerId == XM.config.use_controller)
                if(M.data.whichButton == DF.defines.PS3_B_X)
                  disp('X recd');
                  if(isfield(XM, 'runtime'))
                    XM.runtime.cancel_button_pressed = 1;
                  end
                  M.msg_type = 'PROCEED_TO_Failure';
                elseif(M.data.whichButton == DF.defines.PS3_B_R1)
                  disp('R1 recd');
                  M.msg_type = 'PROCEED_TO_NextState';
                elseif(M.data.whichButton == DF.defines.PS3_B_R2)
                  disp('R2 recd');
                  M.msg_type = 'PROCEED_TO_NextState';
                elseif(M.data.whichButton == DF.defines.PS3_B_SQUARE)
                  disp('SQ recd');
                  if( ~isfield( XM, 'pausing_experiment'))
                      XM.pausing_experiment = false;
                  end
                  if( XM.pausing_experiment)
                      disp('Going to resume experiment!');
                      XM.pausing_experiment = false;
                      M.msg_type = 'RESUME_EXPERIMENT';
                  else
                      disp('Going to pause experiment!');
                      XM.pausing_experiment = true;
                      M.msg_type = 'PAUSE_EXPERIMENT';
                  end
                elseif(M.data.whichButton == DF.defines.PS3_B_CIRCLE)
                  disp('circle recd');
                  GiveDirectReward(5);
                end
           end
    end
