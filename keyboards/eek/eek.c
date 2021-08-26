/* Copyright 2020 klackygears
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
#include "eek.h"

#ifdef RGB_MATRIX_ENABLE

  // Logical Layout
  // Columns
  //  0  1  2  3  4
  //                   ROWS
  //  4  3  2  1  0      0
  //  5  6  7  8  9      1
  // 14 13 12 11 10      2
  //       15 16 17      3

 // Logical Layout v1.3
  // Columns
  //  0  1  2  3  4  5  6  7  8  9
  //                                 ROWS
  //  0  1  2  3  4  5  6  7  8  9     0
  // 19 18 17 16 15 14 13 12 11 10     1
  // 20 21 22 23 24 25 26 27 28 29     2
  //       35 34 33 32 31 30           3


led_config_t g_led_config = { {
    {    0,  1,  2,  3,  4,  5,  6,  7,  8,  9  },
    {   19, 18, 17, 16, 15, 14, 13, 12, 11, 10  },
    {   20, 21, 22, 23, 24, 25, 26, 27, 28, 29  },
    { NO_LED, NO_LED, 35, 34, 33, 32, 31, 30, NO_LED, NO_LED }
}, {
    {  31,  0 }, {  46,  0 }, {  62,  0 }, {  77,  7 }, {  93, 13 }, { 131, 13 }, { 147,  7 }, { 162,  0 }, { 178,  0 }, { 193,  0 },
    { 201, 10 }, { 185, 10 }, { 170, 10 }, { 154, 17 }, { 139, 24 }, {  85, 24 }, {  70, 17 }, {  54, 10 }, {  39, 10 }, {  23, 10 },
    {  15, 20 }, {  31, 20 }, {  46, 20 }, {  62, 27 }, {  77, 34 }, { 147, 34 }, { 162, 27 }, { 178, 20 }, { 193, 20 }, { 209, 20 },
    { 185, 34 }, { 170, 37 }, { 154, 44 }, {  70, 44 }, {  54, 37 }, {  39, 34 },
}, {
     4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
     4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
     4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
     1, 1, 1, 1, 1, 1,
} };
#endif
