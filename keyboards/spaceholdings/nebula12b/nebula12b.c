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

#include "nebula12b.h"

#ifdef RGB_MATRIX_ENABLE
// clang-format off
led_config_t g_led_config = { {
    { 13, 15,  1 }, 
    {  4,  3,  2 }, 
    {  5,  6,  7 }, 
    { 11, 10,  9 }, 
}, {
    {224,  0 }, {224,  9 }, {224, 27 }, {112, 27 }, {  0,27 }, 
    {  0, 46 }, {112, 46 }, {224, 46 }, {224, 55 }, {224,64 }, 
    {112, 64 }, {  0, 64 }, {  0, 55 }, {  0,  9 }, {  0, 0 }, {112, 9 }
}, {
    2,
    4, 4, 4, 4, 4, 4, 4,
    2,
    4, 4, 4,
    2,
    4,
    2,
    4
} };
// clang-format on
#endif

