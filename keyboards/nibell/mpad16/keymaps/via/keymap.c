// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───────┬─────┬────────┬───────┐
     * │  F1   │ F2  │   F3   │  F4   │
     * ├───────┼─────┼────────┼───────┤
     * │  F5   │ F6  │   F7   │  F8   │
     * ├───────┼─────┼────────┼───────┤
     * │   1   │  2  │   3    │   4   │
     * ├───────┼─────┼────────┼───────┤
     * │ PRTSC │ INS │ RSHIFT │ RCTRL │
     * └───────┴─────┴────────┴───────┘
     */
    [0] = LAYOUT_ortho_4x4(
        KC_F1,              KC_F2,      KC_F3,          KC_F4,
        KC_F5,              KC_F6,      KC_F7,          KC_F8,
        KC_1,               KC_2,       KC_3,           KC_4,
        KC_PRINT_SCREEN,    KC_INSERT,  KC_RIGHT_SHIFT, KC_RIGHT_CTRL
    )
};
