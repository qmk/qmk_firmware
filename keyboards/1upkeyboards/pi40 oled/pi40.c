/* Copyright 2022 ziptyze
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

#include "pi40.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    // Key Matrix to LED Index
    {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11 },
    { 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12 },
    { 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35 },
    { 46, 45, 44, 43, 42, 41, NO_LED, 40, 39, 38, 37, 36 }
}, {
    // LED Index to Physical Position
    {   9,  8 }, {  28,  8 }, {  46,  8 }, {  65,  8 }, {  84,  8 }, { 102,  8 }, { 121,  8 }, { 140,  8 }, { 159,  8 }, { 177,  8 }, { 196,  8 }, { 215,  8 },
    { 215, 24 }, { 196, 24 }, { 177, 24 }, { 159, 24 }, { 140, 24 }, { 121, 24 }, { 102, 24 }, {  84, 24 }, {  65, 24 }, {  46, 24 }, {  28, 24 }, {   9, 24 },
    {   9, 40 }, {  28, 40 }, {  46, 40 }, {  65, 40 }, {  84, 40 }, { 102, 40 }, { 121, 40 }, { 140, 40 }, { 159, 40 }, { 177, 40 }, { 196, 40 }, { 215, 40 },
    { 215, 56 }, { 196, 56 }, { 177, 56 }, { 159, 56 }, { 140, 56 }, { 112, 56 }, {  84, 56 }, {  65, 56 }, {  46, 56 }, {  28, 56 }, {   9, 56 }
}, {
    // LED Index to Flag
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
} };
#endif