// Copyright 2023 tercy (@TercyKB)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "keymap_japanese.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    JP_AT,
        KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    JP_SCLN, JP_COLN,
        KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, JP_BSLS,
        KC_NO,   KC_NO,   KC_SPC,  TL_LOWR, KC_TAB,  KC_LALT, KC_RGUI, KC_ENT,  TL_UPPR, KC_GRV,  KC_NO,   KC_NO
    ),
    [1] = LAYOUT(
        KC_DEL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_PGUP, KC_NO,   KC_UP,   KC_NO,   KC_HOME, KC_PSCR,
        KC_TRNS, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  KC_NO,
        KC_TRNS, JP_MINS, JP_CIRC, JP_YEN,  JP_LBRC, JP_RBRC, KC_NO,   KC_BSPC, KC_NO,   KC_DEL,  KC_NO,   KC_NO,
        KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO
    ),
    [2] = LAYOUT(
        KC_DEL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_PGUP, KC_NO,   KC_UP,   KC_NO,   KC_HOME, KC_PSCR,
        KC_TRNS, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  KC_NO,
        KC_TRNS, JP_MINS, JP_CIRC, JP_YEN,  JP_LBRC, JP_RBRC, KC_NO,   KC_BSPC, KC_NO,   KC_DEL,  KC_NO,   KC_NO,
        KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO
    ),
    [3] = LAYOUT(
        KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_WH_U, KC_NO,   KC_MS_U, KC_NO,   KC_NO,   KC_NO,
        KC_TRNS, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, KC_NO,   KC_NO,
        KC_TRNS, KC_F11,  KC_F12,  KC_BTN1, KC_BTN2, KC_ACL0, KC_NO,   KC_WH_L, KC_NO,   KC_WH_R, KC_NO,   KC_NO,
        KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO
    )
};
