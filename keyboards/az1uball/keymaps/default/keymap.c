// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌────────────┐
     * │ KC_MS_BTN1 │
     * └────────────┘
     */
    [0] = LAYOUT_ortho_1x1(
        KC_MS_BTN1
    )
};


