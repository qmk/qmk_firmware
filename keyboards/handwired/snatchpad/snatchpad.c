// Copyright 2022 xia0 (@xia0)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "snatchpad.h"

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
                    tap_code(KC_MS_L);
                } else {
                    tap_code(KC_MS_R);
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
                    tap_code(KC_MS_D);
                } else {
                    tap_code(KC_MS_U);
                }
                break;
        }
    }
    return true;
}
#endif
