/* Copyright 2022 Yiancar
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

#include "nk20.h"

#ifdef RGB_MATRIX_ENABLE
// clang-format off
led_config_t g_led_config = { {   
    {   0,      1,   2, NO_LED }, 
    {   6,      5,   4,      3 }, 
    {   7,      8,   9,     10 }, 
    {  13,     12,  11, NO_LED }, 
    {  14,     15,  16,     17 }, 
    {  19, NO_LED,  18, NO_LED }, 
}, {
    {  0,0  }, { 75,0  }, {149,0  }, {224,15 }, {149,15 }, { 75,15 }, {  0,15 }, {  0,27 }, { 75,27 }, {149,27 }, 
    {224,34 }, {149,40 }, { 75,40 }, {  0,40 }, {  0,52 }, { 75,52 }, {149,52 }, {224,58 }, {149,64 }, { 37,64 }
}, {
    1, 1, 1,
    1, 1, 1, 1,
    4, 4, 4, 1,
    4, 4, 4,
    4, 4, 4, 1,
    4, 4
} };
// clang-format on
#endif
