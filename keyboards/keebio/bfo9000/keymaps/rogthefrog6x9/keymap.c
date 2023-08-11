// Copyright 2022 rogthefrog
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum custom_layers {
    _BASE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT(
    KC_ESC,  KC_CALC, KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,         KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_VOLU, KC_MUTE,
    KC_NUM,  KC_INS,  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,          KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_VOLD, KC_HOME,
    KC_P7,   KC_P8,   KC_P9,   KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_END,
    KC_P4,   KC_P5,   KC_P6,   KC_BSPC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,          KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  KC_INS,  KC_PGUP,
    KC_P1,   KC_P2,   KC_P3,   KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,          KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RCTL, KC_APP,  KC_UP,   KC_PGDN,
    KC_P0,   KC_PDOT, KC_ENT,  KC_LCTL, KC_LGUI, KC_LALT, KC_CAPS, KC_ENT,  KC_BSPC,       KC_SPC,  KC_BSPC, KC_RGUI, KC_CUT,  KC_COPY, KC_PSTE, KC_LEFT, KC_DOWN, KC_RGHT
)
};
