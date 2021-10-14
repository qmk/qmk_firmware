/* Copyright 2019 Ryota Goto
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


/*
 *  K702,       K503, K504, K604, K704,    K706, K708, K609, K509,    K506, K406, K411, K412,    K415, K315, K114, \
 *  K502, K402, K403, K404, K405, K505, K507, K407, K408, K409, K410, K510, K508,       K606,    K512, K514, K513, \
 *  K602, K302, K303, K304, K305, K605, K607, K307, K308, K309, K310, K610, K608,       K206,    K511, K414, K413, \
 *  K603, K202, K203, K204, K205, K705, K707, K207, K208, K209, K210, K710,             K106,                      \
 *  K601,       K102, K103, K104, K105, K005, K007, K107, K108, K109, K010,             K101,          K714,       \
 *  K500,       K715,                         K006,                         K015,       K100,    K014, K011, K012  \
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT( /* Base */
    KC_ESC,           KC_F1,   KC_F2,   KC_F3,   KC_F4,       KC_F5,   KC_F6,   KC_F7,   KC_F8,        KC_F9,   KC_F10,  KC_F11,  KC_F12,     KC_PSCR, KC_SLCK, KC_PAUS, 
	KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,           KC_BSPC,    KC_INS,  KC_HOME, KC_PGUP, 
	KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,          KC_BSLS,    KC_DEL,  KC_END,  KC_PGDN, 
	MO(1),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,                   KC_ENT,                                
	KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                   KC_RSFT,             KC_UP,            
	KC_LCTL,          KC_LALT,                                     KC_SPC,                                      KC_RALT,          KC_RCTL,    KC_LEFT, KC_DOWN, KC_RGHT  
  ),
  [1] = LAYOUT( /* FN */
    RESET,            _______, _______, _______, _______,     _______, _______, _______, _______,      _______, _______, _______, _______,    _______, _______, _______, 
	_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,    _______, _______, _______, 
	KC_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,    _______, _______, _______, 
	_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,                               
	_______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,             _______,          
	_______,          _______,                                     _______,                                     _______,          _______,    _______, _______, _______  
  )
};
