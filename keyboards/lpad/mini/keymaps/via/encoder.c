#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (biton32(layer_state) == 0) {
        if (index == 0) {
            if (clockwise) {
                // tap_code(KC_PGDN);
                tap_code16(dynamic_keymap_get_keycode(0, 0, 0));
            } else {
                // tap_code(KC_PGUP);
                tap_code16(dynamic_keymap_get_keycode(0, 0, 1));
            }
        } else if (index == 1) {
            if (clockwise) {
                // tap_code(KC_LEFT);
                tap_code16(dynamic_keymap_get_keycode(0, 3, 3));
            } else {
                // tap_code(KC_RIGHT);
                tap_code16(dynamic_keymap_get_keycode(0, 4, 2));
            }
        }
    } else if (biton32(layer_state) == 1) {
        if (index == 0) {
            if (clockwise) {
                // tap_code(KC_PGDN);
                tap_code16(dynamic_keymap_get_keycode(0, 0, 0));
            } else {
                // tap_code(KC_PGUP);
                tap_code16(dynamic_keymap_get_keycode(0, 0, 1));
            }
        } else if (index == 1) {
            if (clockwise) {
                // tap_code(KC_LEFT);
                tap_code16(dynamic_keymap_get_keycode(0, 3, 3));
            } else {
                // tap_code(KC_RIGHT);
                tap_code16(dynamic_keymap_get_keycode(0, 4, 2));
            }
        }
    } else if (biton32(layer_state) == 2) {
        if (index == 0) {
            if (clockwise) {
                // tap_code(KC_PGDN);
                tap_code16(dynamic_keymap_get_keycode(0, 0, 0));
            } else {
                // tap_code(KC_PGUP);
                tap_code16(dynamic_keymap_get_keycode(0, 0, 1));
            }
        } else if (index == 1) {
            if (clockwise) {
                // tap_code(KC_LEFT);
                tap_code16(dynamic_keymap_get_keycode(0, 3, 3));
            } else {
                // tap_code(KC_RIGHT);
                tap_code16(dynamic_keymap_get_keycode(0, 4, 2));
            }
        }
    }
    return true;
}

#endif
