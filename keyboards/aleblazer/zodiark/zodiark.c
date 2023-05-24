/*
Copyright 2021 Spencer Deven <splitlogicdesign@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "zodiark.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
// Key Matrix to LED Index
  // Left Hand
  { 5, 4, 3, 2, 1, 0, 12 },
  { 6, 7, 8, 9, 10, 11, 13 },
  { 19, 18, 17, 16, 15, 14, 26 },
  { 20, 21, 22, 23, 24, 25, NO_LED },
  { 33, 32, 31, 30, 29, 28, 27},
  // Right Hand
  { 39, 38, 37, 36, 35, 34, 46 },
  { 40, 41, 42, 43, 44, 45, 47 },
  { 53, 52, 51, 50, 49, 48, 60 },
  { 54, 55, 56, 57, 58, 59, NO_LED },
  { 67, 66, 65, 64, 63, 62, 61 },

  
}, {
  // LED Index to Physical Position
  // Left Hand
  { 93,  0 }, { 74,  0 }, { 56,  0 }, { 37,  0 }, { 19,  0 }, { 0,  0 }, { 0,  16 },
  { 19,  16 }, { 37,  16 }, { 56,  16 }, { 74,  16 }, { 93,  16 }, { 112,  24 }, { 112,  40 },
  { 93,  32 }, { 74,  32 }, { 56,  32 }, { 37,  32 }, { 19,  32 }, { 0,  32 }, { 0,  48 },
  { 19,  48 }, { 37,  48 }, { 56,  48 }, { 74,  48 }, { 93,  48 }, { 112,  52 },
  { 112,  64 }, { 93,  64 }, { 74,  64 }, { 56,  64 }, { 37,  64 }, { 19,  64 }, { 0,  64 },
  // Right Hand
  { 132,  0 }, { 150,  0 }, { 169,  0 }, { 187,  0 }, { 206,  0 }, { 224,  0 }, { 224,  16 },
  { 206,  16 }, { 187,  16 }, { 169,  16 }, { 150,  16 }, { 132,  16 }, { 113,  24 }, { 113,  40 },
  { 132,  32 }, { 150,  32 }, { 169,  32 }, { 187,  32 }, { 206,  32 }, { 224,  32 }, { 224,  48 },
  { 206,  48 }, { 187,  48 }, { 169,  48 }, { 150,  48 }, { 132,  48 }, { 113,  52 },
  { 113,  64 }, { 132,  64 }, { 150,  64 }, { 169,  64 }, { 187,  64 }, { 206,  64 }, { 224,  64 },
}, {
  // LED Index to Flag
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
} };
#endif
