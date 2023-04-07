/*
Copyright 2023 Victor Eikman <viktor.eikman@gmail.com>

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

// This uses the same coordinate system as the program that defines
// the case model, but not the same coordinates.
// Numbers increase going to the right and away from the user on the
// right-hand side of the keyboard. This is mirrored for the
// left-hand side.
// The matrix is constructed for ease of soldering, with the columns
// of the thumb cluster extending along the sides of the finger
// cluster so that everything can be contained in a 6x6 pattern.

#define LAYOUT_dmote_62( \
    LA_20, LA_10, LF_35, LF_25, LF_15, LF_05, \
    LF_55, LF_45, LF_34, LF_24, LF_14, LF_04, \
    LF_54, LF_44, LF_33, LF_23, LF_13, LF_03, \
    LF_53, LF_43, LF_32, LF_22, LF_12, \
                         LF_21,        LT_21, LT_22, \
                                    LT_10, LT_11, LT_12, \
                                       LT_01, LT_02, \
\
           RF_05, RF_15, RF_25, RF_35, RA_10, RA_20, \
           RF_04, RF_14, RF_24, RF_34, RF_45, RF_55, \
           RF_03, RF_13, RF_23, RF_33, RF_44, RF_54, \
                  RF_12, RF_22, RF_32, RF_43, RF_53, \
       RT_22, RT_21,     RF_21, \
    RT_12, RT_11, RT_10, \
       RT_02, RT_01 \
) { \
    { LA_20, LA_10, LF_35, LF_25, LF_15, LF_05 }, \
    { LF_55, LF_45, LF_34, LF_24, LF_14, LF_04 }, \
    { LF_54, LF_44, LF_33, LF_23, LF_13, LF_03 }, \
    { LF_53, LF_43, LF_32, LF_22, LF_12, LT_22 }, \
    { KC_NO, KC_NO, LT_21, LF_21, LT_11, LT_12 }, \
    { KC_NO, KC_NO, LT_10, KC_NO, LT_01, LT_02 }, \
\
    { RA_20, RA_10, RF_35, RF_25, RF_15, RF_05 }, \
    { RF_55, RF_45, RF_34, RF_24, RF_14, RF_04 }, \
    { RF_54, RF_44, RF_33, RF_23, RF_13, RF_03 }, \
    { RF_53, RF_43, RF_32, RF_22, RF_12, RT_22 }, \
    { KC_NO, KC_NO, RT_21, RF_21, RT_11, RT_12 }, \
    { KC_NO, KC_NO, RT_10, KC_NO, RT_01, RT_02 } \
}
