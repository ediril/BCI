function ids = FindButtonPressIds(iData, buttonId, controllerId, init_var)
    
    ids = false(1, length( iData.QL.SampleNos));
    
    if isfield(iData.QL.Data, 'PS3_BUTTON_PRESS')
        button_idx = (iData.QL.Data.PS3_BUTTON_PRESS.whichButton == buttonId);
        controller_id_idx = (iData.QL.Data.PS3_BUTTON_PRESS.controllerId == controllerId);
        button_press_idx = (button_idx & controller_id_idx);

        button_idx = (iData.QL.Data. PS3_BUTTON_RELEASE.whichButton == buttonId);
        controller_id_idx = (iData.QL.Data. PS3_BUTTON_RELEASE.controllerId == controllerId);
        button_release_idx = (button_idx & controller_id_idx);

        if any(button_press_idx)
            button_press_seqno = iData.QL.SequenceNo.PS3_BUTTON_PRESS(button_press_idx);
            button_press = GetRelativeRefIndices(button_press_seqno, iData.QL.SequenceNo.SAMPLE_GENERATED);
            button_press_SG_idx = button_press.idx(button_press.valid);

            button_release_seqno = iData.QL.SequenceNo. PS3_BUTTON_RELEASE(button_release_idx);
            button_release = GetRelativeRefIndices(button_release_seqno, iData.QL.SequenceNo.SAMPLE_GENERATED);
            button_release_SG_idx = button_release.idx(button_press.valid);

            was_pressed_mask = zeros(1, length( iData.QL.SampleNos));
            was_pressed_mask(button_press_SG_idx) = 1;
            was_pressed_mask(button_release_SG_idx) = -1;
            was_pressed_mask = cumsum(was_pressed_mask);
            if any(was_pressed_mask<0)
                was_pressed_mask = was_pressed_mask + 1;
            end
            was_pressed_mask = logical(was_pressed_mask);

            % if exist('init_var', 'var')
            %     upto_idx = button_press_SG_idx(1)-1;
            %     ids(1:upto_idx) = init_var;
            % end
            % 
            % ids(button_press_SG_idx) = true;
            ids(was_pressed_mask) = true;
        end
    end