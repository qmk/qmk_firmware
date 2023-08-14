// Copyright 2021 QMK / NachoxMacho
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┌───┬───┬───┬───┐
     * │ ` │Esc│Tab│MO1│Bsp│
     * ├───┼───┼───┼───┼───┤
     * │ , │Num│ / │ * │ - │
     * ├───┼───┼───┼───┼───┤
     * │Gui│ 7 │ 8 │ 9 │   │
     * ├───┼───┼───┼───┤ + │
     * │Alt│ 4 │ 5 │ 6 │   │
     * ├───┼───┼───┼───┼───┤
     * │Shi│ 1 │ 2 │ 3 │   │
     * ├───┼───┴───┼───┤Ent│
     * │Ctr│ 0     │ . │   │
     * └───┴───────┴───┴───┘
     */
    [0] = LAYOUT_numpad_6x5(
        KC_GRV,  KC_ESC, KC_TAB,  MO(1),   KC_BSPC,
        KC_COMM, KC_NUM, KC_PSLS, KC_PAST, KC_PMNS,
        KC_LGUI, KC_P7,  KC_P8,   KC_P9,
        KC_LALT, KC_P4,  KC_P5,   KC_P6,   KC_PPLS,
        KC_LSFT, KC_P1,  KC_P2,   KC_P3,
        KC_LCTL, KC_P0,           KC_PDOT, KC_PENT
    ),

    /*
     * ┌───┌───┐───┬───┬───┐
     * │ ` │Rst│Tab│MO1│Bsp│
     * ├───┼───┘───┼───┼───┤
     * │ , │Num│ / │ * │ - │
     * ├───┼───┼───┼───┼───┤
     * │Gui│Hom│ ↑ │PgU│   │
     * ├───┼───┼───┼───┤ + │
     * │Alt│ ← │   │ → │   │
     * ├───┼───┼───┼───┤───┤
     * │Shi│End│ ↓ │PgD│   │
     * ├───┼───┴───┼───┤Ent│
     * │Ctr│Insert │Del│   │
     * └───┴───────┴───┘───┘
     */
    [1] = LAYOUT_numpad_6x5(
        _______, QK_BOOT,   _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______, KC_HOME, KC_UP,   KC_PGUP,
        _______, KC_LEFT, XXXXXXX, KC_RGHT, _______,
        _______, KC_END,  KC_DOWN, KC_PGDN,
        _______, KC_INS,           KC_DEL,  _______
    )
};
