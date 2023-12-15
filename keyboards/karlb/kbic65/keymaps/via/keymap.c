// Copyright 2021 Karl Berggren <@bkarl>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// Default ANSI keymap
[0] = LAYOUT_all(
KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,   _______,  KC_HOME,
KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,             KC_PGUP,
KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,                        KC_PGDN,
KC_LSFT,  _______,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,             KC_UP,    KC_END,
KC_LCTL,  KC_LGUI,  KC_LALT,                                KC_SPC,                                 KC_RALT,  MO(1),    KC_RCTL,   KC_LEFT,  KC_DOWN,  KC_RGHT),

[1] = LAYOUT_all(
KC_GRV,    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_DEL,   _______,  KC_INS,
_______,   _______,  KC_UP,    _______,  _______,  _______,  _______,  _______,  KC_PSCR,  KC_SCRL,  KC_PAUS,  KC_UP,    _______,  _______,            _______,
_______,   KC_LEFT,  KC_DOWN,  KC_RGHT,  _______,  _______,  _______,  _______,  KC_HOME,  KC_PGUP,  KC_LEFT,  KC_RGHT,  _______,                      _______,
_______,   _______,  _______,  _______,  _______,  _______,  QK_BOOT,    _______,  _______,  KC_END,   KC_PGDN,  KC_DOWN,  _______,            KC_PGUP,  _______,
_______,   _______,  _______,                                _______,                                _______,  _______,  _______, KC_HOME,   KC_PGDN,  KC_END)
};
