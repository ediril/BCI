function [fp, ep_pos, ep_vel] = ProcessFeedback( fp, fbk, dt)

        ep_pos = fbk.pos';
        current_cori_matrix = fbk.R;

        % calculate ep_vel based on ep_pos
        if( ~isfield( fp, 'prev_ep_pos'))
            ep_vel = zeros(size(ep_pos));
            fp.ep_vel_buffer.buffer = zeros(fp.vel_buf_len, length(ep_pos));
            fp.ep_vel_buffer.active_index = 1;
            fp.ep_vel_filter = repmat(fp.ep_vel_filter_coeff, 1, length(ep_pos));
        else
            % Linear
            ep_vel(1:3) = (ep_pos(1:3) - fp.prev_ep_pos(1:3)) / dt;
            % Rotational
            % ori_ypr = ep_pos(5:7);
            cori_diff_matrix = current_cori_matrix * fp.prev_cori_matrix';
            [rot_axis, rot_angle] = rotmat2rotvec( cori_diff_matrix);
            rot_speed = rot_angle / dt;
            rot_vel = rot_axis * rot_speed;
            ep_vel(4:6) = rot_vel;
        end


        % Filter
        [ep_vel, fp.ep_vel_buffer] = continuousFilter(ep_vel, fp.ep_vel_filter, fp.ep_vel_buffer);
        fp.prev_ep_pos = ep_pos;
        fp.prev_cori_matrix = current_cori_matrix;

        % Output as column vectors
        ep_pos = ep_pos(:);
        ep_vel = ep_vel(:);
