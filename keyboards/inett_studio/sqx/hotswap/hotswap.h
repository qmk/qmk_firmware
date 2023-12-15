/**
  * @file hotswap.h
  *
    Copyright 2020 astro <yuleiz@gmail.com>

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
#pragma once

#include "quantum.h"

#if defined(RGB_MATRIX_DISABLE_KEYCODES)
#    ifndef RGB_MATRIX_TOGGLE
#        define RGB_MATRIX_TOGGLE   KC_F16
#    endif
#    ifndef RGB_MATRIX_STEP
#        define RGB_MATRIX_STEP     KC_F17
#    endif
#    ifndef RGB_MATRIX_INC_HUE
#        define RGB_MATRIX_INC_HUE  KC_F18
#    endif
#    ifndef RGB_MATRIX_DEC_HUE
#        define RGB_MATRIX_DEC_HUE  KC_F19
#    endif
#    ifndef RGB_MATRIX_INC_SAT
#        define RGB_MATRIX_INC_SAT  KC_F20
#    endif
#    ifndef RGB_MATRIX_DEC_SAT
#        define RGB_MATRIX_DEC_SAT  KC_F21
#    endif
#    ifndef RGB_MATRIX_INC_VAL
#        define RGB_MATRIX_INC_VAL  KC_F22
#    endif
#    ifndef RGB_MATRIX_DEC_VAL
#        define RGB_MATRIX_DEC_VAL  KC_F23
#    endif
#endif
