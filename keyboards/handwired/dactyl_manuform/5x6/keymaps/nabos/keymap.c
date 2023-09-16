/*
Copyright 2022 Nabos <nabos at glargh dot fr>

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

enum layer_names {
    _QWERTY,
    _FUNCTIONS,
    _NUMPAD,
    _GAMING
};

#define FUNCTIONS MO(_FUNCTIONS)
#define NUMPAD MO(_NUMPAD)
#define GAMING TG(_GAMING)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_5x6(
     QK_GESC, KC_1 , KC_2  ,  KC_3  , KC_4  , KC_5  ,         KC_6     , KC_7  , KC_8  , KC_9 , KC_0  ,KC_RBRC,
     KC_TAB , KC_Q , KC_W  ,  KC_E  , KC_R  , KC_T  ,         KC_Y     , KC_U  , KC_I  , KC_O , KC_P  ,KC_LBRC,
     KC_PGUP, KC_A , KC_S  ,  KC_D  , KC_F  , KC_G  ,         KC_H     , KC_J  , KC_K  , KC_L ,KC_SCLN,KC_QUOT,
     KC_PGDN, KC_Z , KC_X  ,  KC_C  , KC_V  , KC_B  ,         KC_N     , KC_M  ,KC_COMM,KC_DOT,KC_SLSH,_______,
                    KC_LEFT,KC_RIGHT,                                           KC_DOWN,KC_UP ,
                                     KC_LSFT,KC_SPC ,         KC_ENT   ,KC_BSPC,
                                     KC_LGUI,KC_LALT,         FUNCTIONS,KC_RALT,
                                     KC_DEL ,GAMING ,         NUMPAD   ,KC_RCTL
  ),

  [_FUNCTIONS] = LAYOUT_5x6(
     KC_F12 , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 ,         KC_F6  , KC_F7 , KC_F8 , KC_F9 ,KC_F10 ,KC_F11 ,
     _______,_______,_______,_______,_______,_______,         _______,_______,_______,_______,_______,_______,
     _______,_______,_______,_______,_______,_______,         _______,_______,_______,_______,_______,_______,
     _______,_______,_______,_______,_______,_______,         _______,_______,_______,_______,_______,_______,
                     _______,_______,                                         _______,_______,
                                     _______,_______,         _______,_______,
                                     _______,_______,         _______,_______,
                                     _______,_______,         _______,_______
  ),

  [_NUMPAD] = LAYOUT_5x6(
     _______,_______,_______,_______,_______,_______,         _______,KC_NUM ,_______,_______,KC_MINS,KC_EQL ,
     _______,_______,_______,_______,_______,_______,         _______,KC_KP_7,KC_KP_8,KC_KP_9,_______,_______,
     _______,_______,_______,_______,_______,_______,         _______,KC_KP_4,KC_KP_5,KC_KP_6,_______,_______,
     _______,_______,_______,_______,_______,_______,         _______,KC_KP_1,KC_KP_2,KC_KP_3,_______,KC_PSCR,
                     _______,_______,                                         KC_KP_0,KC_PDOT,
                                     _______,_______,         KC_PENT,_______,
                                     _______,_______,         _______,_______,
                                     _______,_______,         _______,_______
  ),

  [_GAMING] = LAYOUT_5x6(
     _______,_______,_______,_______,_______,_______,         _______,_______,_______,_______,_______,_______,
      KC_T  ,KC_TAB , KC_Q  , KC_W  , KC_E  , KC_R  ,         _______,_______,_______,_______,_______,_______,
      KC_G  ,KC_LSFT, KC_A  , KC_S  , KC_D  , KC_F  ,         _______,_______,_______,_______,_______,_______,
      KC_B  ,KC_LCTL, KC_Z  , KC_X  , KC_C  , KC_V  ,         _______,_______,_______,_______,_______,_______,
                     _______,_______,                                         _______,_______,
                                     _______,_______,         _______,_______,
                                     _______,_______,         _______,_______,
                                     _______,_______,         _______,_______
  )
};

