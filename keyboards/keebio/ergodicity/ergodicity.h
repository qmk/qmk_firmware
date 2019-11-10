/* Copyright 2019 Keebio
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
 */
#pragma once

#include "quantum.h"

/* This a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT( \
    kA1, kA2, kA3, kE3, kA4, kA5, kA6, kA7, kA8, kA9,  kA10, kA11, kA12, kA13, kA15, \
    kB1, kB2, kB3, kB4, kB5, kB6, kB7, kB8, kB9, kB10, kB11, kB12, kB13, kB14, kB15, \
    kC1, kC2, kC3, kC4, kC5, kC6, kC7, kC8, kC9, kC10, kC11, kC12, kC13,       kC15, \
         kD2, kD3, kD4, kD5, kD6, kD7, kD8, kD9, kD10, kD11, kD12, kD13, kD14, kD15, \
         kE2,      kE4,      kE6, kE7,      kE9,       kE11,                   kE15 \
) \
{ \
    { kA1, kA2, kA3, kA4, kA5, kA6, kA7, kA8, kA9, kA10, kA11, kA12, kA13, KC_NO, kA15 }, \
    { kB1, kB2, kB3, kB4, kB5, kB6, kB7, kB8, kB9, kB10, kB11, kB12, kB13, kB14, kB15 }, \
    { kC1, kC2, kC3, kC4, kC5, kC6, kC7, kC8, kC9, kC10, kC11, kC12, kC13, KC_NO, kC15 }, \
    { KC_NO, kD2, kD3, kD4, kD5, kD6, kD7, kD8, kD9, kD10, kD11, kD12, kD13, kD14, kD15 }, \
    { KC_NO, kE2, kE3, kE4, KC_NO, kE6, kE7, KC_NO, kE9, KC_NO, kE11, KC_NO, KC_NO, kE15 } \
}
