// Copyright 2023 Ismaïl Senhaji (@iSma)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(/* Base */
                 KC_BSPC, KC_7, KC_8, KC_9,
                 KC_TAB,  KC_4, KC_5, KC_6,
                 KC_0,    KC_1, KC_2, KC_3,
                 RGB_MOD, RGB_TOG, KC_MPLY, KC_MUTE
                 ),
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* top left encoder */
        if (clockwise) {
            rgblight_increase_hue();
        } else {
            rgblight_decrease_hue();
        }
    } else if (index == 1) { /* top right encoder */
        if (clockwise) {
            rgblight_increase_val();
        } else {
            rgblight_decrease_val();
        }
    } else if (index == 2) { /* center encoder */
        if (clockwise) {
            tap_code(KC_MFFD);
        } else {
            tap_code(KC_MRWD);
        }
    } else if (index == 3) { /* bottom encoder */
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return true;
}
