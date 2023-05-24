/* Copyright 2021 stevendlander
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
 * The first section contains "names" for physical keys of the keyboard
 * and defines their position on the board.
 * The second section defines position of the keys on the switch matrix 
 * (where COLUMNS and ROWS crosses). */

#define LAYOUT( \
    K5A,      K5B, K5C, K5D, K5E,  K5F, K5G, K5H, K5I,  K5J, K5K, K5L, K5M,      K5N, K5O, K5P, \
    \
    K4A, K4B, K4C, K4D, K4E, K4F, K4G, K4H, K4I, K4J, K4K, K4L, K4M, K4N, K4O,   K4P, K4Q, K4R, \
    K3A, K3B, K3C, K3D, K3E, K3F, K3G, K3H, K3I, K3J, K3K, K3L, K3M, K3N,        K3O, K3P, K3Q, \
    K2A, K2B, K2C, K2D, K2E, K2F, K2G, K2H, K2I, K2J, K2K, K2L,      K2M, K2N,                  \
    K1A, K1B, K1C, K1D, K1E, K1F, K1G, K1H, K1I, K1J, K1K, K1L, K1M, K1N,             K1O,      \
    K0A, K0B, K0C,                K0D,                K0E, K0F, K0G, K0H,        K0I, K0J, K0K  \
) \
{ \
/* 00 */ { K4A,   K5A,   K4F,   K1M,   K5C,   K5D,   K5E,   K3K,   KC_NO, KC_NO, KC_NO, KC_NO, K0C,   K2N,   KC_NO, KC_NO }, \
/* 01 */ { K2A,   K1B,   K3B,   KC_NO, KC_NO, KC_NO, KC_NO, K4G,   K5F,   KC_NO, KC_NO, KC_NO, KC_NO, K2M,   K0H,   K1N,  }, \
/* 02 */ { K2C,   K2D,   K5B,   K2E,   K2F,   K1C,   K1E,   KC_NO, K1D,   K1F,   K1G,   K2B,   K3A,   KC_NO, KC_NO, KC_NO }, \
/* 03 */ { KC_NO, KC_NO, K4B,   KC_NO, KC_NO, KC_NO, KC_NO, K3G,   K5G,   KC_NO, KC_NO, K0B,   KC_NO, KC_NO, KC_NO, KC_NO }, \
/* 04 */ { KC_NO, KC_NO, K4E,   KC_NO, KC_NO, KC_NO, KC_NO, K3J,   K5H,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K0A,   K1A,  }, \
/* 05 */ { KC_NO, KC_NO, K3C,   KC_NO, KC_NO, KC_NO, KC_NO, K4H,   K5I,   K3L,   K0F,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
/* 06 */ { KC_NO, KC_NO, K4C,   KC_NO, KC_NO, KC_NO, KC_NO, K3H,   K5J,   K4M,   K5K,   K5L,   K4L,   K5N,   KC_NO, KC_NO }, \
/* 07 */ { KC_NO, KC_NO, K4D,   KC_NO, KC_NO, KC_NO, KC_NO, K3I,   KC_NO, KC_NO, KC_NO, K5M,   K4N,   K5O,   KC_NO, KC_NO }, \
/* 08 */ { KC_NO, KC_NO, K3F,   KC_NO, KC_NO, KC_NO, KC_NO, K4K,   KC_NO, K4O,   K1O,   K3P,   K4P,   KC_NO, KC_NO, KC_NO }, \
/* 09 */ { KC_NO, KC_NO, K3E,   K0E,   K0I,   KC_NO, KC_NO, K4J,   KC_NO, K3N,   KC_NO, KC_NO, KC_NO, K4Q,   KC_NO, KC_NO }, \
/* 0A */ { K0D,   KC_NO, K3D,   KC_NO, K0G,   KC_NO, KC_NO, K4I,   KC_NO, K3M,   K0K,   K0J,   K4R,   K3Q,   KC_NO, KC_NO }, \
/* 0B */ { K1I,   K1J,   KC_NO, K1K,   K1L,   K2G,   K2I,   KC_NO, K2H,   K2J,   K2K,   K1H,   K2L,   K3O,   KC_NO, K5P,  }, \
}
/*         0      1      2      3      4      5      6      7      8      9      A      B      C      D      E      F       */
