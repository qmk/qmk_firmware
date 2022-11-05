// Copyright 2022 catmunch (@catmunch)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = {
        {KC_PLUS,   KC_9,       KC_8,   KC_7 },
        {KC_MINS,   KC_6,       KC_5,   KC_4 },
        {KC_DOT,    KC_3,       KC_2,   KC_1 },
        {KC_ENT,    KC_SPACE,   KC_0,   MO(1)}
    },
    [1] = {
        {KC_ASTR,   KC_MPRV,    KC_MPLY,KC_MNXT},
        {KC_SLSH,   KC_LPRN,    KC_UP,  KC_RPRN},
        {KC_COMM,   KC_LEFT,    KC_DOWN,KC_RIGHT},
        {KC_TAB,    KC_BSPC,    KC_0,   KC_TRNS}
    }
};
