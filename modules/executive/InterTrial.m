%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function InterTrial( )

    global XM;
    global DF;

    if( XM.config.task_state_config.use_denso && XM.config.enable_denso )
        fprintf('\nHalting DENSO (hit R1 to proceed if stuck) ...');
        HaltDenso( );
	    ExpectedEvents = {'DENSO_HALTED', 'PROCEED_TO_NextState'};
        WaitFor( 98, ExpectedEvents{:});
        fprintf(' done\n');


        fprintf('\nMoving DENSO away (hit R1 to proceed if stuck) ...');
        MoveDenso('Present', XM.config.task_state_config.target_configurations.denso_away_moveID);
	    ExpectedEvents = {'DENSO_MOVE_COMPLETE', 'PROCEED_TO_NextState'};
        WaitFor( 98, ExpectedEvents{:});
        fprintf(' done\n');
    end

    SaveData();

    % If ABORT_SESSION received then quit
    if( XM.aborting_session)
        return;
    end

    % Implement a penalty time
    if (XM.penalty_time > 0)
        disp('implementing penalty time...');
        SendTaskStateConfigTimeout(99, XM.penalty_time);
        WaitFor(99, 'JUDGE_VERDICT');
    end

   if( XM.pausing_experiment == true)
       disp('Experiment paused...');

       ExpectedEvents = {'RESUME_EXPERIMENT', 'XM_ABORT_SESSION', 'JUDGE_VERDICT' };
       while(1)
           SendTaskStateConfigTimeout(100, 30000);
           evt = WaitFor( 100, ExpectedEvents{:});
           if (~strcmp(evt.msg_type, 'RESUME_EXPERIMENT'))
               SaveData();
           end
           if (XM.aborting_session == true), break;  end
           if (XM.pausing_experiment == false), break;  end
       end

       disp('Resuming experiment...');
   end

