// Copyright 2025 @v3lmx
// SPDX-License-Identifier: GPL-3.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
    [0] = LAYOUT_split_3x5_3_ex2(
        KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_LBRC,        KC_RBRC,    KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,
        KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   XXXXXXX,        XXXXXXX,    KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,
        KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,                               KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,
                                KC_ESC, MO(1),  KC_TAB,         KC_ENT,     MO(2),  KC_BSPC
    ),
    [1] = LAYOUT_split_3x5_3_ex2(
        KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   _______,        _______,    KC_6,   KC_7,   KC_8,   KC_9,   KC_0,
        XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,_______,        _______,    KC_LEFT,KC_DOWN,KC_UP,  KC_RIGHT,XXXXXXX,
        XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,                            XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
                                KC_LGUI,_______,KC_SPC,         KC_ENT,     XXXXXXX,  KC_RALT
  ),
    [2] = LAYOUT_split_3x5_3_ex2(
        KC_EXLM, KC_AT,KC_HASH, KC_DLR, KC_PERC,_______,        _______,    KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,
        XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,_______,        _______,    KC_MINS,KC_EQL, KC_LBRC,KC_RBRC,KC_BSLS,
        XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,                            KC_UNDS,KC_PLUS,KC_LCBR,KC_RCBR,KC_PIPE,
                                KC_LGUI,XXXXXXX,  KC_SPC,         KC_ENT,     _______,KC_RALT
  )
    // clang-format on
};
