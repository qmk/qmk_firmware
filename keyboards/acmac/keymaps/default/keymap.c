// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

//enum custom_layers {
//    _0
//    _1
//    _2
//    _3
//};

//#define LOWER MO(_LOWER)
//#define RAISE MO(_RAISE)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* BASE
     * ┌───┬───┬───┬───┐┌───┬───┬───┬───┐
     * |Esc|   |   |   ||   |   |   |   |
     * ├───┼───┼───┼───┤├───┼───┼───┼───┤
     * |Del|   |   |   ||   |   | * | / |
     * ├───┼───┼───┼───┤├───┼───┼───┼───┤
     * │   │   │   │   │| 7 | 8 | 9 | - |
     * ├───┼───┼───┼───┤├───┼───┼───┼───┤
     * │   │   │   │   │| 4 | 5 | 6 | + |
     * ├───┼───┼───┼───┤├───┼───┼───┼───┤
     * │   │   │   │   │| 1 | 2 | 3 |Ent|
     * ├───┼───┼───┼───┤├───┼───┼───┼─ ─┤
     * │   │   │   │   || 0 | . | ' |Ent|
     * └───┴───┴───┴───┘└───┴───┴───┴───┘
     */
    [0] = LAYOUT (
        KC_ESC,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_DEL,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PAST, KC_PSLS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_P7,   KC_P8,   KC_P9,   KC_PMNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_P1,   KC_P2,   KC_P3,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_P0,   KC_PDOT, KC_COMM, KC_PENT,
    ),

    [1] = LAYOUT (
        _______,  _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,
        KC_TRNS,  _______, _______, _______, _______, _______, _______, _______,
    ),
};

