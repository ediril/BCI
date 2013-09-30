function [C, Pc_fingers, Pf_low, Vf_low] = Evaluate_vel_c( C, Vc_low, Pc_low, Pf_fingers, dt)

    global prev_Pc_low;
    if( isempty( prev_Pc_low))
        prev_Pc_low = zeros( size( Vc_low));
    end

    Pc_low = prev_Pc_low + Vc_low * dt;
    prev_Pc_low = Pc_low;
    Pc_fingers = C.config.low2high_mapper.fmap' * Pc_low;
    Pf_low = Pc_low;
    Vf_low = Vc_low;
    