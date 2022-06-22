// Copyright 2022 catmunch (@catmunch)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = {
        {KC_PPLS,   KC_P9,      KC_P8,  KC_P7},
        {KC_PMNS,   KC_P6,      KC_P5,  KC_P4},
        {KC_PDOT,   KC_P3,      KC_P2,  KC_P1},
        {KC_PENT,   KC_SPACE,   KC_P0,  MO(1)}
    },
    [1] = {
        {KC_PAST,   KC_NO,      KC_NO,  KC_NO},
        {KC_PSLS,   LSFT(KC_9), KC_UP,  LSFT(KC_0)},
        {KC_COMM,   KC_LEFT,    KC_DOWN,KC_RIGHT},
        {KC_TAB,    KC_SPACE,   KC_P0,  KC_TRNS}
    },
    [2] = {
        {KC_NO,     KC_NO,      KC_NO,  KC_NO},
        {KC_NO,     KC_NO,      KC_NO,  KC_NO},
        {KC_NO,     KC_NO,      KC_NO,  KC_NO},
        {KC_NO,     KC_NO,      KC_NO,  KC_NO}
    },
    [3] = {
        {KC_NO,     KC_NO,      KC_NO,  KC_NO},
        {KC_NO,     KC_NO,      KC_NO,  KC_NO},
        {KC_NO,     KC_NO,      KC_NO,  KC_NO},
        {KC_NO,     KC_NO,      KC_NO,  KC_NO}
    }
};
