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
#include "ALysaght.h"
//#include "muse.h"

#define LAYOUT_preonic_wrapper(...) LAYOUT_preonic_grid(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// Qwerty
[_QWERTY] = LAYOUT_preonic_wrapper(
  _________________ALPHA_LN__________________,   XXXXXXX, XXXXXXX,   _________________ALPHA_RN__________________,
  _________________QWERTY_L1_________________,   XXXXXXX, XXXXXXX,   _________________QWERTY_R1_________________,
  _________________QWERTY_L2_________________,   XXXXXXX, XXXXXXX,   _________________QWERTY_R2_________________,
  _________________QWERTY_L3_________________,   XXXXXXX, XXXXXXX,   _________________QWERTY_R3_________________,
  _________________ALPHA_LT__________________,   XXXXXXX, XXXXXXX,   _________________ALPHA_RT__________________
),

// Workman
[_WORKMAN] = LAYOUT_preonic_wrapper(
  _________________ALPHA_LN__________________,   XXXXXXX, XXXXXXX,   _________________ALPHA_RN__________________,
  _________________WORKMAN_L1________________,   XXXXXXX, XXXXXXX,   _________________WORKMAN_R1________________,
  _________________WORKMAN_L2________________,   XXXXXXX, XXXXXXX,   _________________WORKMAN_R2________________,
  _________________WORKMAN_L3________________,   XXXXXXX, XXXXXXX,   _________________WORKMAN_R3________________,
  _________________ALPHA_LT__________________,   XXXXXXX, XXXXXXX,   _________________ALPHA_RT__________________
),

// Final Fantasy XIV
[_FFXIV] = LAYOUT_preonic_wrapper(
  _________________FFXIV_L0__________________, XXXXXXX, XXXXXXX,   _________________FFXIV_R0__________________,
  _________________FFXIV_L1__________________, XXXXXXX, XXXXXXX,   _________________FFXIV_R1__________________,
  _________________FFXIV_L2__________________, XXXXXXX, XXXXXXX,   _________________FFXIV_R2__________________,
  _________________FFXIV_L3__________________, XXXXXXX, XXXXXXX,   _________________FFXIV_R3__________________,
  _________________FFXIV_LT__________________, XXXXXXX, XXXXXXX,   _________________FFXIV_RT__________________
),

// Navigation layer
[_NAVR] = LAYOUT_preonic_wrapper(
  _________________BLANK_5___________________, XXXXXXX, XXXXXXX, _________________BLANK_5___________________,
  _________________NAV_L1____________________, XXXXXXX, XXXXXXX, _________________NAV_R1____________________,
  _________________NAV_L2____________________, XXXXXXX, XXXXXXX, _________________NAV_R2____________________,
  _________________NAV_L3____________________, XXXXXXX, XXXXXXX, _________________NAV_R3____________________,
  _________________NAV_LT____________________, XXXXXXX, XXXXXXX, _________________NAV_RT____________________
),

// Number and Symbol layer
[_NSL] = LAYOUT_preonic_wrapper(
  _________________BLANK_5___________________, XXXXXXX, XXXXXXX, _________________BLANK_5___________________,
  _________________NSL_L1____________________, XXXXXXX, XXXXXXX, _________________NSL_R1____________________,
  _________________NSL_L2____________________, XXXXXXX, XXXXXXX, _________________NSL_R2____________________,
  _________________NSL_L3____________________, XXXXXXX, XXXXXXX, _________________NSL_R3____________________,
  _________________NSL_LT____________________, XXXXXXX, XXXXXXX, _________________NSL_RT____________________
),

// SHIFTED Number and Symbol layer
[_NSSL] = LAYOUT_preonic_wrapper(
  _________________BLANK_5___________________, XXXXXXX, XXXXXXX, _________________BLANK_5___________________,
  _________________NSSL_L1___________________, XXXXXXX, XXXXXXX, _________________NSSL_R1___________________,
  _________________NSSL_L2___________________, XXXXXXX, XXXXXXX, _________________NSSL_R2___________________,
  _________________NSSL_L3___________________, XXXXXXX, XXXXXXX, _________________NSSL_R3___________________,
  _________________NSSL_LT___________________, XXXXXXX, XXXXXXX, _________________NSSL_RT___________________
),

// MOUSE layer
[_MOUSE] = LAYOUT_preonic_wrapper(
  _________________BLANK_5___________________, XXXXXXX, XXXXXXX, _________________BLANK_5___________________,
  _________________MOUSE_L1__________________, XXXXXXX, XXXXXXX, _________________MOUSE_R1__________________,
  _________________MOUSE_L2__________________, XXXXXXX, XXXXXXX, _________________MOUSE_R2__________________,
  _________________MOUSE_L3__________________, XXXXXXX, XXXXXXX, _________________MOUSE_R3__________________,
  _________________MOUSE_LT__________________, XXXXXXX, XXXXXXX, _________________MOUSE_RT__________________
),

// MEDIA layer
[_MEDIA] = LAYOUT_preonic_wrapper(
  _________________BLANK_5___________________, XXXXXXX, XXXXXXX, _________________BLANK_5___________________,
  _________________MEDIA_L1__________________, XXXXXXX, XXXXXXX, _________________MEDIA_R1__________________,
  _________________MEDIA_L2__________________, XXXXXXX, XXXXXXX, _________________MEDIA_R2__________________,
  _________________MEDIA_L3__________________, XXXXXXX, XXXXXXX, _________________MEDIA_R3__________________,
  _________________MEDIA_LT__________________, XXXXXXX, XXXXXXX, _________________MEDIA_RT__________________
),

// FUNCTION layer
[_FUNL] = LAYOUT_preonic_wrapper(
  _________________BLANK_5___________________,   XXXXXXX, XXXXXXX,   _________________BLANK_5___________________,
  _________________FUNC_L1___________________,   XXXXXXX, XXXXXXX,   _________________FUNC_R1___________________,
  _________________FUNC_L2___________________,   XXXXXXX, XXXXXXX,   _________________FUNC_R2___________________,
  _________________FUNC_L3___________________,   XXXXXXX, XXXXXXX,   _________________FUNC_R3___________________,
  _________________FUNC_LT___________________,   XXXXXXX, XXXXXXX,   _________________FUNC_RT___________________
),

// Adjust (_MOUSE + _MEDIA)
[_ADJUST] = LAYOUT_preonic_wrapper(
  _________________BLANK_5___________________,   XXXXXXX, XXXXXXX,   _________________BLANK_5___________________,
  _________________DRAGO_L1__________________,   XXXXXXX, XXXXXXX,   _________________DRAGO_R1__________________,
  _________________DRAGO_L2__________________,   XXXXXXX, XXXXXXX,   FFXIV,   QWERTY,  WORKMAN, XXXXXXX, XXXXXXX,
  _________________DRAGO_L3__________________,   XXXXXXX, XXXXXXX,   _________________DRAGO_R3__________________,
  _________________DRAGO_LT__________________,   XXXXXXX, XXXXXXX,   _________________DRAGO_RT__________________
)


};
