// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layer {
    LAYER_0,
    LAYER_1,
};

#define KC_LYR1     LT(LAYER_1, KC_P0) 

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐
     * │ 7 │ 8 │ 9 │ / │
     * ├───┼───┼───┼───┤
     * │ 4 │ 5 │ 6 │ * │
     * ├───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │ - │
     * ├───┼───┼───┼───┤
     * │ 0 │ . │Ent│ + │
     * └───┴───┴───┴───┘
     */
    [LAYER_0] = LAYOUT_ortho_4x4(KC_P7, KC_P8, KC_P9, KC_PSLS, KC_P4, KC_P5, KC_P6, KC_PAST, KC_P1, KC_P2, KC_P3, KC_PMNS, KC_LYR1, KC_PDOT, KC_PENT, KC_PPLS),
    [LAYER_1] = LAYOUT_ortho_4x4(_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_TOG, RGB_MOD, RGB_RMOD)};
