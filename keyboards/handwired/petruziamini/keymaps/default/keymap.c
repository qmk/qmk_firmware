// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │ A │ B │ C │ D │ E │ F │ G │ H │ I │ J │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │ A │ B │ C │ D │ E │ F │ G │ H │ I │ J │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │ A │ B │ C │ D │ E │ F │ G │ H │ I │ J │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │ A │ B │   │ D │   │   │ G │   │ I │ J │
     * └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
     */
    [0] = LAYOUT(
        KC_A,    KC_B,    KC_C,    KC_D,    KC_E,    KC_F,    KC_G,    KC_H,    KC_I,    KC_J,
        KC_A,    KC_B,    KC_C,    KC_D,    KC_E,    KC_F,    KC_G,    KC_H,    KC_I,    KC_J,
        KC_A,    KC_B,    KC_C,    KC_D,    KC_E,    KC_F,    KC_G,    KC_H,    KC_I,    KC_J,
        KC_A,    KC_B,    KC_C,    KC_D,    LT(1, KC_E),    KC_F
    ),
    [1] = LAYOUT(
    KC_NO,    QK_BOOT,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO
)
};
