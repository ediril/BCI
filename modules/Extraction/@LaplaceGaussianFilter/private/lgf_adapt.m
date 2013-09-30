function lgf = lgf_adapt(lgf, spike, teach, serialno)
%     spike:           T x 384 int8
%     teach:           T x NUMBER OF STATES double
%     serialno:        
%     active periods:  1 x T logical
%     estimate_Q:      logical specifying whether or not to estimate the
%                      state transition variance matrix from the teach
%                      signal


    % Wrong size, if regressor(teach) is not the same size as teach.
    B = zeros(size(teach,2)+1, size(spike,2));
    % Identify used dimensions
    dmask = sum(abs(teach))>0 & lgf.dimension_mask>0;
    % Identify active units
    lgf.activity_mask(:) = 0;
    
    % Old way - take any cell that fires.
    %     lgf.activity_mask(sum(spike)>0) = 1;
    % Better way - Only take units with firing rates of more than 1Hz.
    lgf.activity_mask(sum(spike)>size(spike,1)*.03) = 1;
    
    % Fit baseline rates, preferred directions, modulation depths
    switch lgf.tuning_model
        case {0} % Standard.  Velocity, position, or combination
            for i=find(lgf.activity_mask>0)
                B([true dmask],i) = glmfit(regressor(teach(:,dmask)),single(spike(:,i)),'poisson');
            end
        case {1} % Direction
            % Note: will only work if dmask is [1,1,*,0,0,0,0,0]
            
            % Direction models need an overall scale to keep the tuning
            % coefficients in the right range.  Use the average speed to
            % scale the direction vectors.
            spd=sqrt(sum(teach(:,dmask).^2,2));
            nzinds=find(spd);
            lgf.direction_scale=mean(spd(nzinds));
            
            for i=find(lgf.activity_mask>0)
                B([true dmask],i) = glmfit(regressor_direction(teach(:,dmask),lgf.direction_scale),single(spike(:,i)),'poisson');
            end
        case {2} % Speed and direction
            % Note: will only work if dmask is [1,1,*,0,0,0,0,0]
            
            % Direction models need an overall scale to keep the tuning
            % coefficients in the right range.  Use the average speed to
            % scale the direction vectors.
            spd=sqrt(sum(teach(:,dmask).^2,2));
            nzinds=find(spd);
            lgf.direction_scale=mean(spd(nzinds));

            Bdmask=dmask; Bdmask(7)=true; % Put the extra coefficient in the 7th spot
            for i=find(lgf.activity_mask>0)
                B([true Bdmask],i) = glmfit(regressor_speed_and_direction(teach(:,dmask),lgf.direction_scale),single(spike(:,i)),'poisson');
            end
        case {3} % Speed and velocity
            % Note: will only work if dmask is [1,1,*,0,0,0,0,0]
            Bdmask=dmask; Bdmask(7)=true;
            for i=find(lgf.activity_mask>0)
                B([true Bdmask],i) = glmfit(regressor_speed_and_velocity(teach(:,dmask)),single(spike(:,i)),'poisson');
            end
    end
    
    % Estimate state transition variance matrix, Q, from the adapt data
    if lgf.estimate_Q
        valid_indx = find(diff(serialno)==1);
        T_valid = length(valid_indx);
        x_t_plus_one = teach(valid_indx+1,:); % T_valid x NUMBER OF STATES
        x_t = teach(valid_indx,:);
        residual = x_t_plus_one - (lgf.F*x_t')'; % T_valid x NUMBER OF STATES
        residual = residual - repmat(mean(residual),T_valid,1);
        lgf.var = (residual'*residual)/(T_valid-1);
    end
    
    % Set pva parameter fields
    lgf.baseline = B(1,:);
    lgf.prefdirs = B(2:end,:);
end