/*
  Copyright 2018 Eric Gebhart <e.a.gebhart@gmail.com>

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
#include "ericgebhart.h"
#include "layouts.h"

// Point the keymap macros at the proper layouts.
// Base layers 4x10, no numbers, just a 3x10 for the keymap.
// Transient function layers are all 3x10.
// The 4th row and middle 3 buttons remain as base defines it.

#define BASE Rebound_base
#define BEPO Rebound_base_bepo
#define TRANS Rebound_transient

#undef BEPO_ENABLE

#include "map.h"

bool encoder_update_user(uint8_t index, bool clockwise) {
  switch(get_highest_layer(layer_state)){
  case _DVORAK:
    if (clockwise) {
      tap_code16(KC_VOLD);
    } else {
      tap_code16(KC_VOLU);
    }
    break;

  case _NAV:
    if (clockwise) {
      tap_code16(S(KC_TAB));
    } else {
      tap_code16(KC_TAB);
    }
    break;
  }
  return true;
}
