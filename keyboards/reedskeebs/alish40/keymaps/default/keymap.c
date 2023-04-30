// Copyright 2022 Kyle McCreery (@kylemccreery)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [0] = LAYOUT_all(
        KC_ESC,            KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,     KC_O,     KC_P,     KC_BSPC,
        MO(1),             KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,     KC_L,     KC_QUOT,  KC_ENT,
        KC_LSFT,  _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,
        KC_LCTL,  KC_LGUI, KC_MUTE,                   KC_SPC,                    KC_SPC,            KC_RALT,  KC_RGUI,  KC_RCTL
    ),
    [1] = LAYOUT_all(
        _______,            KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,     KC_9,     KC_0,    KC_DEL,
        _______,            _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______, KC_SCLN,
        _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______, _______,
        _______,  _______,  _______,                   _______,                   _______,           _______,  _______, _______
        ),
    [2] = LAYOUT_all(
        _______,            _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______, _______,
        _______,            _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______, _______,
        _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______, _______,
        _______,  _______,  _______,                   _______,                   _______,           _______,  _______, _______
        ),
    [3] = LAYOUT_all(
        _______,            _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______, _______,
        _______,            _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______, _______,
        _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______, _______,
        _______,  _______,  _______,                   _______,                   _______,           _______,  _______, _______
        )
};


#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =  { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [1] =  { ENCODER_CCW_CW(RGB_SAD, RGB_SAI)  },
    [2] =  { ENCODER_CCW_CW(RGB_SPD, RGB_SPI)  },
    [3] =  { ENCODER_CCW_CW(KC_RIGHT, KC_LEFT) }
};
#endif
