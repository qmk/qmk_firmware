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

#include "mw65_rgb.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
  { 82,     81,     80,     79,     78,     77,     76,     75,     74,     73,     72,     71,     70,     69,     68 },
  { 53,     54,     55,     56,     57,     58,     59,     60,     61,     62,     63,     64,     65,     66,     67 },
  { 52,     51,     50,     49,     48,     47,     46,     45,     44,     43,     42,     41,     NO_LED, 40,     39 },
  { 25,     NO_LED, 26,     27,     28,     29,     30,     31,     32,     33,     34,     35,     36,     37,     38 },
  { 24,     23,     22,     NO_LED, NO_LED, NO_LED, 21,     NO_LED, NO_LED, 15,     20,     19,     18,     17,     16 },

  { 0,      1,      2,      3,      4,      5,      6,      7,      8,      9,      10,     11,     12,     13,     14 }
}, {
    { 175, 45 },{ 130, 45 },{ 85, 45 },  { 50, 45 },  {  15, 45 }, { 15, 35 }, { 15, 25 }, { 15, 10 },
    { 50, 10 }, { 85, 10 }, { 130, 10 }, { 175, 10 }, { 210, 10 }, { 210, 25 }, { 210, 35 }, { 210, 45 },
    { 217, 54 }, { 203, 54 }, { 189, 54 }, { 166, 54 }, { 150, 54 }, { 95, 54 }, { 40, 54 }, { 24, 54 }, { 8, 54 },
    { 17, 42 }, { 39, 42 }, { 53, 42 }, { 67, 42 }, { 81, 42 }, { 95, 42 }, { 109, 42 }, { 123, 42 }, { 137, 42 }, { 151, 42 }, { 165, 42 }, { 184, 42 }, { 203, 42 }, { 217, 42 },
    { 217, 30 }, { 195, 30 }, { 172, 30 }, { 158, 30 }, { 144, 30 }, { 130, 30 }, { 116, 30 }, { 102, 30 }, { 88, 30 }, { 74, 30 }, { 60, 30 }, { 46, 30 }, { 32, 30 },{ 13, 30 },
    { 9, 18 }, { 25, 18 }, { 39, 18 }, { 53, 18 }, { 67, 18 }, { 81, 18 }, { 95, 18 }, { 109, 18 }, { 123, 18 }, { 137, 18 }, { 151, 18 }, { 165, 18 }, { 181, 18 }, { 199, 18 }, { 217, 18 },
    { 217, 6 }, { 196, 6 }, { 175, 6 }, { 161, 6 }, { 147, 6 }, { 133, 6 }, { 119, 6 }, { 105, 6 }, { 91, 6 }, { 77, 6 }, { 63, 6 }, { 49, 6 }, { 35, 6 }, { 21, 6 }, { 7, 6 },
}, {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
} };
#endif

