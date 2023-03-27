bool process_record_user(uint16_t keycode, keyrecord_t* record) {
//    if (keycode == DRAG_SCROLL && record->event.pressed) {
//        set_scrolling = !set_scrolling;
//    }

    // Store the current modifier state in the variable for later reference
    mod_state = get_mods();

    if (IS_LAYER_ON(LA_LTHUMB) || IS_LAYER_ON(LA_LTHUMBMS)) {
        if (IS_LAYER_ON(LA_LTHUMBW)) {
            if (!processKeycodeIfLThumbW(keycode, record)) {return false;}
        }
        if (IS_LAYER_ON(LA_LTHUMBQ)) {
            if (!processKeycodeIfLThumbQ(keycode, record)) {return false;}
        }
        if (IS_LAYER_ON(LA_LTHUMB3MO)) {
            if (!processKeycodeIfLThumb3Mo(keycode, record)) {return false;}
        }
        if (IS_LAYER_ON(LA_LTHUMB2MO)) {
            if (!processKeycodeIfLThumb2Mo(keycode, record)) {return false;}
        }
        if (IS_LAYER_ON(LA_LTHUMB1MO)) {
            if (!processKeycodeIfLThumb1Mo(keycode, record)) {return false;}
        }
        if (IS_LAYER_ON(LA_LTHUMBDOSL)) {
            if(!processKeycodeIfLThumbDOsl(keycode, record)) {return false;}
        }
        if (IS_LAYER_ON(LA_LTHUMBEOSL)) {
            if(!processKeycodeIfLThumbEOsl(keycode, record)) {return false;}
        }
        if (IS_LAYER_ON(LA_LTHUMBDMO)) {
            if (!processKeycodeIfLThumbDMo(keycode, record)) {return false;}
        }
        if (IS_LAYER_ON(LA_LTHUMBEMO)) {
            if (!processKeycodeIfLThumbEMo(keycode, record)) {return false;}
        }
        if (IS_LAYER_ON(LA_LTHUMBMS)) {
            if (!processKeycodeIfLThumbMs(keycode, record)) {return false;}
        }
        else if (!processKeycodeIfLThumb(keycode, record)) {return false;}
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
