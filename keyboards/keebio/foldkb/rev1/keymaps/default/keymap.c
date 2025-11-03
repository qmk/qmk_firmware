// Copyright 2025 Keebio (@keebio)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
    KC_MUTE, KC_ESC,  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
    KC_HOME,          KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
    KC_END,           KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
    KC_PGUP,          KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(1),
    KC_PGDN,          KC_LCTL, KC_LGUI, KC_LALT, MO(1),   KC_SPC,  KC_SPC,      KC_SPC,  KC_SPC,  KC_RALT, KC_RGUI, KC_MENU, KC_RCTL
  ),
  [1] = LAYOUT(
    KC_MUTE, QK_BOOT, KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  _______, KC_DEL,
    BL_STEP,          _______, UG_SATD, UG_SATU, _______, _______, _______,     _______, KC_7,    KC_8,    KC_9,    _______, _______, _______, _______,
    UG_NEXT,          _______, UG_VALD, UG_VALU, _______, _______, _______,     _______, KC_4,    KC_5,    KC_6,    _______, _______,          _______,
    KC_VOLU,          _______, UG_HUED, UG_HUEU, _______, _______, _______,     _______, KC_1,    KC_2,    KC_3,    _______, _______, _______,
    KC_VOLD,          _______, _______, _______, _______, _______, _______,     _______, KC_0,    _______, _______, _______, _______
  ),
};
