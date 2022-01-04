// Copyright 2021 minibois (@minibois)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap _BASE: (Base Layer) Default Layer
     * ,-------------------.
     * |Esc|Cal| / | * | - |
     * |--------------------
     * | BS| 7 | 8 | 9 | + |
     * |--------------------
     * | ( | 4 | 5 | 6 | + |
     * |--------------------
     * | ) | 1 | 2 | 3 |Ent|
     * |--------------------
     * | Y | 00| 0 | . |Ent|
     * `-------------------'
     */
    [_BASE] = LAYOUT_all(
        KC_ESC,  KC_CALC, KC_PSLS, KC_PAST, KC_PMNS,
        KC_BSPC,  KC_P7, KC_P8, KC_P9, KC_PPLS,
        KC_LEFT_PAREN,  KC_P4, KC_P5, KC_P6, KC_PPLS,
        KC_RIGHT_PAREN,  KC_P1, KC_P2, KC_P3, KC_PENT,
        KC_Y,  KC_P0, KC_P0, KC_PDOT, KC_PENT
    )
};
