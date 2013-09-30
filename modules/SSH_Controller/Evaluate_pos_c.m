function [C, PcH, Pe, Ve] = Evaluate_pos_c( C, Vc, Pc, Pf, dt)

% [C, PcH, Pe, Ve] = Evaluate_pos_c( C, Vc, Pc, Pf, dt)
%
% Implements an open-loop position controller that simply converts low-DOF
% position into high-DoF position. Calls on the EKF controller to turn 
% high-DoF feedback back into low-DoF Feedback.
%
% Inputs:
%  C - controller struct
%  Vc - command velocity in low-DoF control space
%  Pc - command position in low-DoF control space
%  Pf - feedback position in high-DoF actuator space
%  dt - delta time
%
% Outputs:
%  C - controller struct
%  PcH - command position in high-DoF actuator space
%  Pe - estimated current position in low-DoF space
%  Ve - estimated current velocity in low-DoF space

	% Transform low-DoF command position into high-DOF command position
    PcH = C.L2H.G( Pc, C.L2H);
    
    % Replace velocity command with zeros because we do not really use
    % the velocity command, we just want to use the filter to turn high-DoF
    % feedback into low-DoF feedback
    Vc(:) = 0;
	[C, PcH_dummy, Pe, Ve] = Evaluate_EKF_fc( C, Vc, Pc, Pf, dt);
