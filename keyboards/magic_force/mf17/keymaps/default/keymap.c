// Copyright 2012,2013 gezhaoyou <gezhaoyou@126.com>
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_numpad_5x4(
        KC_NUM,  KC_PSLS, KC_PAST, LT(1, KC_PMNS),
        KC_P7,   KC_P8,   KC_P9,
        KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        KC_P1,   KC_P2,   KC_P3,
        KC_P0,   KC_PDOT,          KC_PENT
    ),
    [1] = LAYOUT_numpad_5x4(
        _______, KC_CALC, KC_BSPC, _______,
        RM_NEXT, RM_VALU, RM_HUEU,
        RM_SPDD, RM_TOGG, RM_SPDU, QK_BOOT,
        RM_PREV, RM_VALD, RM_HUED,
        _______, _______,          EE_CLR
    ),
};
