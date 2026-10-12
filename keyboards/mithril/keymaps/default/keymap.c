// Copyright 2024 sanfeps (@sanfeps)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                KC_6,    KC_7,    KC_8,    KC_9,     KC_0,    KC_MINS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                KC_Y,    KC_U,    KC_I,    KC_O,     KC_P,    KC_BSLS,
        KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                KC_H,    KC_J,    KC_K,    KC_L,     KC_SCLN, KC_QUOT,
        KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                KC_N,    KC_M,    KC_COMM, KC_DOT,   KC_SLSH, KC_EQL,
                                            KC_LALT, KC_BSPC, MO(1),              KC_ENT, KC_SPC,  KC_RGUI
    ),

    [1] = LAYOUT(
        KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                               KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,  KC_F11,
        KC_TAB,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                             XXXXXXX, KC_LBRC, KC_RBRC, KC_PLUS,  XXXXXXX, KC_GRV,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                             KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, XXXXXXX, XXXXXXX,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, KC_DEL,
                                            XXXXXXX, XXXXXXX, _______,            MO(2),  KC_ENT,  XXXXXXX
    ),

    [2] = LAYOUT(
        RM_TOGG, RM_PREV, RM_NEXT, XXXXXXX, XXXXXXX, XXXXXXX,                             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,
        XXXXXXX, RM_SPDD, RM_SPDU, XXXXXXX, XXXXXXX, XXXXXXX,                             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                             RM_HUED, RM_VALD, RM_VALU, RM_HUEU,  XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                             XXXXXXX, RM_SATD, RM_SATU, XXXXXXX,  XXXXXXX, QK_BOOT,
                                            XXXXXXX, XXXXXXX, XXXXXXX,            _______, XXXXXXX, XXXXXXX
    ),
};
