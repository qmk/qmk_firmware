// Copyright 2026 SEApodEErman
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    _BASE = 0,
    _FN,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * LAYOUT_all is the union of every switch position on the PCB, including
     * positions that are mutually exclusive on a single build: all three space
     * cells are KC_SPACE so the 6.25u, 7u and 3u-1u-3u bottom rows work, and
     * the top-right switch sits next to the rotary encoder.
     */
    [_BASE] = LAYOUT_all(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_HOME, KC_AUDIO_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_BSPC,   KC_PGUP,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_PGDN,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  KC_END,
        KC_LSFT, KC_BSLS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_DEL,
        KC_LCTL, KC_LGUI, KC_LALT, KC_SPC,  KC_SPC,  KC_SPC,  KC_RALT, MO(_FN), KC_LEFT, KC_DOWN, KC_RIGHT
    ),

    [_FN] = LAYOUT_all(
        QK_BOOT, KC_PSCR, KC_SCRL, KC_PAUS, _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, KC_VOLD, KC_VOLU, KC_MUTE, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_FN]   = {ENCODER_CCW_CW(KC_PGDN, KC_PGUP)},
};
#endif
