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

#define _BL  0   // base layer
#define _FN1 1  // function layer 1
#define _FN2 2  // function layer 2
#define _FN3 3  // function layer 3
#define _____ KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   [_BL] = KEYMAP(
     KC_ESC,     KC_Q,       KC_W,       KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSPC,
     KC_TAB,     KC_A,       KC_S,       KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_ENT,
     KC_LSFT,    KC_Z,       KC_X,       KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   MO(_FN2),
     KC_LCTL,    KC_LGUI,    KC_LALT,         _____,         KC_SPC,        _____,                   MO(_FN1), MO(_FN3)
   ),
   [_FN1] = KEYMAP(
     KC_GRAVE,   _____,      KC_UP,      KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_MRWD,  KC_MPLY,  KC_MFFD,  KC_SLCK,  KC_PAUS,  KC_DEL,
     KC_CAPS,    KC_LEFT,    KC_DOWN,    KC_RIGHT, _____,    _____,    _____,    KC_INS,   KC_HOME,  KC_PGUP,  KC_PSCR,
     _____,      _____,      M(0),       M(1),     M(2),     _____,    _____,    KC_END,   KC_PGDN,  _____,    _____,
     _____,      _____,      _____,            _____,        _____,         _____,                   _____,    _____
   ),
   [_FN2] = KEYMAP(
     KC_GRAVE,   KC_1,       KC_2,       KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_DEL,
     KC_CAPS,    _____,      _____,      _____,    _____,    KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_MINS,  KC_EQL,   _____,
     _____,      _____,      _____,      _____,    _____,    _____,    _____,    KC_SCLN,  KC_QUOT,  KC_SLSH,  _____,
     _____,      _____,      _____,            _____,        _____,         _____,                   _____,    _____
   ),
   [_FN3] = KEYMAP(
     KC_F1,      KC_F2,      KC_F3,      KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,
     _____,      M(3),       M(4),       M(5),     _____,    _____,    _____,    _____,    _____,    _____,    _____,
     _____,      M(6),       _____,      _____,    _____,    _____,    _____,    _____,    _____,    _____,    _____,
     _____,      _____,      _____,            _____,        _____,         _____,                   _____,    _____
   )
};
