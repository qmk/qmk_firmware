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

#include "favepada.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        { 17,     18,    19,       20 },
        { 16,     15,    14,       13 },
        { 9,      10,    11,       12 },
        { 8,       7,     6,   NO_LED },
        { 2,       3,     4,        5 },
        { 1,  NO_LED,     0,   NO_LED }
    }, {
        // LED Index to Physical Position
        { 149, 59 }, { 0, 59 },
        { 0, 51 }, { 74, 51 }, { 149, 51 }, { 224, 51 },
        { 149, 38 }, { 74, 38 },{ 0, 38 },
        { 0, 26 }, { 74, 26 }, { 149, 26 }, { 224, 26 },
        { 224, 13 }, { 149, 13 }, { 74, 13 }, { 0, 13 },
        { 0, 0 }, { 74, 0 }, { 149, 0 }, { 224, 0 },
        //under RGB
        { 224, 5 }, { 149, 5 }, { 74, 5 }, { 0, 5 },
        { 0, 18 }, { 0, 31 }, { 0, 43 }, { 0, 56 },
        { 0, 64 }, { 74, 64 }, { 149, 64 }, { 224, 64 },
        { 224, 56 }, { 224, 43 }, { 224, 31 }, { 224, 18 }
    }, {
        // LED Index to Flag
        1,1,
        1,1,1,1,
        1,1,1,
        1,1,1,1,
        1,1,1,9,
        2,2,2,2,
        4,4,4,4,
        4,4,4,4,
        4,4,4,4,
        4,4,4,4
    }
};
#endif
