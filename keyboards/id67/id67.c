/* Copyright 2021 Tybera
 * Copyright 2021 thewerther
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

#include "id67.h"

led_config_t g_led_config = { {
    // Key Matrix to LED Index
    {66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52},
    {51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37},
    {36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, NO_LED, 24, 23},
    {22, NO_LED, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9},
    {8,  7,  NO_LED,  6,  NO_LED,  NO_LED,  5,  NO_LED,  NO_LED,  NO_LED,  4,  3,  2,  1, 0},
}, {
    // LED Index to Physical Position
    {0, 0},  {16, 0},  {32, 0},  {48, 0},  {64, 0},  {80, 0},  {96, 0},  {112, 0},  {128, 0},  {144, 0},  {160, 0},  {176, 0},  {192, 0},  {208, 0},  {224, 0},
    {0, 16}, {16, 16}, {32, 16}, {48, 16}, {64, 16}, {80, 16}, {96, 16}, {112, 16}, {128, 16}, {144, 16}, {160, 16}, {176, 16}, {192, 16}, {208, 16}, {224, 16},
    {0, 32}, {16, 32}, {32, 32}, {48, 32}, {64, 32}, {80, 32}, {96, 32}, {112, 32}, {128, 32}, {144, 32}, {160, 32}, {176, 32}, {192, 32}, {224, 32},
    {0, 48}, {32, 48}, {48, 48}, {64, 48}, {80, 48}, {96, 48}, {112, 48}, {128, 48}, {144, 48}, {160, 48}, {176, 48}, {192, 48}, {208, 48}, {224, 48},
    {0, 64}, {16, 64}, {48, 64}, {96, 64}, {160, 64}, {176, 64}, {192, 64}, {208, 64}, {224, 64},
    // underglow LEDs
    {0, 0}, {56, 0}, {112, 0}, {168, 0}, {224, 0},
    {0, 64}, {56, 64}, {112, 64}, {168, 64}, {224, 64}
},  {
    // LED Index to Flag
    // Indices are reveresed on the physical board, top left is bottom right.
    4, 4, 4, 1, 1, 4, 1, 1, 1,                      // first row
    1, 4, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,       // second row
    1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,       // third row
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,    // fourth row
    4, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,    // fifth row
    // underglow leds
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2
} };
