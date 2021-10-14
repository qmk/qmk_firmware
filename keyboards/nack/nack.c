/* Copyright 2020 farfalleflickan <farfalleflickan@gmail.com>
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

#include QMK_KEYBOARD_H

#ifdef RGB_MATRIX_ENABLE
    led_config_t g_led_config = { {
      // Key Matrix to LED Index
      {   0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 },
      {  13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25 },
      {  26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38 },
      {  39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51 }
    }, {
      // LED Index to Physical Position
      { 0, 0 }, { 19,  0 }, { 38,  0 }, { 57,  0 }, { 76,  0 }, { 95, 0 }, { 114,  0 }, { 133,  0 }, { 152,  0 }, { 171,  0 }, { 190, 0 }, { 209,  0 }, { 223,  0 },
      { 0, 21 }, { 19,  21 }, { 38,  21 }, { 57,  21 }, { 76,  21 }, { 95, 21 }, { 114,  21 }, { 133,  21 }, { 152,  21 }, { 171,  21 }, { 190, 21 }, { 209,  21 }, { 223,  21 },
      { 0, 42 }, { 19,  42 }, { 38,  42 }, { 57,  42 }, { 76,  42 }, { 95, 42 }, { 114,  42 }, { 133,  42 }, { 152,  42 }, { 171,  42 }, { 190, 42 }, { 209,  42 }, { 223,  42 },
      { 0, 63 }, { 19,  63 }, { 38,  63 }, { 57,  63 }, { 76,  63 }, { 95, 63 }, { 114,  63 }, { 133,  63 }, { 152,  63 }, { 171,  63 }, { 190, 63 }, { 209,  63 }, { 223,  63 }
    }, {
      // LED Index to Flag
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
    } };
#endif

