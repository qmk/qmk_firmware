// Copyright 2023 Proceee
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT_numpad_6x4(
        KC_ESC,   KC_TAB,   KC_BSPC,  MO(1),
        KC_NUM,   KC_PSLS,  KC_PAST,  KC_PMNS,
        KC_P7,    KC_P8,    KC_P9,
        KC_P4,    KC_P5,    KC_P6,    KC_PPLS,
        KC_P1,    KC_P2,    KC_P3,
        KC_P0,              KC_PDOT,  KC_PENT
    ),

    [1] = LAYOUT_numpad_6x4(
        EE_CLR,   _______,  RM_NEXT,  _______,
        KC_CALC,  _______,  _______,  RM_VALD,
        _______,  RM_SPDU,  _______,
        _______,  _______,  _______,  RM_VALU,
        _______,  RM_SPDD,  _______,
        _______,            RM_TOGG,  _______
    )
};
