// Copyright 2026 11customs
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layer_names {
    _BL,
    _FL,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BL] = LAYOUT_65_ansi_blocker(
        QK_GRAVE_ESCAPE, KC_1,        KC_2,        KC_3,        KC_4,          KC_5,          KC_6,          KC_7,          KC_8,          KC_9,          KC_0,          KC_MINUS,    KC_EQUAL,         KC_BACKSPACE,    KC_INSERT,
        KC_TAB,          KC_Q,        KC_W,        KC_E,        KC_R,          KC_T,          KC_Y,          KC_U,          KC_I,          KC_O,          KC_P,          KC_LEFT_BRACKET, KC_RIGHT_BRACKET, KC_BACKSLASH,    KC_DELETE,
        KC_CAPS_LOCK,    KC_A,        KC_S,        KC_D,        KC_F,          KC_G,          KC_H,          KC_J,          KC_K,          KC_L,          KC_SEMICOLON,  KC_QUOTE,         KC_ENTER,                            KC_PAGE_UP,
        KC_LEFT_SHIFT,   KC_Z,        KC_X,        KC_C,        KC_V,          KC_B,          KC_N,          KC_M,          KC_COMMA,      KC_DOT,        KC_SLASH,      KC_RIGHT_SHIFT,                          KC_UP,          KC_PAGE_DOWN,
        KC_LEFT_CTRL,    KC_RWIN,     KC_LALT,                   KC_SPC,                                         KC_RALT,       KC_RIGHT_CTRL, MO(_FL),                                                  KC_LEFT,         KC_DOWN,        KC_RIGHT
    ),

    [_FL] = LAYOUT_65_ansi_blocker(
        KC_GRAVE, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  QK_BOOT, _______,
        _______,  _______, _______, _______, _______, _______, _______, _______, KC_PSCR, KC_SCRL, KC_PAUS, _______, _______, _______, _______,
        _______,  _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGUP, _______, _______, _______, _______,
        _______,  _______, _______, _______, _______, _______, _______, _______, KC_END,  KC_PGDN, _______, _______, _______, _______,
        _______,  _______, _______,                     _______,                             _______, _______, _______, _______, _______, _______
    ),
};
