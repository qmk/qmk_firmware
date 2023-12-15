// Copyright 2022 Jimmy Lye (@satorusaka)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌────┬───┬───┬───┬────┐
     * │ F3 │ 9 │ 6 │ 3 │ fn │
     * ├────┼───┼───┼───┼────┤
     * │ F2 │ 8 │ 5 │ 2 │ .  │
     * ├────┼───┼───┼───┼────┤
     * │ F1 │ 7 │ 4 │ 1 │ O  │
     * └────┴───┴───┴───┴────┘
     */
    [0] = LAYOUT_default(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   LT(1, KC_KB_MUTE),
        KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_KB_VOLUME_UP,
        KC_F9,   KC_F10,   KC_F11,   KC_F12,   KC_KB_VOLUME_DOWN
    ),
    [1] = LAYOUT_default(
        RGB_TOG,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
        RGB_MODE_FORWARD,RGB_HUI,RGB_SAI,RGB_VAI,RGB_SPI,
        RGB_MODE_REVERSE,RGB_HUD,RGB_SAD,RGB_VAD,RGB_SPD
    )
};
