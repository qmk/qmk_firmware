// Copyright 2024 Richard Dawe
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#define LT1_SPC LT(1, KC_SPC)
#define LT2_ESC LT(2, KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base layer
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
        KC_TAB,  KC_Q,    KC_W,    KC_E,     KC_R,    KC_T,    KC_LBRC, KC_RBRC,  KC_Y,    KC_U,     KC_I,    KC_O,    KC_P,    KC_BSPC,
        LT2_ESC, KC_A,    KC_S,    KC_D,     KC_F,    KC_G,    KC_GRV,  KC_MINS,  KC_H,    KC_J,     KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,     KC_V,    KC_B,             KC_B,     KC_N,    KC_M,     KC_COMM, KC_DOT,  KC_UP,   KC_ENT,
        KC_LCTL, KC_LGUI, KC_LALT,           LT1_SPC,                             LT1_SPC,           KC_SLSH, KC_LEFT, KC_DOWN, KC_RIGHT
    ),

    /* Numbers and symbols layer
     */
    [1] = LAYOUT(
        KC_COLN, KC_1,    KC_2,    KC_3,     KC_4,    KC_5,    KC_LBRC, KC_RBRC,  KC_6,    KC_7,     KC_8,    KC_9,    KC_0,    KC_BSPC,
        KC_DOT,  S(KC_1), S(KC_2), S(KC_3),  S(KC_4), S(KC_5), KC_GRV,  KC_MINS,  S(KC_6), S(KC_7),  S(KC_8), S(KC_9), S(KC_0), KC_BSLS,
        _______, XXXXXXX, KC_GRV,  KC_TILD,  KC_PIPE, KC_PLUS,          KC_PLUS,  KC_MINS, KC_EQL,   KC_LBRC, KC_RBRC, KC_PGUP, _______,
        _______, _______, _______,           _______,                             _______,           XXXXXXX, KC_HOME, KC_PGDN, KC_END
    ),

    /* F-keys and media
     */
    [2] = LAYOUT(
        KC_F12,  KC_F1,   KC_F2,   KC_F3,    KC_F4,   KC_F5,   KC_LBRC, KC_RBRC,  KC_F6,   KC_F7,    KC_F8,   KC_F9,   KC_F10,  KC_F11,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, KC_GRV,  KC_MINS,  KC_LEFT, KC_DOWN,  KC_UP,   KC_RGHT, XXXXXXX, XXXXXXX,
        _______, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,          XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX, KC_MUTE, KC_VOLU, _______,
        _______, _______, _______,           _______,                             _______,           KC_MPLY, KC_MPRV, KC_VOLD, KC_MNXT
    )
};
