#include QMK_KEYBOARD_H
#include "layers.h"

#ifdef ENCODER_ENABLE

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        switch (get_highest_layer(layer_state)) {
            case WORKMAN:
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
                break;
            case SYMBOLS:
            case FN:
                if (clockwise) {
                    tap_code(KC_PGDN);
                } else {
                    tap_code(KC_PGUP);
                }
                break;
            case NAV:
            case RNAV:
            default:
                if (clockwise) {
                    tap_code16(C(A(KC_RIGHT)));
                } else {
                    tap_code16(C(A(KC_LEFT)));
                }
                break;
        }
    } else if (index == 1) {
        switch (get_highest_layer(layer_state)) {
            case WORKMAN:
                if (clockwise) {
                    tap_code(KC_BRIU);
                } else {
                    tap_code(KC_BRID);
                   }
                break;
            case SYMBOLS:
            case FN:
                if (clockwise) {
                    tap_code16(C(KC_RIGHT));
                } else {
                    tap_code16(C(KC_LEFT));
                }
                break;
            case NAV:
            case RNAV:
            default:
                if (clockwise) {
                    tap_code16(C(KC_TAB));
                } else {
                    tap_code16(C(S(KC_TAB)));
                }
                break;
        }
    }
}
#endif
