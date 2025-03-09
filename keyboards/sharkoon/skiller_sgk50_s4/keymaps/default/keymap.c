// Copyright 2024 JoyLee (@itarze)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_60_iso(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,     KC_5,    KC_6,    KC_7,     KC_8,     KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,     KC_T,    KC_Y,    KC_U,     KC_I,     KC_O,    KC_P,    KC_LBRC, KC_RBRC,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,     KC_G,    KC_H,    KC_J,     KC_K,     KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,
        KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,     KC_V,    KC_B,    KC_N,     KC_M,     KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT,                             KC_SPC,                               KC_RALT, MO(1),   KC_APP,  KC_RCTL
    ),

    [1] = LAYOUT_60_iso(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,   KC_F6,   KC_F7,    KC_F8,    KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        _______, _______, _______, _______, _______,  _______, KC_INS,  _______,  KC_UP,    KC_PAUS, KC_PGUP, KC_HOME, KC_PSCR,
        _______, _______, _______, _______, _______,  _______, KC_SCRL, KC_LEFT,  KC_DOWN,  KC_RGHT, KC_PGDN, KC_END,  RM_VALU, _______,
        _______, _______, _______, _______, _______,  _______, _______, _______,  KC_MUTE,  KC_VOLD, KC_VOLU, RM_VALD,          _______,
        _______, GU_TOGG, _______,                             _______,                              _______, _______, RM_HUEU, RM_NEXT
    )
};
