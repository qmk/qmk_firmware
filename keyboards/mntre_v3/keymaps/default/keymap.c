// Copyright 2021 Cedric Vincent (@cdc-mkb)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        KC_ESC,    KC_F1,   KC_F2,    KC_F3,    KC_F4,   KC_F5,   KC_F6,    KC_F7,   KC_F8,     KC_F9,    KC_F10,  KC_F11,      KC_F12,      MO(_FN),
        KC_GRAVE,  KC_1,    KC_2,     KC_3,     KC_4,    KC_5,    KC_6,     KC_7,    KC_8,      KC_9,     KC_0,    KC_MINUS,    KC_EQUAL,    KC_BSPC,
        KC_TAB,    KC_Q,    KC_W,     KC_E,     KC_R,    KC_T,    KC_Y,     KC_U,    KC_I,      KC_O,     KC_P,    KC_LBRC,     KC_RBRC,     KC_BSLS,
        KC_LCTL,   KC_A,    KC_S,     KC_D,     KC_F,    KC_G,    KC_H,     KC_J,    KC_K,      KC_L,     KC_SCLN, KC_QUOTE,    KC_ENTER,
        KC_LSFT,   KC_DEL,  KC_Z,     KC_X,     KC_C,    KC_V,    KC_B,     KC_N,    KC_M,      KC_COMMA, KC_DOT,  KC_SLASH,    KC_UP,       KC_RSFT,
        KC_RGUI,   KC_LGUI, KC_LALT,  KC_SPACE, KC_SPACE, KC_SPACE, KC_RALT, KC_RCTL, KC_LEFT,  KC_DOWN, KC_RIGHT
    ),

    [_FN] = LAYOUT(
        _______, BL_DOWN,  BL_UP,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______,  _______, _______, QK_BOOT, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
        _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______
	),
};
