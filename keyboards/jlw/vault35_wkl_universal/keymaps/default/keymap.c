// Copyright 2024 jlw
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_all(
         KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,     KC_VOLU,      KC_Y,   KC_U,   KC_I,    KC_O,   KC_P,
         KC_A,   KC_S,   KC_D,   KC_F,   KC_G,     KC_VOLD,      KC_H,   KC_J,   KC_K,    KC_L,   KC_QUOT,
         KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,     RM_TOGG,      KC_N,   KC_M,   KC_COMM, KC_DOT, KC_SLSH,
         KC_ESC,         MO(1),  KC_ENT, KC_LEFT,  KC_DOWN,      KC_UP,  KC_RIGHT,                KC_BSPC
    ),

    [1] = LAYOUT_all(
         _______,  _______,  _______,  _______,  _______,  _______, _______,  KC_7,     KC_8,     KC_9,    KC_0,
         _______,  _______,  _______,  _______,  _______,  _______, _______,  KC_4,     KC_5,     KC_6,    _______,
         _______,  _______,  _______,  _______,  _______,  QK_BOOT, _______,  KC_1,     KC_2,     KC_3,    _______,
         _______,            _______,  _______,  _______,  _______, _______,  MO(2),                       _______
    ),

    [2] = LAYOUT_all(
         _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
         _______,  _______,  _______,  _______,  _______,  _______,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_LEFT,  _______,
         _______,  _______,  _______,  _______,  _______,  QK_BOOT,  _______,  _______,  _______,  _______,  _______,
         _______,            _______,  _______,  _______,  _______,  _______,  _______,                      _______
    )
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] =   { ENCODER_CCW_CW(RM_HUED, RM_HUEU) },
    [2] =   { ENCODER_CCW_CW(RM_VALD, RM_VALU) }
};
#endif

