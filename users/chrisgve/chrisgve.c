#include "chrisgve.h"

__attribute__ ((weak))
    bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
        return true;
    }

bool apple_mode = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef APPLE_FN_ENABLE
    switch (keycode) {
        case KC_WF1:
            if (!record->event.pressed) {
                if (apple_mode) {
                    tap_code(KC_APPLE_FN);
                }
                tap_code(KC_F1);
            }
            break;
        case KC_WF2:
            if (!record->event.pressed) {
                if (apple_mode) {
                    tap_code(KC_APPLE_FN);
                }
                tap_code(KC_F2);
            }
            break;
        case KC_WF3:
            if (!record->event.pressed) {
                if (apple_mode) {
                    tap_code(KC_APPLE_FN);
                }
                tap_code(KC_F3);
            }
            break;
        case KC_WF4:
            if (!record->event.pressed) {
                if (apple_mode) {
                    tap_code(KC_APPLE_FN);
                }
                tap_code(KC_F4);
            }
            break;
        case KC_WF5:
            if (!record->event.pressed) {
                if (apple_mode) {
                    tap_code(KC_APPLE_FN);
                }
                tap_code(KC_F5);
            }
            break;
        case KC_WF6:
            if (!record->event.pressed) {
                if (apple_mode) {
                    tap_code(KC_APPLE_FN);
                }
                tap_code(KC_F6);
            }
            break;
        case KC_WF7:
            if (!record->event.pressed) {
                if (apple_mode) {
                    tap_code(KC_APPLE_FN);
                }
                tap_code(KC_F7);
            }
            break;
        case KC_WF8:
            if (!record->event.pressed) {
                if (apple_mode) {
                    tap_code(KC_APPLE_FN);
                }
                tap_code(KC_F8);
            }
            break;
        case KC_WF9:
            if (!record->event.pressed) {
                if (apple_mode) {
                    tap_code(KC_APPLE_FN);
                }
                tap_code(KC_F9);
            }
            break;
        case KC_WF10:
            if (!record->event.pressed) {
                if (apple_mode) {
                    tap_code(KC_APPLE_FN);
                }
                tap_code(KC_F10);
            }
            break;
        case KC_WF11:
            if (!record->event.pressed) {
                if (apple_mode) {
                    tap_code(KC_APPLE_FN);
                }
                tap_code(KC_F11);
            }
            break;
        case KC_WF12:
            if (!record->event.pressed) {
                if (apple_mode) {
                    tap_code(KC_APPLE_FN);
                }
                tap_code(KC_F12);
            }
            break;
    }
#endif
    return process_record_keymap(keycode, record);
}
