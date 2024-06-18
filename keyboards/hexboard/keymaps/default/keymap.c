// Copyright 2022-2023 Zach DeCook
// SPDX-License-Identifier: GPL-3.0-only

#include QMK_KEYBOARD_H

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =   {ENCODER_CCW_CW(KC_VOLD, KC_VOLU),},
    [1] =   {ENCODER_CCW_CW(KC_BRID, KC_BRIU),},

};
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_landscape(
               _______,QK_BOOT,RGB_HUI,
          MO(1),    _______,RGB_VAD,RGB_MOD,

      _______,_______,_______,KC_EQL ,_______,_______,KC_PGUP,
          _______,_______,KC_LBRC,KC_RBRC,_______,KC_HOME,KC_END ,
      _______,_______,_______,KC_MINS,_______,_______,KC_PGDN,
          _______,KC_F15 ,_______,_______,KC_F20 ,_______,_______,
      _______,KC_F14 ,KC_F16 ,_______,KC_F19 ,KC_F21 ,_______,
          KC_F13 ,KC_F3  ,KC_F17 ,KC_F18 ,KC_F8  ,KC_F22 ,_______,
      _______,KC_F2  ,KC_F4  ,_______,KC_F7  ,KC_F9  ,KC_F23 ,
          KC_F1  ,KC_3   ,KC_F5  ,KC_F6  ,KC_8   ,KC_F10 ,KC_F24 ,
      _______,KC_2   ,KC_4   ,_______,KC_7   ,KC_9   ,KC_F11 ,
          KC_1   ,KC_E   ,KC_5   ,KC_6   ,KC_I   ,KC_0   ,KC_F12 ,
      KC_TAB ,KC_W   ,KC_R   ,_______,KC_U   ,KC_O   ,KC_BSPC,
          KC_Q   ,KC_D   , KC_T  ,KC_Y   ,KC_K   ,KC_P   ,_______,
      KC_ESC ,KC_S   ,KC_F   ,_______,KC_J   ,KC_L   ,KC_QUOT,
          KC_A   ,KC_C   ,KC_G   ,KC_H   ,KC_COMM,KC_SCLN,KC_SLSH,
      KC_LSFT,KC_X   ,KC_V   ,_______,KC_M   ,KC_DOT ,KC_ENT ,
          KC_Z   ,_______,KC_B   ,KC_N   ,_______,KC_SLSH,_______,
      _______,_______,_______,_______,_______,_______,KC_UP  ,
          KC_LCTL,KC_LGUI,_______,_______,KC_RALT,KC_LEFT,KC_RGHT,
      _______,KC_LALT,MO(1)  ,KC_SPC ,KC_RGUI,KC_RCTL,KC_DOWN
    ),
    [1] = LAYOUT_portrait(
_______,            _______,_______,_______,_______,_______,_______,_______,_______,_______,
                _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
_______,            _______,_______,_______,_______,_______,_______,_______,_______,_______,
                _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
_______,            _______,_______,_______,_______,_______,_______,_______,_______,_______,
                _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
_______,            _______,_______,_______,_______,_______,_______,_______,_______,_______,
                _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
_______,            _______,_______,_______,_______,_______,_______,_______,_______,_______,
                _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
_______,            _______,_______,_______,_______,_______,_______,_______,_______,_______,
                KC_Q   ,KC_W   ,KC_E   ,KC_R   ,KC_T   ,KC_Y   ,KC_U   ,KC_I   ,KC_O   ,KC_P   ,
_______,            KC_A   ,KC_S   ,KC_D   ,KC_F   ,KC_G   ,KC_H   ,KC_J   ,KC_K   ,KC_L   ,
          SFT_T(KC_SPC),KC_Z   ,KC_X   ,KC_C   ,KC_V   ,KC_B   ,KC_B   ,KC_N   ,KC_M   ,RCTL_T(KC_COMM)
    ),
};
