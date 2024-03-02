// TODO: Improve this currently there is no feedback if activated by other means.
bool CAPS_LOCK   = false;
bool NUM_LOCK    = false;
bool SCROLL_LOCK = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_dynamic_macro(keycode, record)) {
        return false;
    }

    switch (keycode) {
        case KC_CAPS_LOCK:
            if (record->event.pressed) {
                if (!(CAPS_LOCK)) {
                    ergodox_right_led_1_on();
                    CAPS_LOCK = true;
                } else {
                    ergodox_right_led_1_off();
                    CAPS_LOCK = false;
                }
            }

            return true;

        case KC_NUM_LOCK:
            if (record->event.pressed) {
                if (!(NUM_LOCK)) {
                    ergodox_right_led_2_on();
                    NUM_LOCK = true;
                } else {
                    ergodox_right_led_2_off();
                    NUM_LOCK = false;
                }
            }

            return true;

        case KC_SCROLL_LOCK:
            if (record->event.pressed) {
                if (!(SCROLL_LOCK)) {
                    ergodox_right_led_3_on();
                    SCROLL_LOCK = true;
                } else {
                    ergodox_right_led_3_off();
                    SCROLL_LOCK = false;
                }
            }

            return true;

        case KC_MS_WH_UP ... KC_MS_WH_RIGHT:
            if (record->event.pressed) {
                if (SCROLL_LOCK) {
                    return false;
                } else {
                    return true;
                }
            }

        case MY_CUSTOM_MACRO:
            if (record->event.pressed) {
                SEND_STRING("QMK is the best thing ever!"); // this is our macro!
                return false;
            }

        case MY_OTHER_MACRO:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("ac")); // selects all and copies
                return false;
            }

        default:
            return true;
    }
}
