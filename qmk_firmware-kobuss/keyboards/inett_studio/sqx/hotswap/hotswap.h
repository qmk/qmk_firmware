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

// This a shortcut to help you visually see your layout.
// The first section contains all of the arguements
// The second converts the arguments into a two-dimensional array
#define LAYOUT_60_tsangan_hhkb( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1e, \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2e, \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, \
    k40,      k42, k43,                k47,                k49, k4a, k4b       \
) \
{ \
    {k00,   k01, k02,   k03,   k04,   k05, k06, k08,   k09,   k0a,   k0b, k0c,   k0d, k0e}, \
    {k10,   k11, k12,   k13,   k14,   k15, k16, k17,   k18,   k19,   k1a, k1b,   k1c, k1e}, \
    {k20,   k22, k23,   k24,   k25,   k26, k27, k28,   k29,   k2a,   k2b, k2c, KC_NO, k2e}, \
    {k30, KC_NO, k32,   k33,   k34,   k35, k36, k37,   k38,   k39,   k3a, k3b,   k3c, k3d}, \
    {k40,   k42, k43, KC_NO, KC_NO, KC_NO, k47, k07, KC_NO, KC_NO, KC_NO, k49,   k4a, k4b}  \
}

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
