/* Copyright 2020 Neil Brian Ramirez
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "keycodes.h"

#ifndef VIA_ENABLE
#    ifndef RGB_MATRIX_TOGGLE
#        define RGB_MATRIX_TOGGLE KC_F15
#    endif
#    ifndef RGB_MATRIX_MODE_INC
#        define RGB_MATRIX_MODE_INC KC_F16
#    endif
#    ifndef RGB_MATRIX_MODE_DEC
#        define RGB_MATRIX_MODE_DEC KC_F17
#    endif
#    ifndef RGB_MATRIX_HUE_INC
#        define RGB_MATRIX_HUE_INC KC_F18
#    endif
#    ifndef RGB_MATRIX_HUE_DEC
#        define RGB_MATRIX_HUE_DEC KC_F19
#    endif
#    ifndef RGB_MATRIX_SAT_INC
#        define RGB_MATRIX_SAT_INC KC_F20
#    endif
#    ifndef RGB_MATRIX_SAT_DEC
#        define RGB_MATRIX_SAT_DEC KC_F21
#    endif
#    ifndef RGB_MATRIX_VAL_INC
#        define RGB_MATRIX_VAL_INC KC_F22
#    endif
#    ifndef RGB_MATRIX_VAL_DEC
#        define RGB_MATRIX_VAL_DEC KC_F23
#    endif
#else
#    ifndef RGB_MATRIX_TOGGLE
#        define RGB_MATRIX_TOGGLE QK_KB_0
#    endif
#    ifndef RGB_MATRIX_MODE_INC
#        define RGB_MATRIX_MODE_INC QK_KB_1
#    endif
#    ifndef RGB_MATRIX_MODE_DEC
#        define RGB_MATRIX_MODE_DEC QK_KB_2
#    endif
#    ifndef RGB_MATRIX_HUE_INC
#        define RGB_MATRIX_HUE_INC QK_KB_3
#    endif
#    ifndef RGB_MATRIX_HUE_DEC
#        define RGB_MATRIX_HUE_DEC QK_KB_4
#    endif
#    ifndef RGB_MATRIX_SAT_INC
#        define RGB_MATRIX_SAT_INC QK_KB_5
#    endif
#    ifndef RGB_MATRIX_SAT_DEC
#        define RGB_MATRIX_SAT_DEC QK_KB_6
#    endif
#    ifndef RGB_MATRIX_VAL_INC
#        define RGB_MATRIX_VAL_INC QK_KB_7
#    endif
#    ifndef RGB_MATRIX_VAL_DEC
#        define RGB_MATRIX_VAL_DEC QK_KB_8
#    endif
#endif

#define R_M_TOG RGB_MATRIX_TOGGLE
#define R_M_MOD RGB_MATRIX_MODE_INC
#define R_M_RMOD RGB_MATRIX_MODE_DEC
#define R_M_HUI RGB_MATRIX_HUE_INC
#define R_M_HUD RGB_MATRIX_HUE_DEC
#define R_M_SAI RGB_MATRIX_SAT_INC
#define R_M_SAD RGB_MATRIX_SAT_DEC
#define R_M_VAI RGB_MATRIX_VAL_INC
#define R_M_VAD RGB_MATRIX_VAL_DEC
