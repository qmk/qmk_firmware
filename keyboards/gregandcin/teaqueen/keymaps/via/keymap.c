// Copyright 2018-2023 Mattia Dal Ben <matthewdibi@gmail.com> gregandcin <gregandcinbusiness@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum custom_layer {
    _QWERTY,
    _SYMB,
    _NAV
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_QWERTY] = LAYOUT(
		KC_ESC,  KC_1,    KC_2,  KC_3,    KC_4,  KC_5,   KC_6,                    KC_7,  KC_8,   KC_9,  KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
		KC_TAB,           KC_Q,  KC_W,    KC_E,  KC_R,   KC_T,                    KC_Y,  KC_U,   KC_I,  KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
		KC_CAPS,          KC_A,  KC_S,    KC_D,  KC_F,   KC_G,                    KC_H,  KC_J,   KC_K,  KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
		KC_LSFT,          KC_Z,  KC_X,    KC_C,  KC_V,   KC_B,                    MO(1), KC_N,   KC_M,  KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(2),
		KC_LCTL, KC_LGUI,        KC_LALT,        KC_SPC, MO(1),                          KC_SPC,        KC_RALT,                   KC_RGUI, KC_RCTL),

	[_SYMB] = LAYOUT(
		KC_GRV,  KC_F1,  KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,              KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS,
		KC_TRNS,         KC_TRNS, KC_UP,   KC_TRNS, KC_TRNS, KC_TRNS,             KC_TRNS, KC_TRNS, KC_INS,  KC_HOME, KC_PGUP, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS,         KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS,             KC_TRNS, KC_TRNS, KC_DEL,  KC_END,  KC_PGDN, KC_TRNS,          KC_TRNS,
		KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		QK_BOOT,  KC_TRNS,          KC_TRNS,          KC_TRNS, KC_TRNS,                      KC_TRNS,          KC_TRNS,                    KC_TRNS, QK_BOOT),

	 [_NAV] = LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,          KC_BTN2, KC_MS_U,  KC_BTN1, KC_WH_U, KC_TRNS,            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS,          KC_MS_L, KC_MS_D,  KC_MS_R, KC_WH_D, KC_TRNS,            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
		KC_TRNS,          KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS,          KC_TRNS,           KC_TRNS, KC_TRNS,                     KC_TRNS,          KC_TRNS,                   KC_TRNS, KC_TRNS),
};

