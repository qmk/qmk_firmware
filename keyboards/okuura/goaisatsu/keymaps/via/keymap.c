// Copyright 2023 okuura (@okuura)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "keymap_japanese.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12,    KC_DEL,
        JP_ZKHK, JP_1,    JP_2,    JP_3,    JP_4,    JP_5,    JP_6,    JP_7,    JP_8,    JP_9,    JP_0,     JP_MINS,  JP_CIRC,   JP_YEN,   KC_BSPC,
        KC_TAB,  JP_Q,    JP_W,    JP_E,    JP_R,    JP_T,    JP_Y,    JP_U,    JP_I,    JP_O,    JP_P,     JP_AT,    JP_LBRC,   KC_ENT,
        KC_CAPS, JP_A,    JP_S,    JP_D,    JP_F,    JP_G,    JP_H,    JP_J,    JP_K,    JP_L,    JP_SCLN,  JP_COLN,  JP_RBRC,
        KC_LSFT, JP_Z,    JP_X,    JP_C,    JP_V,    JP_B,    JP_N,    JP_M,    JP_COMM, JP_DOT,  JP_SLSH,  JP_BSLS,  KC_UP,
        KC_LCTL, KC_LWIN, KC_LALT, JP_MHEN, JP_MHEN, KC_SPC,  KC_SPC, JP_HENK,  JP_HENK, JP_KANA, KC_LEFT,  KC_DOWN,  KC_RIGHT
    )
};