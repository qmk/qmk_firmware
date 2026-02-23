// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Base
    [0] = LAYOUT_ortho_3x12(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,   KC_J,   KC_K,    KC_L,    MO(1),   KC_SPC,
        KC_LCTL, KC_LALT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_N,   KC_M,    KC_RGUI, KC_UP,   KC_DOWN
    ),
    // Fn
    [1] = LAYOUT_ortho_3x12(
        KC_TAB,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,   KC_7,   KC_8,    KC_9,    KC_0,    KC_DEL,
        _______, S(KC_EQL), KC_MINS, KC_SLSH, KC_PAST, KC_LBRC, KC_RBRC, KC_BSLS, KC_SCLN, KC_QUOT, _______, KC_ENT,
        _______, _______, KC_EQL, RM_TOGG, RM_HUEU, RM_NEXT, KC_GRV, KC_COMM, KC_DOT,  _______, KC_LEFT, KC_RIGHT
    )
};
