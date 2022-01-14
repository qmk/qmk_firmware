// Copyright 2022 raylax (@raylax)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H


// Defines names for use in layer keycodes and the keymap
enum layer_names {
    BASE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_X
    ),
    [1] = LAYOUT(
        KC_TRNS
    ),
    [2] = LAYOUT(
        KC_TRNS
    ),
    [3] = LAYOUT(
        KC_TRNS
    ),
};
