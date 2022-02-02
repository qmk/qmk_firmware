/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert
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
#include "yfuku_keymaps.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum layer_number {
    _QWERTY = 0,
    _RAISE,
    _LOWER,
    _ADJUST,
};

#define TAPPING_LAYER_TERM 230
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case GS_S:
      return TAPPING_LAYER_TERM;
    case GS_L:
      return TAPPING_LAYER_TERM;
    case A_D:
      return TAPPING_LAYER_TERM;
    case A_K:
      return TAPPING_LAYER_TERM;
    default:
      return TAPPING_TERM;
  }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_wrapper(
       __QWERTY_L1__,                    __QWERTY_R1__,
       __QWERTY_L2__,  KC_BSPC, KC_BSPC, __QWERTY_R2__,
       __QWERTY_L3__,  KC_DEL , KC_DEL , __QWERTY_R3__,
       __QUERTY_T4__
    ),

    [_RAISE] = LAYOUT_wrapper(
       __RAISE_L1__,              __RAISE_R1__,
       __RAISE_L2__,  ____, ____, __RAISE_R2__,
       __RAISE_L3__,  ____, ____, __RAISE_R3__,
       __RAISE_T4__
    ),

    [_LOWER] = LAYOUT_wrapper(
       __LOWER_L1__,              __LOWER_R1__,
       __LOWER_L2__,  ____, ____, __LOWER_R2__,
       __LOWER_L3__,  ____, ____, __LOWER_R3__,
       __LOWER_T4__
    ),
    [_ADJUST] = LAYOUT_wrapper(
       __TRANSx6__,              __TRANSx6__, 
       __TRANSx6__, __TRANSx2__, __TRANSx6__, 
       __TRANSx6__, __TRANSx2__, __TRANSx6__, 
       __TRANSx4__, __TRANSx4__
    ),
};
