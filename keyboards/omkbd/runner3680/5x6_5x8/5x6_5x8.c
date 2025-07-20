/* Copyright 2021 omkbd
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

#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
  // Key Matrix to LED Index
  { NO_LED, NO_LED, 5, 4, 3, 2, 1, 0 },
  { NO_LED, NO_LED, 6, 7, 8, 9, 10, 11 },
  { NO_LED, NO_LED, 17, 16, 15, 14, 13, 12 },
  { NO_LED, NO_LED, 18, 19, 20, 21, 22, 23 },
  { NO_LED, NO_LED, 29, 28, 27, 26, 25, 24 },
  { 37, 36, 35, 34, 33, 32, 31, 30 },
  { 38, 39, 40, 41, 42, 43, 44, 45 },
  { 53, 52, 51, 50, 49, 48, 47, 46 },
  { 54, 55, 56, 57, 58, 59, 60, 61 },
  { 69, 68, 67, 66, 65, 64, 63, 62 }
}, {
  // LED Index to Physical Position
  { 86, 0 }, { 69, 0 }, { 52, 0 }, { 34, 0 }, { 17, 0 }, { 0, 0 },
  { 0, 16 }, { 17, 16 }, { 34, 16 }, { 52, 16 }, { 69, 16 }, { 86, 16 },
  { 86, 32 }, { 69, 32 }, { 52, 32 }, { 34, 32 }, { 17, 32 }, { 0, 32 },
  { 0, 48 }, { 17, 48 }, { 34, 48 }, { 52, 48 }, { 69, 48 }, { 86, 48 },
  { 86, 64 }, { 69, 64 }, { 52, 64 }, { 34, 64 }, { 17, 64 }, { 0, 64 },
  { 103, 0 }, { 121, 0 }, { 138, 0 }, { 155, 0 }, { 172, 0 }, { 190, 0 }, { 207, 0 }, { 224, 0 },
  { 224, 16 }, { 207, 16 }, { 190, 16 }, { 172, 16 }, { 155, 16 }, { 138, 16 }, { 121, 16 }, { 103, 16 },
  { 103, 32 }, { 121, 32 }, { 138, 32 }, { 155, 32 }, { 172, 32 }, { 190, 32 }, { 207, 32 }, { 224, 32 },
  { 224, 48 }, { 207, 48 }, { 190, 48 }, { 172, 48 }, { 155, 48 }, { 138, 48 }, { 121, 48 }, { 103, 48 },
  { 103, 64 }, { 121, 64 }, { 138, 64 }, { 155, 64 }, { 172, 64 }, { 190, 64 }, { 207, 64 }, { 224, 64 }
}, {
  // LED Index to Flag
  LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL,
  LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL,
  LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL,
  LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL,
  LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL
} };
#endif
