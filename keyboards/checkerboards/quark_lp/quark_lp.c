/* Copyright 2021 Nathan Spears
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

#include "quark_lp.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
  // Key Matrix to LED Index
  { 11, 10, 9, 8, 7, NO_LED, 6, NO_LED, 5, NO_LED, 4, 3, 2, 1, 0 },
  { 12, 13, 14, 15, 16, NO_LED, 17, NO_LED, 18, NO_LED, 19, 20, 21, 22, 23 },
  { 35, 34, 33, 32, 31, NO_LED, 30, NO_LED, 29, NO_LED, 28, 27, 26, 25, 24 },
  { 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50 }
}, {
  // LED Index to Physical Position
  { 244, 0 }, { 224, 0 }, { 203, 0 }, { 183, 0 }, { 163, 0 }, { 143, 0 }, { 122, 0 }, { 102, 0 }, { 81, 0 }, { 61, 0 }, { 41, 0 }, { 20, 0 },
  { 20, 21 }, { 41, 21 }, { 61, 21 }, { 81, 21 }, { 102, 21 }, { 122, 21 }, { 143, 21 }, { 163, 21 }, { 183, 21 }, { 203, 21 }, { 224, 21 }, { 244, 21 },
  { 244, 43 }, { 224, 43 }, { 203, 43 }, { 183, 43 }, { 163, 43 }, { 143, 43 }, { 122, 43 }, { 102, 43 }, { 81, 43 }, { 61, 43 }, { 41, 43 }, { 20, 43 },
  { 20, 64 }, { 41, 64 }, { 61, 64 }, { 81, 64 }, { 102, 64 }, { 112, 64 }, { 122, 64 }, { 132, 64 }, { 143, 64 }, { 153, 64 }, { 163, 64 }, { 183, 64 }, { 203, 64 }, { 224, 64 }, { 244, 64 }
}, {
  // LED Index to Flag
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
} };
#endif
