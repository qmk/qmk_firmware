/* Copyright 2021 TW59420 <https://github.com/TW59420>
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

#include "id42.h"

#define __ NO_LED

#ifdef RGB_MATRIX_ENABLE

led_config_t g_led_config = { {
    // Key Matrix to LED Index
    // WS2812 LED strings are addressed from 0 (1st) to DRIVER_LED_TOTAL-1 (last)
    { 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30 },
    { 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, __, 19 },
    { 18, 17, 16, 15, 14, 13, 12, 11, 10, __, 9,  8  },
    { 7,  6,  5,  4,  __, __, 3,  __, __, 2,  1,  0  }

}, {
    // LED Index to Physical Position
    // This part corresponds to the physical matrix position of the LED string, written in order
    {211, 64}, {193, 64}, {175, 64}, {157, 64}, {139, 64}, {121, 64}, {103, 64}, {85, 64}, {67, 64}, {49, 64}, {31, 64}, {13, 64},
    {208, 43}, {188, 43}, {170, 43}, {153, 43}, {134, 43}, {116, 43}, {98, 43},  {80, 43}, {62, 43}, {44, 43}, {13, 43},
    {205, 21}, {180, 21}, {162, 21}, {144, 21}, {126, 21}, {108, 21}, {90, 21},  {72, 21}, {51, 21}, {31, 21}, {13, 21},
    {208, 0},  {210, 0},  {196, 0},  {182, 0},  {175, 0},  {49, 0},   {31, 0},   {13, 0},
}, {
    // LED Index to Flag
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1
} };

#endif
