function HaltDenso( )

% HaltDenso( )
%
% Halt the current DENSO movement.

global XM;

if( XM.config.task_state_config.use_denso && XM.config.enable_denso)
	SendSignal DENSO_HALT;
end
