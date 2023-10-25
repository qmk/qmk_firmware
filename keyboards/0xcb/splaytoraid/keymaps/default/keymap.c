// Copyright 2023 Conor Burns (@Conor-Burns)
/* SPDX-License-Identifier: GPL-2.0-or-later */

#include QMK_KEYBOARD_H

enum layer_names {
    _BASE,
    _LOWER,
    _RAISE,
    _ADJUST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_40(
    KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,               KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSPC,
    KC_LCTL,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,               KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
              KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,               KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,
                                  KC_LSFT,  KC_ESC,   KC_ENT,  KC_MPLY,   KC_SPC,   KC_DEL,    KC_RSFT
  ),

  [_LOWER] = LAYOUT_40(
    _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,
              _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,  _______,
                                  _______,  _______,  _______,  _______,  _______,  _______,  _______
  ),

  [_RAISE] = LAYOUT_40(
    _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,
              _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,  _______,
                                  _______,  _______,  _______,  _______,  _______,  _______,  _______
  ),

  [_ADJUST] = LAYOUT_40(
    _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,
              _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,  _______,
                                  _______,  _______,  _______,  _______,  _______,  _______,  _______
  )
};


const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_LOWER] =  { ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
    [_RAISE] =  { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
    [_ADJUST] = { ENCODER_CCW_CW(KC_RGHT, KC_LEFT) }
};
