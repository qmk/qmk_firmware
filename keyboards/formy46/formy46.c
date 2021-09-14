/* Copyright 2021 marby3
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

#include "formy46.h"

#ifdef RGB_MATRIX_ENABLE
    led_config_t g_led_config = { {
    // Key Matrix to LED Index LEFT
        {   4,  3,  2,  1,  0        },
        {   5,  6,  7,  8,  9,   22  },
        {  14, 13, 12, 11, 10,   21  },
        {  15, 16, 17, 18,   19, 20  },
    // Key Matrix to LED Index RIGHT
        {        23, 24, 25, 26, 27  },
        {  45,   32, 31, 30, 29, 28  },
        {  44,   33, 34, 35, 36, 37  },
        {  43, 42,   41, 40, 39, 38  }
    }, {
    // LED Index to Physical Position
        {  70,   4 }, {  53,   0 }, {  37,   2 }, {  18,   6 }, {   0,  12 },
        {   2,  28 }, {  20,  22 }, {  38,  18 }, {  54,  16 }, {  70,  20 },
        {  70,  36 }, {  55,  32 }, {  39,  34 }, {  22,  38 }, {   4,  44 },
        {   6,  60 }, {  24,  54 }, {  40,  50 }, {  56,  48 },
        {  78,  54 }, {  94,  59 }, { 110,  64 }, {  98,  42 },
        { 154,   4 }, { 171,   0 }, { 187,   2 }, { 206,   6 }, { 224,  12 },
        { 222,  28 }, { 204,  22 }, { 186,  18 }, { 170,  16 }, { 154,  20 },
        { 154,  36 }, { 169,  32 }, { 185,  34 }, { 202,  38 }, { 220,  44 },
        { 218,  60 }, { 200,  54 }, { 184,  50 }, { 168,  48 },
        { 146,  54 }, { 130,  59 }, { 114,  64 }, { 126,  42 }
    }, {
    // LED Index to Flag
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4
} };
#endif

void matrix_init_kb(void) {
	matrix_init_user();
};
