/* Copyright 2023 Sergi Meseguer <zigotica@gmail.com>

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

#include "zigotica.h"

#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_wrapper(
       KC_ESC,    ____NUM15,     _BLANK_3,    ____NUM60,     KC_DEL, 
       KC_TAB,    _STENAI_L1,    _BLANK_3,    _STENAI_R1,    _______,
       KC_EQL,    _STENAI_L2,    _BLANK_3,    _STENAI_R2,    KC_ENT,
       KC_LSFT,   _STENAI_L3,    ____TARRS,   _STENAI_R3,    KC_RSFT,
       ____LORTH, _STENAI_LT,    ____BARRS,   _STENAI_RT,    ____RORTH
    ),

    [_NUM] = LAYOUT_wrapper(
      QK_MAKE,    _BLANK_ROW,    _BLANK_3,    _BLANK_ROW,    _______,
      _______,    ____NUM_L1,    _BLANK_3,    ____NUM_R1,    _______,
      _______,    ____NUM_L2,    _BLANK_3,    ____NUM_R2,    _______,
      _______,    ____NUM_L3,    _BLANK_3,    ____NUM_R3,    _______,
      _BLANK_4,   ____NUM_LT,    _BLANK_3,    ____NUM_RT,    _BLANK_4
    ),

    [_NAV] = LAYOUT_wrapper(
      QK_MAKE,    _BLANK_ROW,    _BLANK_3,    _BLANK_ROW,    _______,
      _______,    ____NAV_L1,    _BLANK_3,    ____NAV_R1,    _______,
      _______,    ____NAV_L2,    _BLANK_3,    ____NAV_R2,    _______,
      _______,    ____NAV_L3,    _BLANK_3,    ____NAV_R3,    _______,
      _BLANK_4,   ____NAV_LT,    _BLANK_3,    ____NAV_RT,    _BLANK_4
    ),

    [_SYM] = LAYOUT_wrapper(
      QK_MAKE,    _BLANK_ROW,    _BLANK_3,    _BLANK_ROW,    _______,
      _______,    ____SYM_L1,    _BLANK_3,    ____SYM_R1,    _______,
      _______,    ____SYM_L2,    _BLANK_3,    ____SYM_R2,    _______,
      _______,    ____SYM_L3,    _BLANK_3,    ____SYM_R3,    _______,
      _BLANK_4,   ____SYM_LT,    _BLANK_3,    ____SYM_RT,    _BLANK_4
    ),

    [_FN] = LAYOUT_wrapper(
      QK_MAKE,    ____FN_15,     _BLANK_3,    ____FN_60,     _______,
      _______,    ____FN_L1,     _BLANK_3,    ____FN_R1,     _______,
      _______,    ____FN_L2,     _BLANK_3,    ____FN_R2,     _______,
      _______,    ____FN_L3,     _BLANK_3,    ____FN_R3,     _______,
      _BLANK_4,   ____FN_LT,     _BLANK_3,    ____FN_RT,     _BLANK_4
    ),
};


