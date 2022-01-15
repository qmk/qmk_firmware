// Copyright 2022 s8erdude (@jpuerto96)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT_3u(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_MIN, KC_PLUS,  KC_BSPC, KC_INS, KC_HOME, KC_NLCK,    KC_DIV,    KC_MULT, KC_MIN,
        KC_TAB, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,  KC_P,  KC_LBRC, KC_RBRC, KC_LINE, KC_END, KC_DEL, KC_7, KC_8, KC_9,
        KC_CLCK, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_4, KC_5, KC_6, KC_PLUS,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP, KC_1, KC_2, KC_3,
        KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, KC_RGUI, KC_RMEN, KC_LEFT, KC_DOWN, KC_RIGHT, KC_0, KC_DOT, KC_ENT
    )
};
