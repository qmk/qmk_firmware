// Copyright 2022 Chris Hoage (@chrishoage)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[0] = LAYOUT(
         KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,  KC_ESC,                                          KC_BSPC,    KC_6,    KC_7,    KC_8,   KC_9,    KC_0, KC_BSLS,
         KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T, KC_MINS,                                           KC_EQL,    KC_Y,    KC_U,    KC_I,   KC_O,    KC_P, KC_QUOT,
        KC_LSFT,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G, KC_LBRC,                                          KC_RBRC,    KC_H,    KC_J,    KC_K,   KC_L, KC_SCLN, KC_RSFT,
                    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,            KC_NO,                          KC_NO,             KC_N,    KC_M, KC_COMM, KC_DOT, KC_SLSH,
                                            KC_LCTL, KC_LALT, KC_LGUI,  KC_ENT,   MO(1),        MO(1),  KC_SPC, KC_RGUI, KC_RALT, KC_RCTL
    ),

	[1] = LAYOUT(
        KC_PAUS,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,  KC_ESC,                                           KC_DEL,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, KC_PSCR,
        KC_LCAP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                          KC_TRNS, KC_HOME, KC_PGDN, KC_PGUP,  KC_END, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                          KC_TRNS, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,                        KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                            KC_TRNS, KC_TRNS, KC_TRNS,  KC_SPC, KC_TRNS,      KC_TRNS,  KC_ENT, KC_TRNS, KC_TRNS, KC_TRNS
    ),

	[2] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,                         KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
};
// clang-format on
