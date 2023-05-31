// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_3,    KC_8,    KC_2,    KC_4,    KC_7,    KC_9,    KC_5,    KC_6,    KC_1,    KC_0,    KC_UNDS, KC_TILD, KC_EQL,
        KC_E,    KC_I,    KC_W,    KC_R,    KC_U,    KC_O,    KC_T,    KC_Y,    KC_Q,    KC_P,    KC_LBRC, KC_TAB,  KC_RBRC,
        KC_D,    KC_K,    KC_S,    KC_F,    KC_J,    KC_L,    KC_G,    KC_H,    KC_A,    KC_SCLN, KC_QUOT, KC_CAPS, KC_BSLS,
        KC_C,    KC_COMM, KC_X,    KC_V,    KC_M,    KC_DOT,  KC_B,    KC_N,    KC_Z,    KC_SLSH, KC_LSFT, XXXXXXX, KC_LALT, XXXXXXX, KC_LCTL, KC_LGUI, XXXXXXX, XXXXXXX, XXXXXXX, KC_SPC,  KC_BSPC,
        KC_R,    KC_ESC,  KC_ENT,  KC_L
    )
};
