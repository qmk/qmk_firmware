/* Copyright 2022 DOIO
 * Copyright 2022 HorrorTroll <https://github.com/HorrorTroll>
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

#include "rev2.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    {  0,      1,      2,      3, NO_LED },
    {  4,      5,      6,      7, NO_LED },
    {  8,      9,     10,     11, NO_LED },
    { 12,     13,     14,     15, NO_LED }
}, {
    {0  ,  0}, {75 ,  0}, {149,  0}, {224,  0},
    {0  , 21}, {75 , 21}, {149, 21}, {224, 21},
    {0  , 43}, {75 , 43}, {149, 43}, {224, 43},
    {0  , 64}, {75 , 64}, {149, 64}, {224, 64},
}, {
    1, 1, 1, 1,
    1, 4, 4, 1,
    1, 4, 4, 1,
    1, 1, 1, 1,
} };
#endif
