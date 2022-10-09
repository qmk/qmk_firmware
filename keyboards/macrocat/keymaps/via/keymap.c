// Copyright 2022 catmunch (@catmunch)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_4x4(
        KC_PPLS,   KC_9,       KC_8,   KC_7 ,
        KC_PMNS,   KC_6,       KC_5,   KC_4 ,
        KC_PDOT,   KC_3,       KC_2,   KC_1 ,
        KC_PENT,   KC_SPACE,   KC_P0,  MO(1)
    ),
    [1] = LAYOUT_ortho_4x4(
        KC_PAST,   KC_NO,      KC_NO,  KC_NO,
        KC_PSLS,   KC_LPRN,    KC_UP,  KC_RPRN,
        KC_COMM,   KC_LEFT,    KC_DOWN,KC_RIGHT,
        KC_TAB,    KC_BSPC,    KC_P0,  KC_TRNS
    ),
    [2] = LAYOUT_ortho_4x4(
        KC_NO,     KC_NO,      KC_NO,  KC_NO,
        KC_NO,     KC_NO,      KC_NO,  KC_NO,
        KC_NO,     KC_NO,      KC_NO,  KC_NO,
        KC_NO,     KC_NO,      KC_NO,  KC_NO
    ),
    [3] = LAYOUT_ortho_4x4(
        KC_NO,     KC_NO,      KC_NO,  KC_NO,
        KC_NO,     KC_NO,      KC_NO,  KC_NO,
        KC_NO,     KC_NO,      KC_NO,  KC_NO,
        KC_NO,     KC_NO,      KC_NO,  KC_NO
    )
};
