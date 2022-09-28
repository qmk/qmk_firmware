// Copyright 2022 Markus Knutsson (@TweetyDaBird)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT(
        KC_MPLY,	KC_MPRV,	KC_MPLY,	KC_MNXT,	KC_NO,	KC_MSEL,	KC_NO
    )
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { // First encoder
        if (clockwise) {
            tap_code_delay(KC_VOLU,0);
        } else {
            tap_code_delay(KC_VOLD,0);
        }
    } /*else if (index == 1) { // Second encoder
        if (clockwise) {
            rgb_matrix_increase_hue();
        } else {
            rgb_matrix_decrease_hue();
        }
    }*/
    return false;
}
