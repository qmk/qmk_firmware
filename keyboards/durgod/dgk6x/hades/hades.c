/* Copyright 2021 Jessica Sullivan and Don Kjer 
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

#include "hades.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = {{
    { 0,  1,  2,  3,      4,      5,  6,      7,      8,      9,  10, 11, 12,     13, 14 },
    { 15, 16, 17, 18,     19,     20, 21,     22,     23,     24, 25, 26, 27,     28, 29 },
    { 30, 31, 32, 33,     34,     35, 36,     37,     38,     39, 40, 41, NO_LED, 42, 43 },
    { 44, 45, 46, 47,     48,     49, 50,     51,     52,     53, 54, 55, NO_LED, 56, 57 },
    { 58, 59, 60, NO_LED, NO_LED, 61, NO_LED, NO_LED, NO_LED, 62, 63, 64, 65,     66, 67 }
}, {
    {  0,  0 }, { 16,  0 }, { 32,  0 }, { 48,  0 }, { 64,  0 }, { 80,  0 }, { 96,   0 }, { 112,  0 }, { 128,  0 }, { 144,  0 }, { 160,  0 }, { 176,  0 }, { 192,  0 }, { 216,  0 }, { 240,  0 }, 
    {  4, 16 }, { 24, 16 }, { 40, 16 }, { 56, 16 }, { 72, 16 }, { 88, 16 }, { 104, 16 }, { 120, 16 }, { 136, 16 }, { 152, 16 }, { 168, 16 }, { 184, 16 }, { 200, 16 }, { 220, 16 }, { 240, 16 },
    {  6, 32 }, { 28, 32 }, { 44, 32 }, { 60, 32 }, { 76, 32 }, { 92, 32 }, { 108, 32 }, { 124, 32 }, { 140, 32 }, { 156, 32 }, { 172, 32 }, { 188, 32 },              { 214, 32 }, { 240, 32 },
    { 10, 48 },             { 36, 48 }, { 52, 48 }, { 68, 48 }, { 84, 48 }, { 100, 48 }, { 116, 48 }, { 132, 48 }, { 148, 48 }, { 164, 48 }, { 180, 48 }, { 202, 48 }, { 224, 48 }, { 240, 48 },
    {  2, 64 }, { 22, 64 }, { 42, 64 },                                     { 101, 64 },                           { 160, 64 }, { 176, 64 }, { 192, 64 }, { 208, 64 }, { 224, 64 }, { 240, 64 }
}, {
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    1, 4,
    1,    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 4, 4,
    1, 1, 1,          4,       1, 1, 1, 4, 4, 4
}};
#endif /* RGB_MATRIX_ENABLE */
