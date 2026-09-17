/* Copyright 2018-2021 James Laird-Wah, Islam Sharabash
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
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "raise.h"

// "led_map" is taken from kaleidoscope
// LHK = Left Hand Keys
// LPH = "Leds per hand", which isn't _actually_ the number of leds, but instead
// is just used for indexing
#define LHK 33
#define LPH 72

const uint8_t led_map[RGB_MATRIX_LED_COUNT] = {
  // left side - 32 keys includes LP: key 19 is missing for ANSI layout
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 20, 0xff, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 68, 69,

  // right side - 36 keys includes LP
  0 + LPH, 1 + LPH, 2 + LPH, 3 + LPH, 4 + LPH, 5 + LPH, 6 + LPH, 7 + LPH, 8 + LPH, 9 + LPH, 10 + LPH, 11 + LPH, 12 + LPH, 13 + LPH, 14 + LPH, 15 + LPH, 16 + LPH, 17 + LPH, 18 + LPH, 19 + LPH,
  20 + LPH, 21 + LPH, 22 + LPH, 23 + LPH, 24 + LPH, 25 + LPH, 26 + LPH, 27 + LPH, 28 + LPH, 29 + LPH, 30 + LPH, 31 + LPH, 32 + LPH, 33 + LPH, 68 + LPH, 69 + LPH,

  // left under glow - 30
  34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,

  // right underglow - 32
  34 + LPH, 35 + LPH, 36 + LPH, 37 + LPH, 38 + LPH, 39 + LPH, 40 + LPH, 41 + LPH, 42 + LPH, 43 + LPH, 44 + LPH, 45 + LPH, 46 + LPH, 47 + LPH, 48 + LPH, 49 + LPH, 50 + LPH, 51 + LPH,
  52 + LPH, 53 + LPH, 54 + LPH, 55 + LPH, 56 + LPH, 57 + LPH, 58 + LPH, 59 + LPH, 60 + LPH, 61 + LPH, 62 + LPH, 63 + LPH, 64 + LPH, 65 + LPH, 0xff
};
