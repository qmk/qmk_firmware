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
  _LOWER,
  _RAISE,
  _ADJUST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_1x5(
       KC_A  , KC_S  , KC_D  , KC_F  ,KC_SPC ,              KC_SPC , KC_J  , KC_K  , KC_L  ,KC_SCLN
  ),

  [_LOWER] = LAYOUT_split_1x5(
      _______,_______,_______,_______,_______,              _______,_______,_______,_______,_______
  ),

  [_RAISE] = LAYOUT_split_1x5(
      _______,_______,_______,_______,_______,              _______,_______,_______,_______,_______
  ),

  [_ADJUST] = LAYOUT_split_1x5(
      _______,_______,_______,_______,_______,              _______,_______,_______,_______,_______
  )
};
