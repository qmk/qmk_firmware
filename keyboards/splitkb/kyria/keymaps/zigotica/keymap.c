/* Copyright 2020 Sergi Meseguer <zigotica@gmail.com>

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
      _______,    _STENAI_L1,                                         _STENAI_R1,      _______,
      _______,    _STENAI_L2,                                         _STENAI_R2,      _______,
      _______,    _STENAI_L3, _______, _______,   _______, _______,   _STENAI_R3,      _______,
         _______, _______, _STENAI_LT, _______,   _______, _STENAI_RT, _______, _______
    ),

    [_NUM] = LAYOUT_wrapper(
      _______,    ____NUM_L1,                                         ____NUM_R1,      _______,
      _______,    ____NUM_L2,                                         ____NUM_R2,      _______,
      _______,    ____NUM_L3, _______, _______,   _______, _______,   ____NUM_R3,      _______,
         _______, _______, ____NUM_LT, _______,   _______, ____NUM_RT, _______, _______
    ),

    [_NAV] = LAYOUT_wrapper(
      _______,    ____NAV_L1,                                         ____NAV_R1,      _______,
      _______,    ____NAV_L2,                                         ____NAV_R2,      _______,
      _______,    ____NAV_L3, _______, _______,   _______, _______,   ____NAV_R3,      _______,
         _______, _______, ____NAV_LT, _______,   _______, ____NAV_RT, _______, _______
    ),

    [_SYM] = LAYOUT_wrapper(
      _______,    ____SYM_L1,                                         ____SYM_R1,      _______,
      _______,    ____SYM_L2,                                         ____SYM_R2,      _______,
      _______,    ____SYM_L3, _______, _______,   _______, _______,   ____SYM_R3,      _______,
         _______, _______, ____SYM_LT, _______,   _______, ____SYM_RT, _______, _______
    ),

    [_FN] = LAYOUT_wrapper(
      _______,    ____FN_L1,                                         ____FN_R1,      _______,
      _______,    ____FN_L2,                                         ____FN_R2,      _______,
      _______,    ____FN_L3, _______, _______,   _______, _______,   ____FN_R3,      _______,
         _______, _______, ____FN_LT, _______,   _______, ____FN_RT, _______, _______
    ),
};

