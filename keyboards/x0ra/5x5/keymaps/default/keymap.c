// Copyright 2026 X0RA
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers { _LAYER_ZERO, _LAYER_ONE, _LAYER_TWO, _LAYER_THREE };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_LAYER_ZERO] = LAYOUT(
        TO(1),     KC_PSLS,   KC_PAST,   KC_PMNS,   KC_DEL,
        KC_PGUP,   KC_P7,     KC_P8,     KC_P9,     KC_MNXT,
        KC_PGDN,   KC_P4,     KC_P5,     KC_P6,     KC_MPLY,
        KC_PSCR,   KC_P1,     KC_P2,     KC_P3,     KC_MPRV,
        KC_HOME,   KC_P0,     KC_ESC,    KC_PDOT,   KC_PENT
    ),
    [_LAYER_ONE] = LAYOUT(
        TO(2),     KC_NO,     KC_NO,     KC_NO,     KC_NO,
        KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
        KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
        KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
        KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO
    ),
    [_LAYER_TWO] = LAYOUT(
        TO(3),     KC_NO,     KC_NO,     KC_NO,     KC_NO,
        KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
        KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
        KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
        KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO
    ),
    [_LAYER_THREE] = LAYOUT(
        TO(0),     KC_NO,     KC_NO,     KC_NO,     KC_NO,
        KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
        KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
        KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
        KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO
    )
};
