// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    NUM_P,
    ARROW,
    NUM2,
    NUM3
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┐
     * │TG1│
     * ├───┼───┬───┬───┐
     * │ 7 │ 8 │ 9 │ + │
     * ├───┼───┼───┼───┤
     * │ 4 │ 5 │ 6 │ % │
     * ├───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │ = │
     * ├───┼───┼───┼───┤
     * │ 0 │00 │ . │Ent│
     * └───┴───┴───┴───┘
     */
    [0] = LAYOUT_ortho_5x4(
        TG(1),
        KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_P4,   KC_P5,   KC_P6,   KC_PERC,
        KC_P1,   KC_P2,   KC_P3,   KC_EQL,
        KC_P0,   KC_P00,  KC_PDOT, KC_PENT
    ),

    /*
     * ┌───┐
     * │TG2│
     * ├───┼───┬───┬───┐
     * │Hom│ ↑ │PgU│ 3 │
     * ├───┼───┼───┼───┤
     * │ ← │   │ → │ 2 │
     * ├───┼───┼───┤───┤
     * │End│ ↓ │PgD│ 1 │
     * ├───┼───┼───┤───┤
     * │Ins│Spc│Del│Ent│
     * └───┴───┴───┘───┘
     */
    [1] = LAYOUT_ortho_5x4(
        TG(2),
        KC_HOME, KC_UP,   KC_PGUP, KC_3,
        KC_LEFT, XXXXXXX, KC_RGHT, KC_2,
        KC_END,  KC_DOWN, KC_PGDN, KC_1,
        KC_INS,  KC_SPC,  KC_DEL,  KC_PENT,
    ),

    /*
     * ┌───┐
     * │TG3│
     * ├───┼───┬───┬───┐
     * │ 7 │ 8 │ 9 │ + │
     * ├───┼───┼───┼───┤
     * │ 4 │ 5 │ 6 │ % │
     * ├───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │ = │
     * ├───┼───┼───┼───┤
     * │ 0 │00 │ . │Ent│
     * └───┴───┴───┴───┘
     */
    [2] = LAYOUT_ortho_5x4(
        TG(3),
        KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_P4,   KC_P5,   KC_P6,   KC_PERC,
        KC_P1,   KC_P2,   KC_P3,   KC_EQL,
        KC_P0,   KC_P00,  KC_PDOT, KC_PENT
    ),

    /*
     * ┌───┐
     * │TG0│
     * ├───┼───┬───┬───┐
     * │ 7 │ 8 │ 9 │ + │
     * ├───┼───┼───┼───┤
     * │ 4 │ 5 │ 6 │ % │
     * ├───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │ = │
     * ├───┼───┼───┼───┤
     * │ 0 │00 │ . │Ent│
     * └───┴───┴───┴───┘
     */
    [3] = LAYOUT_ortho_5x4(
        TG(0),
        KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_P4,   KC_P5,   KC_P6,   KC_PERC,
        KC_P1,   KC_P2,   KC_P3,   KC_EQL,
        KC_P0,   KC_P00,  KC_PDOT, KC_PENT
    )
};
