/* Copyright 2015-2017 Jack Humbert
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
 *
 * qmk compile -kb preonic/rev3
 * qmk flash -kb preonic/rev3
 */

#include QMK_KEYBOARD_H
#include "alysaght.h"
//#include "muse.h"

#define LAYOUT_ortho_4x10_wrapper(...) LAYOUT_ortho_4x10(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// Colemak DH
[_COLEMAK] = LAYOUT_ortho_4x10_wrapper(
  _________________COLEMAK_L1________________, _________________COLEMAK_R1________________,
  _________________COLEMAK_L2________________, _________________COLEMAK_R2________________,
  _________________COLEMAK_L3________________, _________________COLEMAK_R3________________,
  _________________ALPHA_LT__________________, _________________ALPHA_RT__________________
),

// Qwerty
[_QWERTY] = LAYOUT_ortho_4x10_wrapper(
  _________________QWERTY_L1_________________, _________________QWERTY_R1_________________,
  _________________QWERTY_L2_________________, _________________QWERTY_R2_________________,
  _________________QWERTY_L3_________________, _________________QWERTY_R3_________________,
  _________________ALPHA_LT__________________, _________________ALPHA_RT__________________
),

// Number and Symbol layer
[_NSL] = LAYOUT_ortho_4x10_wrapper(
  _________________NSL_L1____________________, _________________NSL_R1____________________,
  _________________NSL_L2____________________, _________________NSL_R2____________________,
  _________________NSL_L3____________________, _________________NSL_R3____________________,
  _________________NSL_LT____________________, _________________NSL_RT____________________
),

// SHIFTED Number and Symbol layer
[_NSSL] = LAYOUT_ortho_4x10_wrapper(
  _________________NSSL_L1___________________, _________________NSSL_R1___________________,
  _________________NSSL_L2___________________, _________________NSSL_R2___________________,
  _________________NSSL_L3___________________, _________________NSSL_R3___________________,
  _________________NSSL_LT___________________, _________________NSSL_RT___________________
),

// FUNCTION layer
[_FUNL] = LAYOUT_ortho_4x10_wrapper(
  _________________FUNC_L1___________________, _________________FUNC_R1___________________,
  _________________FUNC_L2___________________, _________________FUNC_R2___________________,
  _________________FUNC_L3___________________, _________________FUNC_R3___________________,
  _________________FUNC_LT___________________, _________________FUNC_RT___________________
),

// Navigation layer
[_NAVR] = LAYOUT_ortho_4x10_wrapper(
  _________________NAV_L1____________________, _________________NAV_R1____________________,
  _________________NAV_L2____________________, _________________NAV_R2____________________,
  _________________NAV_L3____________________, _________________NAV_R3____________________,
  _________________NAV_LT____________________, _________________NAV_RT____________________
),

// MOUSE layer
[_MOUSE] = LAYOUT_ortho_4x10_wrapper(
  _________________MOUSE_L1__________________, _________________MOUSE_R1__________________,
  _________________MOUSE_L2__________________, _________________MOUSE_R2__________________,
  _________________MOUSE_L3__________________, _________________MOUSE_R3__________________,
  _________________MOUSE_LT__________________, _________________MOUSE_RT__________________
),

// MEDIA layer
[_MEDIA] = LAYOUT_ortho_4x10_wrapper(
  _________________MEDIA_L1__________________, _________________MEDIA_R1__________________,
  _________________MEDIA_L2__________________, _________________MEDIA_R2__________________,
  _________________MEDIA_L3__________________, _________________MEDIA_R3__________________,
  _________________MEDIA_LT__________________, _________________MEDIA_RT__________________
),

// Adjust (_MOUSE + _MEDIA)
[_ADJUST] = LAYOUT_ortho_4x10_wrapper(
  _________________DRAGO_L1__________________, _________________DRAGO_R1__________________,
  _________________DRAGO_L2__________________, XXXXXXX, QWERTY,  XXXXXXX, COLEMAK, XXXXXXX,
  _________________DRAGO_L3__________________, _________________DRAGO_R3__________________,
  _________________DRAGO_LT__________________, _________________DRAGO_RT__________________
)


};
