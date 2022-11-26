/* Copyright 2020 Ungodly Design <hello@ungodly.design>
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
#include "launch_pad.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    // Key Matrix to LED Index
    { 14, 15, 16, 17 },
    { 13, 12, 11, 10 },
    { 6, 7, 8, 9 },
    { 5, 4, 3, 2 },
    {NO_LED, 0, 1, NO_LED }
}, {  // LED Index to Physical Position
     { 37, 60 }, { 148, 60 },                            // row 5
    { 222, 54 }, { 148, 45 },  { 74, 45 },   { 0, 45 },  // row 4
      { 0, 30 },  { 74, 30 }, { 148, 30 }, { 222, 30 },  // row 3
    { 222, 15 }, { 148, 15 },  { 74, 15 },   { 0, 15 },  // row 2
       { 0, 0 },   { 74, 0 },  { 148, 0 },  { 222, 0 },  // row 1
     { 185, 7 },   { 37, 7 },                            // top underglow
     { 37, 52 }, { 185, 52 },                            // bottom underglow
}, {
    // LED Index to Flag
    4, 4,       // row 5
    4, 4, 4, 4, // row 4
    4, 4, 4, 4, // row 3
    4, 4, 4, 4, // row 2
    4, 4, 4, 4, // row 1
    2, 2,
    2, 2
} };
#endif
