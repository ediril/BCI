function C = Initialize_pos_c( config)

    C = struct();
    C.L2H = config.L2H;
    C.P0 = config.initial_pos;
    C.V0 = config.initial_vel;
    C.Dc = config.control_delay;
    C.Df = config.feedback_delay;
    C.M = length( C.P0);
    C.N = length( C.L2H.G( C.P0, C.L2H));

    M = C.M;
    N = C.N;
    L = C.Df + 1 + C.Dc;
    MM = M + L*M;
    NN = N + L*M;

    Var = config.variance;
    qp = Var.state_trans_pos;
    qv = Var.state_trans_vel;
    rf = Var.feedback_pos;
    rc = Var.command_vel;

    C.Q = eye(MM) * qv;
    C.Q(1:M,1:M) = eye(M) * qp;
    C.R = eye(NN) * rc;
    C.R(1:N,1:N) = eye(N) * rf;
