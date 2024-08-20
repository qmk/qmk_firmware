/*
Copyright 2024 Mkass420 (@Mkass420)
SPDX-License-Identifier: GPL-2.0-or-later
*/
#include QMK_KEYBOARD_H


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┐
     * │ Z │ X │ C │
     * └───┴───┴───┘
     */
    [0] = LAYOUT(KC_Z, KC_X, KC_C)
};

