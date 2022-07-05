/* Copyright 2022 Jose Pablo Ramirez <jp.ramangulo@gmail.com>
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

#ifdef RGB_MATRIX_ENABLE

#include "rgb_matrix.h"
#include "config_led.h"

#define NA NO_LED

led_config_t g_led_config = { {
    { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13 },
    { 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27 },
    { 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, NA },
    { 41, NA, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, NA },
    { 53, NA, 54, 55, NA, NA, 56, NA, NA, 57, 58, 59, 60, NA }
}, {
    { 0 ,  0 }, { 16,  0 }, { 32,  0 }, { 48,  0 }, { 65,  0 }, { 81,  0 }, { 97 ,  0 }, { 113,  0 }, { 129,  0 }, { 145,  0 }, { 161,  0 }, { 178,  0 }, { 194,  0 }, { 218,  0 },
    { 4 , 16 }, { 24, 16 }, { 40, 16 }, { 57, 16 }, { 73, 16 }, { 89, 16 }, { 105, 16 }, { 121, 16 }, { 137, 16 }, { 153, 16 }, { 170, 16 }, { 186, 16 }, { 202, 16 }, { 222, 16 },
    { 6 , 32 }, { 28, 32 }, { 44, 32 }, { 61, 32 }, { 77, 32 }, { 93, 32 }, { 109, 32 }, { 125, 32 }, { 141, 32 }, { 157, 32 }, { 174, 32 }, { 190, 32 }, { 216, 32 },
    { 10, 48 },             { 36, 48 }, { 52, 48 }, { 69, 48 }, { 85, 48 }, { 101, 48 }, { 117, 48 }, { 133, 48 }, { 149, 48 }, { 165, 48 }, { 182, 48 }, { 212, 48 },
    { 2 , 64 }, { 22, 64 }, { 42, 64 },                                     { 103, 64 },                           { 163, 64 }, { 184, 64 }, { 204, 64 }, { 224, 64 },
}, {
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    4,
    1,    4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    1,
    1, 1, 1,          4,          1, 1, 1, 1,
} };
#endif
