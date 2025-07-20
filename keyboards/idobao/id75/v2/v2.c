/* Copyright 2022 peepeetee
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
{ 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70 },
{ 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55 },
{ 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40 },
{ 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25 },
{ 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10 }
}, {
    // LED Index to Physical Position
{8, 12},{60, 12},{112, 12},{164, 12},{216, 12},
{216, 60},{164, 60},{112, 60},{60, 60},{8, 60},


{224, 64}, {208, 64}, {192, 64}, {176, 64}, {160, 64}, {144, 64}, {128, 64}, {112, 64}, {96, 64}, {80, 64}, {64, 64}, {48, 64}, {32, 64}, {16, 64}, {0, 64},
{224, 48}, {208, 48}, {192, 48}, {176, 48}, {160, 48}, {144, 48}, {128, 48}, {112, 48}, {96, 48}, {80, 48}, {64, 48}, {48, 48}, {32, 48}, {16, 48}, {0, 48},
{224, 32}, {208, 32}, {192, 32}, {176, 32}, {160, 32}, {144, 32}, {128, 32}, {112, 32}, {96, 32}, {80, 32}, {64, 32}, {48, 32}, {32, 32}, {16, 32}, {0, 32},
{224, 16}, {208, 16}, {192, 16}, {176, 16}, {160, 16}, {144, 16}, {128, 16}, {112, 16}, {96, 16}, {80, 16}, {64, 16}, {48, 16}, {32, 16}, {16, 16}, {0, 16},
{224,  0}, {208,  0}, {192,  0}, {176,  0}, {160,  0}, {144,  0}, {128,  0}, {112,  0}, {96,  0}, {80,  0}, {64,  0}, {48,  0}, {32,  0}, {16,  0}, {0,  0},

}, {
    // LED Index to Flag
2,2,2,2,2,2,2,2,2,2,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,

} };

#endif
