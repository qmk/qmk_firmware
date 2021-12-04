// Copyright 2021 Trent Hoh (@Trent Hoh)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _LAYER0,
    _LAYER1,
    _LAYER2,
    _LAYER3
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_LAYER0] = LAYOUT_ortho_4x12_1x2uC(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, 
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, 
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_LSFT, 
        KC_LCTL, KC_CAPS, KC_LALT, KC_LGUI, MO(1),   KC_SPC,           MO(2),   MO(2),   M(0),    M(1),    KC_ENT
    ),
    [_LAYER1] = LAYOUT_ortho_4x12_1x2uC(
        RESET,   KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_DEL,  KC_BSLS, KC_7,    KC_8,   KC_9,    RGB_TOG, KC_TRNS, 
        KC_TRNS, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_PLUS, KC_MINS, KC_4,    KC_5,   KC_6,    RGB_MOD, KC_TRNS, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_ASTR, KC_SLSH, KC_1,    KC_2,   KC_3,    KC_TRNS, KC_TRNS, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_0,             KC_TRNS, KC_TRNS, KC_DOT, KC_TRNS, KC_EQL
    ),
    [_LAYER2] = LAYOUT_ortho_4x12_1x2uC(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, 
        KC_TRNS, KC_PIPE, KC_AMPR, KC_LPRN, KC_RPRN, KC_PLUS, KC_MINS, KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, KC_TRNS, 
        KC_TRNS, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_ASTR, KC_SLSH, KC_TILD, KC_LABK, KC_RABK, KC_QUES, KC_TRNS, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [_LAYER3] = LAYOUT_ortho_4x12_1x2uC(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )
};
