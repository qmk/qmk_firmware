// Copyright 2023 ShandonCodes (@ShandonCodes)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬────┐
     * │ A │ B │ C  │
     * ├───┼───┼────┤
     * │ D │ E │ Fn │
     * └───┴───┴────┘
     */
    [0] = LAYOUT_ortho_2x3(
        KC_A,    KC_B,    KC_C,
        KC_D,    KC_E,    MO(1)
    ),
    [1] = LAYOUT_ortho_2x3(
        UG_NEXT,    UG_PREV,    UG_TOGG,
        UG_VALU,    UG_VALD,    KC_TRNS
    )
};
