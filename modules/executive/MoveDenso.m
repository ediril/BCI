function MoveDenso( PosName, PosNumber)

% MoveDenso( PosName, PosNumber)
%
% Move the DENSO robot to named position PosName.
% PosName can be 'Present', 'Away' or 'Hide'. If PosName
% is 'Present', then PosNumber is target_denso_moveID

    global XM;
    global DF;

    if( ~exist('PosNumber', 'var') && (strcmp(PosName, 'Present') == 1))
        error('MoveDenso() needs valid moveID to be used with option ''Present''');
    end

    if( XM.config.enable_denso && XM.config.task_state_config.use_denso)

        %XM.Denso.MoveHalted = false;

        %if( XM.Denso.MoveInProgress), error( 'Trying to move DENSO before previous move finished'); end
        dm = DF.MDF.DENSO_MOVE;
        XM.Denso.CurrentMoveID = XM.Denso.CurrentMoveID + 1;
        %fprintf(['\nCurrentMoveID: ' num2str(XM.Denso.CurrentMoveID)]);

        switch( PosName)
            case 'Present'
                %SendMessage( 'DENSO_SET_SPEED', struct( 'speed', XM.config.denso_speed));
                dm.position_no(1) = PosNumber;
                dm.movement_id(1) = XM.Denso.CurrentMoveID;
                SendMessage( 'DENSO_MOVE', dm);
                %XM.Denso.MoveInProgress = true;
            case 'Away'
                %SendMessage( 'DENSO_SET_SPEED', struct( 'speed', XM.config.denso_speed));
                dm.position_no(1) = 2;
                dm.movement_id(1) = XM.Denso.CurrentMoveID;
                SendMessage( 'DENSO_MOVE', dm);
                %XM.Denso.MoveInProgress = true;
            case 'Hide'
                %SendMessage( 'DENSO_SET_SPEED', struct( 'speed', 30));
                dm.position_no(1) = 3;
                dm.movement_id(1) = XM.Denso.CurrentMoveID;
                SendMessage( 'DENSO_MOVE', dm);
                %XM.Denso.MoveInProgress = true;
            otherwise
                error( 'Unrecognized position name');
        end

        %['MoveDenso() sending ' int2str(dm.position_no(1))]

    end
