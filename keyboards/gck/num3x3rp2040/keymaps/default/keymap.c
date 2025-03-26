// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_P7,   KC_P8,   KC_P9,
        KC_P4,   KC_P5,   KC_P6,
        KC_P1,   KC_P2,   MO(1)),

    [1] = LAYOUT(
        UG_TOGG,  UG_PREV,  UG_NEXT,
        UG_HUEU,  UG_SATU,  UG_VALU,
        KC_LSFT,  UG_SPDU,   KC_P)    

};
