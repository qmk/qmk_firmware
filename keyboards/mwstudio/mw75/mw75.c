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

#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
  { 81,     80,     79,     78,     77,     76,     75,     74,     73,     72,     71,     70,     69,     68,     67 },
  { 66,     65,     64,     63,     62,     61,     60,     59,     58,     57,     56,     55,     54,     53,     52 },
  { 51,     50,     49,     48,     47,     46,     45,     44,     43,     42,     41,     40,     39,     38,     37 },
  { 36,     35,     34,     33,     32,     31,     30,     29,     28,     27,     26,     25,     NO_LED, 24,     23 },
  { 22,     NO_LED, 21,     20,     19,     18,     17,     16,     15,     14,     13,     12,     11,     10,     9 },
  { 8,      7,      6,      NO_LED, NO_LED, NO_LED, 5,      NO_LED, NO_LED, NO_LED, 4,      3,      2,      1,      0 },
  { 82,     83,     84,     85,     86,     87,     88,     89,     90,     91,     92,     93,     94,     95,     96 }
}, {
    { 217, 60 }, { 203, 60 }, { 189, 60 }, { 166, 60 }, { 150, 60 }, { 95, 60 }, { 40, 60 },  { 24, 60 },  { 8, 60 },
    { 217, 50 }, { 203, 50 }, { 184, 50 }, { 165, 50 }, { 151, 50 }, { 137, 50 }, { 123, 50 }, { 109, 50 }, { 95, 50 }, { 81, 50 }, { 67, 50 }, { 53, 50 }, { 39, 50 }, { 17, 50 },
    { 217, 40 }, { 195, 40 }, { 172, 40 }, { 158, 40 }, { 144, 40 }, { 130, 40 }, { 116, 40 }, { 102, 40 }, { 88, 40 }, { 74, 40 }, { 60, 40 }, { 46, 40 }, { 32, 40 }, { 13, 40 },
    { 217, 30 }, { 199, 30 }, { 181, 30 }, { 165, 30 }, { 151, 30 }, { 137, 30 }, { 123, 30 }, { 109, 30 }, { 95, 30 }, { 81, 30 }, { 67, 30 }, { 53, 30 }, { 39, 30 }, { 25, 30 }, { 9, 30 },
    { 217, 20 }, { 196, 20 }, { 175, 20 }, { 161, 20 }, { 147, 20 }, { 133, 20 }, { 119, 20 }, { 105, 20 }, { 91, 20 }, { 77, 20 }, { 63, 20 }, { 49, 20 }, { 35, 20 }, { 21, 20 }, { 7, 20 },
    { 217, 5 },  { 196, 5 },  { 182, 5 },  { 168, 5 },  { 154, 5 },  { 133, 5 },  { 119, 5 },  { 105, 5 },  { 91, 5 },  { 70, 5 },  { 56, 5 },  { 42, 5 },  { 28, 5 },  { 7, 5 },

    { 14, 14 }, { 42, 14 }, { 98, 14 }, { 154, 14 }, { 182, 14 }, { 210, 14 }, { 210, 25 }, { 210, 40 },
    { 210, 55 },{ 182, 55 },{ 126, 55 },{ 98, 55 },  { 42, 55 },  {  14, 55 }, { 14, 40 },  { 14, 25 }
}, {
    1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
} };
#endif
