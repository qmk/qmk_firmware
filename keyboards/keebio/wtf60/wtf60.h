/* Copyright 2021 Danny Nguyen <danny@keeb.io>

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

#define LAYOUT_full_wtf( \
    kA1, kA2, kA3, kA4, kA5, kA6, kA7, kA8, kA9, kA10, kA11, kA12, kA13, kA14, kA15, \
    kB1, kB2, kB3, kB4, kB5, kB6, kB7, kB8, kB9, kB10, kB11, kB12, kB13, kB14, \
    kC1, kC2, kC3, kC4, kC5, kC6, kC7, kC8, kC9, kC10, kC11, kC12, kC13, kC14, \
    kD1, kD2, kD3, kD4, kD5, kD6, kD7, kD8, kD9, kD10, kD11, kD12, kD13, kD14, \
    kE1, kE2, kE3, kE4,           kE7,                       kE12, kE13, kE14 \
) \
{ \
    { kA1, kA2, kA3, kA4, kA5, kA6, kA7, kA8, kA9, kA10, kA11, kA12, kA13, kA14 }, \
    { kB1, kB2, kB3, kB4, kB5, kB6, kB7, kB8, kB9, kB10, kB11, kB12, kB13, kB14 }, \
    { kC1, kC2, kC3, kC4, kC5, kC6, kC7, kC8, kC9, kC10, kC11, kC12, kC13, kC14 }, \
    { kD1, kD2, kD3, kD4, kD5, kD6, kD7, kD8, kD9, kD10, kD11, kD12, kD13, kD14 }, \
    { kE1, kE2, kE3, kE4, KC_NO, KC_NO, kE7, KC_NO, KC_NO, KC_NO, kA15, kE12, kE13, kE14 } \
}

#define LAYOUT_60_ansi( \
    kA15, kA14, kA13, kA12, kA11, kA10, kA9, kA8, kA7, kA6, kA5, kA4, kA3, kA1, \
    kB14, kB13, kB12, kB11, kB10, kB9,  kB8, kB7, kB6, kB5, kB4, kB3, kB2, kB1, \
    kC14, kC13, kC12, kC11, kC10, kC9,  kC8, kC7, kC6, kC5, kC4, kC3, kC1, \
    kD14, kD12, kD11, kD10, kD9,  kD8,  kD7, kD6, kD5, kD4, kD3, kD1, \
    kE14, kE13, kE12,             kE7,                      kE4, kE3, kE2, kE1 \
) \
{ \
    { kA1, KC_NO, kA3, kA4, kA5, kA6, kA7, kA8, kA9, kA10, kA11, kA12, kA13, kA14 }, \
    { kB1, kB2, kB3, kB4, kB5, kB6, kB7, kB8, kB9, kB10, kB11, kB12, kB13, kB14 }, \
    { kC1, KC_NO, kC3, kC4, kC5, kC6, kC7, kC8, kC9, kC10, kC11, kC12, kC13, kC14 }, \
    { kD1, KC_NO, kD3, kD4, kD5, kD6, kD7, kD8, kD9, kD10, kD11, kD12, KC_NO, kD14 }, \
    { kE1, kE2, kE3, kE4, KC_NO, KC_NO, kE7, KC_NO, KC_NO, KC_NO, kA15, kE12, kE13, kE14 } \
}
