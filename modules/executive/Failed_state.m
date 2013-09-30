%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function Failed_state()

    global XM;

    DisplayMessageToUser('************ FAILURE ******************');
    
    if ~XM.insert_alternate_state
        % Increment num times target tried, and if necessary, eliminate the target from the list of targets to be tried
        XM.num_times_tried_combo(XM.active_combo_index) = XM.num_times_tried_combo(XM.active_combo_index) + 1;
        if( XM.config.max_num_tries_per_target > 0)
            if( XM.num_times_tried_combo(XM.active_combo_index) >= XM.config.max_num_tries_per_target)
                XM.combos_to_be_tried(XM.combos_to_be_tried==XM.active_combo_index) = [];
            end
        end
    end
