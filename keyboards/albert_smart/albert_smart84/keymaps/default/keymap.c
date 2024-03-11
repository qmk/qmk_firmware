/* Copyright 2024 albert-zheng
  * 
  * This program is free software: you can redistribute it and/or modify 
  * it under the terms of the GNU General Public License as published by 
  * the Free Software Foundation, either version 2 of the License, or 
  * (at your option) any later version. 
  * 
  * This program is distributed in the hope that it will be useful, 
  * but WITHOUT ANY WARRANTY; without even the implied warranty of 
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
  * GNU General Public License for more details. 
  * 
  * You should have received a copy of the GNU General Public License 
  * along with this program.  If not, see <http://www.gnu.org/licenses/>. 
  */ 


#include QMK_KEYBOARD_H


#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] =  { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [1] =  { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
	[2] =  { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [3] =  { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  }
};
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


	[0] = LAYOUT(
		KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SCRL, KC_PAUS,KC_MUTE,
		KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_HOME,
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,
		KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  KC_PGUP,
		KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_PGDN,
		KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                    KC_RALT, MO(1),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RIGHT,
        _______
	),
	[1] = LAYOUT(
      	_______,   KC_MSEL,   KC_VOLD,    KC_VOLU,   KC_MUTE,   KC_MSTP,    KC_MPRV,   KC_MPLY,   KC_MNXT,   KC_MAIL,   KC_WHOM,  KC_MYCM, KC_CALC,   _______,   _______,  _______, _______,
		_______,   _______,   _______,    _______,   _______,   _______,    _______,   _______,   _______,   _______,   _______,   _______,  _______,  _______,  KC_INS,
		_______,   _______,   _______,    _______,   _______,   _______,    _______,   _______,   _______,   _______,   _______,   _______,  _______,  _______,  KC_END,
		_______,   _______,   _______,    _______,   _______,   _______,    _______,   _______,   _______,   _______,   _______,   _______,  _______,  KC_PSCR,
		_______,   _______,   _______,    _______,   _______,   _______,    _______,   _______,   _______,   _______,   _______,   _______,  _______,  KC_SCRL,
		_______,   GU_TOG,   _______,                          KC_RESET,                                    _______,   _______,   _______,   _______,  _______,   _______,
        _______
	),

	[2] = LAYOUT(
		KC_ESC,  KC_BRID,   KC_BRIU,   RCTL(KC_UP),   KC_F11,   KC_F5,   KC_F6,   KC_MPRV,   KC_MPLY,   KC_MNXT,   KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_PSCR, KC_SCRL, KC_PAUS,KC_MUTE,
		KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_HOME,
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,
		KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  KC_PGUP,
		KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_PGDN,
		KC_LCTL, KC_LALT, KC_LGUI,                            KC_SPC,                    KC_RGUI, MO(3),   KC_RALT, KC_LEFT, KC_DOWN, KC_RIGHT,
        _______
	),
	[3] = LAYOUT(
      	_______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,   _______,  _______,_______,
		_______,   _______,   _______,    _______,   _______,   _______,    _______,   _______,   _______,   _______,   _______,   _______,  _______,  _______,  KC_INS,
		_______,   _______,   _______,    _______,   _______,   _______,    _______,   _______,   _______,   _______,   _______,   _______,  _______,  _______,  KC_END,
		_______,   _______,   _______,    _______,   _______,   _______,    _______,   _______,   _______,   _______,   _______,   _______,  _______,  KC_PSCR,
		_______,   _______,   _______,    _______,   _______,   _______,    _______,   _______,   _______,   _______,   _______,   _______,  _______,  KC_SCRL,
		_______,   _______,   _______,                          KC_RESET,                                    _______,   _______,   _______,   _______,  _______,   _______,
        _______
	)
};



