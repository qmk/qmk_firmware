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

#define _QWERTY 0
#define _NMBR 1
#define _NAV 2
#define _MOUSE 3
#define _FUNCT 4


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   [_QWERTY] = LAYOUT_split_space(
     KC_TAB,     KC_Q,       KC_W,       KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,      KC_P,     KC_BSPC,
     KC_ESC,     KC_A,       KC_S,       KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,      LT(_FUNCT, KC_ENT),
     KC_LSFT,    KC_Z,       KC_X,       KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,    KC_SLSH,
     KC_LCTL,    KC_LGUI,    KC_LALT,         LT(_NAV, KC_SPC),         KC_BSPC,    KC_RALT,             TT(_MOUSE),   TT(_NMBR)
   ),
   [_NAV] = LAYOUT_split_space(
     _______,      _______,    KC_UP,      _______,  KC_LPRN,    KC_RPRN,    _______,   KC_7,     KC_8,     KC_9,         KC_KP_SLASH,    KC_DEL,
     _______,      KC_LEFT,    KC_DOWN,    KC_RIGHT, KC_LCBR,    KC_RCBR,    _______,   KC_4,     KC_5,     KC_6,         KC_KP_ASTERISK,
     _______,      _______,    _______,    _______,  KC_LABK,    KC_RABK,    KC_GRV,    KC_1,     KC_2,     KC_3,         KC_KP_MINUS,
     _______,      _______,    _______,          _______,      _______,       _______,                   KC_KP_DOT,  KC_KP_PLUS
   ),
   [_NMBR] = LAYOUT_split_space(
     KC_GRAVE,   KC_1,       KC_2,       KC_3,    KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINUS,
     _______,    KC_4,       KC_5,       KC_6,    _______,  _______,  _______,  _______,  _______,  _______,  _______,
     _______,    KC_7,       KC_8,       KC_9,    _______,  _______,  _______,  _______,  _______,  _______,  _______,
     _______,    _______,    _______,          _______,        TO(_QWERTY),       _______,                 _______,    _______
   ),
    [_MOUSE] = LAYOUT_split_space(
     _______,   KC_BTN1,      KC_MS_U,     KC_BTN2,  _______,    _______,    _______,    _______,   KC_WH_U,   _______,   _______,     _______,
     _______,   KC_MS_L,      KC_MS_D,     KC_MS_R,  _______,    _______,    _______,    KC_WH_L,   KC_WH_D,   KC_WH_R,   _______,
     _______,   _______,      _______,     _______,  _______,    _______,    _______,    _______,   _______,   _______,   _______,
     _______,   _______,      _______,            _______,        TO(_QWERTY),         _______,                   _______,    _______
   ),
   [_FUNCT] = LAYOUT_split_space(
     KC_F1,        KC_F2,      KC_F3,      KC_F4,    KC_F5,      KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,   KC_F12,
     _______,      KC_INS,     KC_HOME,    KC_PGUP,  _______,    _______,    _______,    _______,    _______,    _______,    _______,
     _______,      KC_DEL,     KC_END,     KC_PGDN,  _______,    _______,    _______,    _______,    _______,    _______,    _______,
     _______,      _______,      _______,            RGB_TOG,        RGB_MOD,         _______,                   _______,    RESET
   )
};
