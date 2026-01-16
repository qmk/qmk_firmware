// Copyright 2024 gtips (@gtips)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _LOWER,
    _RAISE,
    _ADJUST,
};

#define SF_SS RSFT_T(KC_SLSH)
#define SP_LO LT(_LOWER, KC_SPC)
#define SP_RA LT(_RAISE, KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
                          KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSPC,
                          KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_ENT,
              KC_UP,      KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,             SF_SS,
    KC_LEFT,  KC_DOWN,  KC_RGHT,    KC_LCTL,  KC_LALT,               SP_LO,                   SP_RA,                KC_LALT,  KC_RGUI,  KC_RCTL
    ),
    [_LOWER] = LAYOUT(
                          KC_TILD,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,   KC_DEL,
                          _______,  KC_UNDS,  KC_PLUS,  KC_LCBR,  KC_RCBR,  KC_PIPE,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  XXXXXXX,  KC_QUOT,
              _______,    _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    XXXXXXX,  XXXXXXX,  XXXXXXX,            KC_SLSH,
    _______,  _______,  _______,    _______,  _______,               _______,                 _______,              _______,  _______,  _______
    ),
    [_RAISE] = LAYOUT(
                          KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     _______,
                          _______,  KC_MINS,  KC_EQL,   KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_HOME,  KC_END,   KC_PGUP,  KC_PGDN,  XXXXXXX,  KC_DQUO,
              _______,    _______,  KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   XXXXXXX,  XXXXXXX,  XXXXXXX,            KC_QUES,
    _______,  _______,  _______,    _______,  _______,               _______,                 _______,              _______,  _______,  _______
    ),
    [_ADJUST] = LAYOUT(
                          UG_VALU,   UG_SATU, UG_HUEU,  UG_NEXT,  XXXXXXX,  UG_TOGG,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                          UG_VALD,   UG_SATD, UG_HUED,  UG_PREV,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
              KC_VOLU,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  QK_BOOT,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,
    KC_MUTE,  KC_VOLD,  KC_MPLY,    XXXXXXX,  XXXXXXX,               _______,                 _______,              XXXXXXX,  XXXXXXX,  XXXXXXX
    ),
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
