// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,  KC_1,       KC_2,          KC_3,    KC_4,          KC_5,    KC_F22,      KC_RBRC,   KC_PSCR,    KC_F23,  KC_6,  KC_7,  KC_8,    KC_9,    KC_0,           KC_MINS,
        KC_TAB,  KC_Q,       KC_W,          KC_E,    KC_R,          KC_T,    KC_F20,           KC_ENT,           KC_F21,  KC_Y,  KC_U,  KC_I,    KC_O,    KC_P,           KC_LBRC,
        KC_CAPS, KC_A,       KC_S,          KC_D,    KC_F,          KC_G,    KC_DEL,  KC_HOME, KC_UP,   KC_END,  KC_BSPC, KC_H,  KC_J,  KC_K,    KC_L,    KC_SCLN,        KC_QUOT,
        KC_RSFT, KC_Z,       KC_X,          KC_C,    KC_V,          KC_B,          KC_LEFT, KC_DOWN, KC_RGHT,             KC_N,  KC_M,  KC_COMM, KC_DOT,  KC_SLSH,        KC_RSFT,
        KC_LCTL, KC_LGUI,    KC_LALT,       KC_NUBS,         KC_SPC,         KC_LSFT,                            KC_ENT,    KC_SPC,     KC_RALT, MO(1),   RGUI_T(KC_APP), KC_RCTL
    ),
    [1] = LAYOUT(
        KC_ESC,  KC_F1,      KC_F2,         KC_F3,   KC_F4,         KC_F5,   KC_F22,     KC_PAUS,   KC_PSCR,     KC_F23,  KC_F6, KC_F7, KC_F8,   KC_F9,   KC_F10,         KC_F11,
        KC_TAB,  KC_PGUP,    LCTL(KC_LEFT), KC_UP,   LCTL(KC_RGHT), KC_PGDN, KC_F20,           KC_ENT,           KC_F21,  KC_NO, KC_NO, KC_NO,   KC_NO,   KC_NO,          KC_F12,
        KC_CAPS, KC_HOME,    KC_LEFT,       KC_DOWN, KC_RGHT,       KC_END,  KC_DEL,  KC_HOME, KC_VOLU, KC_END,  KC_BSPC, KC_NO, KC_NO, KC_NO,   KC_NO,   KC_NO,          KC_NO,
        KC_RSFT, LCA(KC_F2), KC_TAB,        KC_F2,   KC_F5,         KC_F23,           KC_MUTE, KC_VOLD, KC_MUTE,          KC_NO, KC_NO, KC_NO,   KC_NO,   KC_NO,          KC_RSFT,
        KC_LCTL, KC_LGUI,    KC_LALT,       KC_NUBS,         KC_SPC,         KC_LSFT,                            KC_ENT,    KC_SPC,     KC_RALT, _______, KC_APP,         KC_RCTL
    )
};
