// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

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
    [0] = LAYOUT(
        KC_LNUM,   KC_PSLS,   KC_PAST,   KC_PMNS,
        KC_P7,     KC_P8,     KC_P9,     
        KC_P4,     KC_P5,     KC_P6,     KC_PPLS,
        KC_P1,     KC_P2,     KC_P3,     
        KC_RWIN,   KC_P0,     KC_PDOT,   KC_PENT
    )
};
