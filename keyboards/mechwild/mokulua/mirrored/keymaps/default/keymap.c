// Copyright 2022 Kyle McCreery (@kylemccreery)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#define FN1_SPC     LT(1, KC_SPC)
#define FN2_SPC     LT(2, KC_SPC)

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN1,
    _FN2,
    _FN3
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,                         KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_BSPC, _______,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_RBRC, KC_BSLS,
        MO(1),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,                         KC_SCLN, KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT, KC_ENT,
        KC_LSFT, _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_MUTE,    KC_MUTE, KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT, MO(2),      FN1_SPC, FN2_SPC,       RGB_RMOD,   RGB_MOD,    FN2_SPC, FN1_SPC,       MO(2),   KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_FN1] = LAYOUT(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                        KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______, KC_DEL,  _______,
        _______, _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, KC_LBRC, KC_RBRC, _______,
        _______, _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, KC_SCLN, _______,
        _______, _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, KC_SLSH, KC_PGUP, _______,
        _______, _______, _______, _______,     _______, _______,      _______,    _______,      _______, _______,     _______, KC_HOME, KC_PGDN, KC_END
    ),
    [_FN2] = LAYOUT(
        _______, KC_F11,  KC_F12,  _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, RESET,   _______, _______,                      _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______,     _______, _______,      _______,    _______,      _______, _______,     _______, _______, _______, _______
    ),
    [_FN3] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, RGB_MOD,    _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______,     _______, _______,      _______,    _______,      _______, _______,     _______, _______, _______, _______
    )
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_PGDN, KC_PGUP) },
    [_FN1]  = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [_FN2]  = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [_FN3]  = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
};
#endif
