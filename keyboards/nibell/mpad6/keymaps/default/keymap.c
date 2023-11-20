// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬────────┬───────┐
     * │ 1 │   2    │   3   │
     * ├───┼────────┼───────┤
     * │ 4 │ RSHIFT │ RCTRL │
     * └───┴────────┴───────┘
     */
    [0] = LAYOUT_ortho_2x3(
        KC_1,   KC_2,   KC_3,
        KC_4,   KC_RIGHT_SHIFT,   KC_RIGHT_CTRL
    )
};
