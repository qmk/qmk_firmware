// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
//

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	/*
     * ┌───┐┌───┬───┬───┬───┐
     * │Ply││Esc│Tab│MO1│Bsp│
     * └───┘├───┼───┼───┼───┤
     *      │Num│ / │ * │ - │
     *      ├───┼───┼───┼───┤
     *      │ 7 │ 8 │ 9 │   │
     * ┌───┐├───┼───┼───┤ + │
     * │Esc││ 4 │ 5 │ 6 │   │
     * └───┘├───┼───┼───┼───┤
     *      │ 1 │ 2 │ 3 │   │
     * ┌───┐├───┴───┼───┤Ent│
     * │ENT││   0   │ . │   │
     * └───┘└───────┴───┴───┘
     */
    [0] = LAYOUT(
        KC_MPLY, KC_ESC,  KC_TAB,  MO(1),   KC_BSPC,
                 KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
                 KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_ESC,  KC_P4,   KC_P5,   KC_P6,
                 KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        KC_ENT,  KC_P0,            KC_PDOT
    ),
    /*
     * ┌───┐┌───┬───┬───┬───┐
     * │Ply││Rst│Tab│MO1│Bsp│
     * └───┘├───┼───┼───┼───┤
     *      │Num│ / │ * │ - │
     *      ├───┼───┼───┼───┤
     *      │Hom│ ↑ │PgU│   │
     * ┌───┐├───┼───┼───┤ + │
     * │Esc││ ← │   │ → │   │
     * └───┘├───┼───┼───┼───┤
     *      │End│ ↓ │PgD│   │
     * ┌───┐├───┴───┼───┤Ent│
     * │ENT││Insert │Del│   │
     * └───┘└───────┴───┘───┘
     */
    [1] = LAYOUT(
        _______, QK_BOOT, _______, _______, _______,
                 _______, _______, _______, _______,
                 KC_HOME, KC_UP,   KC_PGUP, _______,
        _______, KC_LEFT, KC_NO,   KC_RGHT,
                 KC_END,  KC_DOWN, KC_PGDN, _______,
        _______, KC_INS,           KC_DEL
    )
};

#if defined(ENCODER_MAP_ENABLE)

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_DOWN, KC_UP),    ENCODER_CCW_CW(KC_LEFT, KC_RIGHT) },
    [1] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(KC_LEFT, KC_RIGHT), ENCODER_CCW_CW(_______, _______) },
};
#endif
