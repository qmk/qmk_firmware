// Copyright 2022 Charue Design
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN0,
    _FN1,
    _FN2,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT_all(
      KC_F1, KC_F2,   QK_GESC,  KC_1,  KC_2,  KC_3,  KC_4,  KC_5,  KC_6,  KC_7,  KC_8,   KC_9,   KC_0,   KC_MINS, KC_EQL, KC_GRV, KC_BSPC,   KC_VOLU,
      KC_F3, KC_F4,     KC_TAB,   KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,  KC_Y,  KC_U,  KC_I,   KC_O,   KC_P,   KC_LBRC, KC_RBRC,     KC_BSLS,    KC_VOLD,
      KC_F5, KC_F6,      KC_CAPS,  KC_A,  KC_S,  KC_D,  KC_F,  KC_G,  KC_H,  KC_J,  KC_K,   KC_L,   KC_SCLN, KC_QUOT,       KC_ENT,          KC_MUTE,
      KC_F7, KC_F8,   KC_LSFT, KC_BSLS, KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,  KC_N,  KC_M, KC_COMM, KC_DOT, KC_SLSH,    KC_RSFT,       KC_UP,   KC_MNXT,
      KC_F9, KC_F10,  KC_LCTL,   KC_LGUI,   KC_LALT,     MO(_FN0),     KC_SPC,        KC_SPC,     KC_RALT,                KC_LEFT, KC_DOWN, KC_RIGHT
    ),
    [_FN0] = LAYOUT_all(
      KC_F11, KC_F12,  QK_BOOT,   KC_1,  KC_2,  KC_3,  KC_4,  KC_5,  KC_6,  KC_7,  KC_8,   KC_9,   KC_0,   KC_MINS, KC_EQL, KC_GRV, KC_BSPC,   KC_VOLU,
      KC_F13, KC_F14,   KC_TAB,   KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,  KC_Y,  KC_U,  KC_I,   KC_O,   KC_P,   KC_LBRC, KC_RBRC,     KC_BSLS,    KC_VOLD,
      KC_F15, KC_F16,    KC_CAPS,  KC_A,  KC_S,  KC_D,  KC_F,  KC_G,  KC_H,  KC_J,  KC_K,   KC_L,   KC_SCLN, KC_QUOT,       KC_ENT,          KC_MUTE,
      KC_F17, KC_F18, KC_LSFT, KC_BSLS, KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,  KC_N,  KC_M, KC_COMM, KC_DOT, KC_SLSH,    KC_RSFT,       KC_UP,   KC_MNXT,
      KC_F19, KC_F20, KC_LCTL,   KC_LGUI,   KC_LALT,     KC_TRNS,       KC_SPC,       KC_SPC,     KC_RALT,                KC_LEFT, KC_DOWN, KC_RIGHT
    ),
    [_FN1] = LAYOUT_all(
      KC_TRNS, KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS,     KC_TRNS,     KC_TRNS,
      KC_TRNS, KC_TRNS,    KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,        KC_TRNS,          KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,        KC_TRNS,           KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_LCTL,   KC_TRNS,   KC_TRNS,         KC_TRNS,         KC_TRNS,          KC_TRNS,         KC_TRNS,                                 KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [_FN2] = LAYOUT_all(
      KC_TRNS, KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS,     KC_TRNS,     KC_TRNS,
      KC_TRNS, KC_TRNS,    KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,        KC_TRNS,          KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,        KC_TRNS,           KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_LCTL,   KC_TRNS,   KC_TRNS,         KC_TRNS,         KC_TRNS,          KC_TRNS,         KC_TRNS,                                 KC_TRNS, KC_TRNS, KC_TRNS
    )
};
