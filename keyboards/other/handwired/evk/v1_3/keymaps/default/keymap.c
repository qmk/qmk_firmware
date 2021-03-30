/* 
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(/* Base Layer (0th Layer) - default Layout */
                 KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_ESC,        TG(1),    KC_PSCR,   KC_INS,   KC_APP,         KC_CAPS,  KC_6,     KC_7,     KC_8,     KC_9,     KC_0,
                 KC_Q,     KC_H,     KC_R,     KC_F,     KC_X,     KC_PGUP,       KC_F1,    KC_F2,     KC_F3,    KC_F4,          KC_PGDN,  KC_QUOT,  KC_Y,     KC_O,     KC_U,     KC_J,
                 KC_L,     KC_S,     KC_N,     KC_T,     KC_D,     KC_LBRC,       KC_F5,    KC_F6,     KC_F7,    KC_F8,          KC_RBRC,  KC_P,     KC_I,     KC_A,     KC_E,     KC_K,
                 KC_Z,     KC_M,     KC_C,     KC_V,     KC_B,                    KC_F9,    KC_F10,    KC_F11,   KC_F12,                   KC_W,     KC_G,     KC_COMM,  KC_DOT,   KC_ENT, 
                 KC_LALT,  KC_MINS,  KC_EQL,   KC_END,   KC_GRV,    KC_LCTL,      KC_HOME,  KC_UP,     KC_END,   KC_PGUP,       KC_RCTL,   KC_BSLS,  KC_TAB,   KC_SCLN,  KC_SLSH,  KC_RALT,
	                       KC_LSFT,  KC_DEL,              KC_SPC,   KC_LGUI,      KC_LEFT,  KC_DOWN,   KC_RGHT,  KC_PGDN,       KC_RGUI,  KC_SPC,              KC_BSPC,  KC_RSFT
				 ),                                                                                                            
    [1] = LAYOUT(/* 1st Layer - Numpad Keys */                                                                                 
                 _______,  _______,  _______,  _______,  _______,  _______,       _______,  KC_SLCK,   KC_PAUS,  _______,        _______,  _______,  _______,  _______,  _______,  _______,
                 _______,  _______,  _______,  _______,  _______,  _______,       _______,  KC_PSLS,   KC_PAST,  KC_PMNS,        _______,  _______,  _______,  _______,  _______,  _______,
                 _______,  _______,  _______,  _______,  _______,  _______,       KC_P7,    KC_P8,     KC_P9,    KC_PPLS,        _______,  _______,  _______,  _______,  _______,  _______,
                 _______,  _______,  _______,  _______,  _______,                 KC_P4,    KC_P5,     KC_P6,    KC_PPLS,                  _______,  _______,  _______,  _______,  _______,
                 _______,  _______,  _______,  _______,  _______,   _______,      KC_P1,    KC_P2,     KC_P3,    KC_PEQL,       _______,   _______,  _______,  _______,  _______,  _______,
                           _______,  _______,             _______,  _______,      KC_P0,    KC_P0,     KC_PDOT,  KC_PENT,       _______,  _______,             _______,  _______
                 )                                                                                                             
};

