// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐
     * │ 7 │ 8 │ 9 │ / │
     * ├───┼───┼───┼───┤
     * │ 4 │ 5 │ 6 │ * │
     * ├───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │ - │
     * ├───┼───┼───┼───┤
     * │ 0 │ . │Ent│ + │
     * └───┴───┴───┴───┘
     */
    [0] = LAYOUT(
        KC_TAB,  KC_Q,    KC_W,    KC_E,   KC_R,     KC_T,
        KC_LCTL, KC_A,    KC_S,    KC_D,   KC_F,     KC_G,
        KC_LSFT, KC_Z,    KC_X,    KC_C,   KC_V,     KC_B,
                          KC_LCMD, KC_SPC, MO(2),    KC_BSPC,


        KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,     KC_PMNS,
        KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN,  KC_QUOTE,
        KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLASH, KC_RSFT,
                 MO(1),   KC_ENT,  KC_RCMD
    ),
    [1] = LAYOUT(
        _______, KC_LABK, KC_LBRC, KC_LCBR, KC_LPRN, _______,
        _______, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,
        _______, _______, _______, _______, _______, _______,
                          _______, _______, _______, _______,


        _______, KC_RPRN, KC_RCBR, KC_RBRC , KC_RABK, _______,
        KC_RGHT, KC_DOWN, KC_UP  , KC_LEFT , KC_ESC , _______,
        _______, _______, _______, _______, _______, _______,
                 _______, _______, _______
    ),
    [2] = LAYOUT(
        _______, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC,
        _______, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,
        _______, _______, _______, _______, _______, _______,
                          _______, _______, _______, _______,


        KC_CIRC, KC_AMPR, KC_ASTR, KC_PEQL, KC_PPLS, _______,
        KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , _______,
        _______, _______, _______, _______, _______, _______,
                 _______, _______, _______
    )
};
