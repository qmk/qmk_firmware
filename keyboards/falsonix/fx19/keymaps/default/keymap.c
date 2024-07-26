// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#define LAYOUT_numpad_4x5( \
    k00, k01, k02, k03, \
    k04, k05, k06, \
    k07, k08, k09, k16, \
    k10, k11, k12, \
    k13, k14, k15, k17 \
) { \
    { k00, k01, k02, k03 }, \
    { k04, k05, k06, KC_NO }, \
    { k07, k08, k09, k16 }, \
    { k10, k11, k12, KC_NO }, \
    { k13, k14, k15, k17 } \
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
    *┌───┬───┬───┬───┐
    * Num│ / │ * │ - │
    *├───┼───┼───┼───┤
    *│ 7 │ 8 │ 9 │ + │
    *├───┼───┼───┤   │
    *│ 4 │ 5 │ 6 │   │
    *├───┼───┼───┤───┤
    *│ 1 │ 2 │ 3 │   │
    *├───┼───┼───┤Ent│
    *│Win│ 0 │ . │   │
    *┴───┴───┴───┴───┘
    */
    [0] = LAYOUT_numpad_4x5(
        KC_LNUM,   KC_PSLS,   KC_PAST,   KC_PMNS,
        KC_P7,     KC_P8,     KC_P9,     KC_PPLS,
        KC_P4,     KC_P5,     KC_P6,   
        KC_P1,     KC_P2,     KC_P3,     KC_PENT,  
        KC_RWIN,   KC_P0,     KC_PDOT
    )
};
