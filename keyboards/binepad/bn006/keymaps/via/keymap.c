/* Copyright 2022 Binepad (@binpad) */
/* SPDX-License-Identifier: GPL-2.0-or-later */

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┐
     * │ A │ B │ C │
     * ├───┼───┼───┤
     * │ D │ E │ F │
     * └───┴───┴───┘
     */
    [0] = LAYOUT_ortho_2x3(
        KC_MPLY, KC_MUTE, KC_VOLU,
        KC_MPRV, KC_MNXT, KC_VOLD
    ),

    [1] = LAYOUT_ortho_2x3(
        _______, _______, _______,
        _______, _______, _______
    ),

    [2] = LAYOUT_ortho_2x3(
        _______, _______, _______,
        _______, _______, _______
    ),

    [3] = LAYOUT_ortho_2x3(
        _______, _______, _______,
        _______, _______, _______
    )
};
