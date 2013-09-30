function fp = InitializeFeedbackProcessor()

    fp = struct();
    fp.vel_buf_len = 100;
    exp_alpha = .95;
    fp.ep_vel_filter_coeff = repmat(exp_alpha, fp.vel_buf_len, 1).^([1:fp.vel_buf_len]'); % Exponential
    % fp.ep_vel_filter_coeff = ones(fp.vel_buf_len, 1); % Boxcar
    fp.ep_vel_filter_coeff = (fp.ep_vel_filter_coeff ./ sum(fp.ep_vel_filter_coeff));
