bool process_record_user(uint16_t keycode, keyrecord_t* record) {
//    if (keycode == DRAG_SCROLL && record->event.pressed) {
//        set_scrolling = !set_scrolling;
//    }

    // Store the current modifier state in the variable for later reference
    mod_state = get_mods();

    if (IS_LAYER_ON(LA_LTHUMB)) {
        if (IS_LAYER_ON(LA_LTHUMBEOSL)) {
            return processKeycodeIfLThumbEOsl(keycode, record);
        } else if (IS_LAYER_ON(LA_LTHUMBEMO)) {
            return processKeycodeIfLThumbEMo(keycode, record);
        } else if (IS_LAYER_ON(LA_LTHUMBDOSL)) {
            return processKeycodeIfLThumbDOsl(keycode, record);
        } else if (IS_LAYER_ON(LA_LTHUMBDMO)) {
            return processKeycodeIfLThumbDMo(keycode, record);
        } else if (IS_LAYER_ON(LA_LTHUMB1MO)) {
            return processKeycodeIfLThumb1Mo(keycode, record);
        } else if (IS_LAYER_ON(LA_LTHUMB2MO)) {
            return processKeycodeIfLThumb2Mo(keycode, record);
        } else if (IS_LAYER_ON(LA_LTHUMB3MO)) {
            return processKeycodeIfLThumb3Mo(keycode, record);
        } else if (IS_LAYER_ON(LA_LTHUMBW)) {
            return processKeycodeIfLThumbW(keycode, record);
        } else if (IS_LAYER_ON(LA_LTHUMBQ)) {
            return processKeycodeIfLThumbQ(keycode, record);
        } else {
            if (!processKeycodeIfLThumb(keycode, record)) {return false;}
        }
    }
    if (IS_LAYER_ON(LA_RTHUMB)) {
        if (!processKeycodeIfRThumb(keycode, record)) {return false;}
    }
    if (IS_LAYER_ON(LA_LPINKY)) {
        if (!processKeycodeIfLPinky(keycode, record)) {return false;}
    }
    if (IS_LAYER_ON(LA_CAPSLOCK)) {
        if (!processKeycodeIfLCapslock(keycode, record)) {return false;}
    }
    if (IS_LAYER_ON(LA_MOUSE)) {
        if (!processKeycodeIfLMouse(keycode, record)) {return false;}
    }
    return processKeycodeIfLBase(keycode, record);

}
