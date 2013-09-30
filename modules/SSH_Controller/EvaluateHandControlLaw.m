function [c, Pc_fingers, Pf_hand, Vf_hand] = EvaluateHandControlLaw( c, Vc_hand, Pc_hand, Pf_fingers, dt)

    Vc_low = Vc_hand(c.config.low_dof_mask);
    Pc_low = Pc_hand(c.config.low_dof_mask);

    [c, Pc_fingers, Pf_low, Vf_low] = ...
        feval( ['Evaluate_' c.config.algorithm], ...
                             c, Vc_low, Pc_low, Pf_fingers, dt);

    Pf_hand = nan( size( Vc_hand));
    Vf_hand = nan( size( Vc_hand));
    Pf_hand(c.config.low_dof_mask) = Pf_low;
    Vf_hand(c.config.low_dof_mask) = Vf_low;

    %SendDebugVector( Pf_hand);

