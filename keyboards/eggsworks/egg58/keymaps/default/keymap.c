// Copyright 2022-2023 Travis Mick (@tmick0)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layer_names {
    _BASE,
    _FN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BASE] = LAYOUT(
  KC_GRV,   KC_1,    KC_2,    KC_3,    KC_4,      KC_5,                    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,
  KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,      KC_T,                    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_EQL,
  KC_LSFT,  KC_A,    KC_S,    KC_D,    KC_F,      KC_G,                    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  KC_LCTL,  KC_Z,    KC_X,    KC_C,    KC_V,      KC_B,                    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_BSPC,
            KC_LGUI, KC_LALT, OSL(1),  MO(1),   KC_SPC,                  KC_ENT,   MO(1), KC_LBRC, KC_RBRC, KC_BSLS
),

[_FN] = LAYOUT(
  KC_ESC,     KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                  KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
  KC_TRNS,  KC_PGUP,   KC_UP, KC_PGDN, KC_TRNS, KC_VOLU,                KC_TRNS, KC_TRNS,  KC_INS, KC_TRNS, KC_PSCR,  KC_F12,
  KC_TRNS,  KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_VOLD,                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS,  KC_HOME, KC_TRNS,  KC_END, KC_TRNS, KC_MUTE,                KC_TRNS, KC_TRNS, RGB_HUI, RGB_SAI, RGB_VAI,  KC_DEL,
            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                KC_TRNS, KC_TRNS, RGB_SPI, RGB_MOD, RGB_TOG
)
};
