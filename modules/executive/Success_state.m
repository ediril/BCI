%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function Success_state()

    global XM;

    DisplayMessageToUser('!!!!!!!!!!!!!!! SUCCESS !!!!!!!!!!!!!!!!!!!!!!!');


    if ~XM.insert_alternate_state
        % Eliminate the target from the list of targets to be tried
        XM.num_times_tried_combo(XM.active_combo_index) = XM.num_times_tried_combo(XM.active_combo_index) + 1;
        XM.combos_to_be_tried(XM.combos_to_be_tried==XM.active_combo_index) = [];
    end
    
