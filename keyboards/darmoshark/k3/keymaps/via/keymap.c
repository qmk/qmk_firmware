// Copyright 2023 Proceee
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
        KC_ESC,   KC_TAB,   KC_BSPC,  MO(1),
        KC_NUM,   KC_PSLS,  KC_PAST,  KC_PMNS,
        KC_P7,    KC_P8,    KC_P9,    KC_PPLS,
        KC_P4,    KC_P5,    KC_P6,
        KC_P1,    KC_P2,    KC_P3,    KC_PENT,
        KC_P0,              KC_PDOT
    ),

    [1] = LAYOUT(
        EE_CLR,   _______,  RGB_MOD,  _______,
        KC_CALC,  _______,  _______,  RGB_VAD,
        _______,  RGB_SPI,  _______,  RGB_VAI,
        _______,  _______,  _______,
        _______,  RGB_SPD,  _______,  _______,
        _______,            RGB_TOG
    ),

    [2] = LAYOUT(
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______,
        _______, _______, _______, _______,
        _______,          _______
    ),

    [3] = LAYOUT(
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______,
        _______, _______, _______, _______,
        _______,          _______
    )
};
