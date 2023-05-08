/* Copyright 2020 Moritz Plattner
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

#include "fave60a.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        { 59,     58, 57,    56,     55,     54, 53,     52,     51,     50,     49,   48,      47,     46, NO_LED },
        { 32,     33, 34,    35,     36,     37, 38,     39,     40,     41,     42,   43,      44,     45, NO_LED },
        { 31,     30, 29,    28,     27,     26, 25,     24,     23,     22,     21,   20,  NO_LED,     19, NO_LED },
        { 7, NO_LED,  8,      9,     10,     11, 12,     13,     14,     15,     16,   17,  NO_LED,     18, NO_LED },
        { 6,      5,  4, NO_LED, NO_LED, NO_LED,  3, NO_LED, NO_LED, NO_LED, NO_LED,    2,       1,      0, NO_LED }
    }, {
        // LED Index to Physical Position
        { 208, 64 }, { 192, 64 }, { 176, 64 }, { 96, 64 }, { 32, 64 }, { 16, 64 }, { 0, 64 },
        { 0, 48 }, { 32, 48 }, { 48, 48 }, { 64, 48 }, { 80, 48 }, { 96, 48 }, { 112, 48 }, { 128, 48 }, { 144, 48 }, { 160, 48 }, { 176, 48 }, { 208, 48 },
        { 208, 32 }, { 176, 32 }, { 160, 32 }, { 144, 32 }, { 128, 32 }, { 112, 32 }, { 96, 32 }, { 80, 32 }, { 64, 32 }, { 48, 32 }, { 24, 32 }, { 12, 32 }, { 0, 32 },
        { 0, 16 }, { 16, 16 }, { 32, 16 }, { 48, 16 }, { 64, 16 }, { 80, 16 }, { 96, 16 }, { 112, 16 }, { 128, 16 }, { 144, 16 }, { 160, 16 }, { 176, 16 }, { 192, 16 }, { 208, 16 },
        { 208, 0 }, { 192, 0 }, { 176, 0 }, { 160, 0 }, { 144, 0 }, { 128, 0 }, { 112, 0 }, { 96, 0 }, { 80, 0 }, { 64, 0 }, { 48, 0 }, { 32, 0 }, { 16, 0 }, { 0, 0 },
        //Under RGB
        {0,3}, {16,3},{32,3},{48,3},{64,3},{80,3},{96,3},{112,3},{128,3},{144,3},{160,3},{176,3},{192,3},{208,3},
        {208,19},{208,35},
        {208,51},{176,51},{160,51},{144,51},{128,51},{112,51},{96,51},{80,51},{64,51},{48,51},{32,51},{16,51},{0,51},
        {0,35},{0,19}
    }, {
        // LED Index to Flag
        4,4,4,1,4,4,4,
        4,1,1,1,1,1,1,1,1,1,1,4,
        1,1,1,1,1,1,1,1,1,1,1,1,9,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        2,2,2,2,2,2,2,2,2,2,
        2,2,2,2,2,2,2,2,2,2,
        2,2,2,2,2,2,2,2,2,2,2
    }
};
#endif
