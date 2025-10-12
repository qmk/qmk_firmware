/* Copyright 2021 Harrison Chan (Xelus)
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
  { 24,     NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
  { 25,     NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
  { 26,     27,     NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
  { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
  { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED }
}, {
  // LED Index to Physical Position
    { 224,  0 },
    { 224,  9 },
    { 224, 21 },
    { 224, 33 },
    { 224, 45 },
    { 223, 51 },
    { 206, 52 },
    { 190, 52 },
    { 172, 52 },
    { 154, 57 },
    { 136, 61 },
    { 118, 63 },
    { 101, 64 },
    { 80 , 60 },
    { 64 , 57 },
    { 46 , 53 },
    { 28 , 53 },
    { 10 , 52 },
    { 3  , 51 },
    { 2  , 45 },
    { 2  , 33 },
    { 2  , 20 },
    { 2  ,  9 },
    { 0  ,  0 },
    { 9  ,  3 },
    { 6  , 14 },
    { 4  , 26 },
    { 21 , 27 }

}, {
  // LED Index to Flag
  2, 2, 2, 2, 2, 2, 2, 2,
  2, 2, 2, 2, 2, 2, 2, 2,
  2, 2, 2, 2, 2, 2, 2, 2,
  8, 8, 8, 8
} };

#endif
