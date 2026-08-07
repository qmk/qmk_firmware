// Copyright 2022 xia0 (@xia0)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) {
        return false;
    }

    uint8_t layer = get_highest_layer(layer_state);

    if (index == 0) { /* First encoder */
        switch (layer) {
            case 0:
                if (clockwise) {
                    tap_code_delay(KC_VOLU, 10);
                } else {
                    tap_code_delay(KC_VOLD, 10);
                }
                break;
            case 2:
                if (clockwise) {
                    tap_code16(LCTL(KC_MINUS));
                } else {
                    tap_code16(LCTL(KC_EQUAL));
                }
                break;
            default:
                if (clockwise) {
                    tap_code(MS_LEFT);
                } else {
                    tap_code(MS_RGHT);
                }
                break;
        }

    } else if (index == 1) { /* Second encoder */
        switch (layer) {
            case 0:
                if (clockwise) {
                    tap_code(KC_MFFD);
                } else {
                    tap_code(KC_MRWD);
                }
                break;
            case 2:
                if (clockwise) {
                    tap_code16(LCTL(KC_Y));
                } else {
                    tap_code16(LCTL(KC_Z));
                }
                break;
            default:
                if (clockwise) {
                    tap_code(MS_DOWN);
                } else {
                    tap_code(MS_UP);
                }
                break;
        }
    }
    return true;
}
#endif
