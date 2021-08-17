/* 
 * Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
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

#include "skeletyl.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    // left
    {  0,  5,  6, 11, 12 },
    {  1,  4,  7, 10, 13 },
    {  2,  3,  8,  9, 14 },
    { 15, NO_LED, 16, 17, NO_LED },
    // right
    { 18, 23, 24, 29, 30 },
    { 19, 22, 25, 28, 31 },
    { 20, 21, 26, 27, 32 },
    { 33, NO_LED, 34, 35, NO_LED }
}, {
    // left
    {   0,   0 }, {   0,  21 }, {   0,  42 }, // col 1
    {  25,  42 }, {  25,  21 }, {  25,   0 }, // col 2
    {  50,   0 }, {  50,  21 }, {  50,  42 },
    {  74,  42 }, {  74,  21 }, {  74,   0 },
    {  99,   0 }, {  99,  21 }, {  99,  42 },
    {  50,  64 }, {  74,  64 }, {  99,  64 }, // left thumb cluster
    // right
    { 224,   0 }, { 224,  21 }, { 224,  42 }, // col 10
    { 198,  42 }, { 198,  21 }, { 198,   0 }, // col 9
    { 174,   0 }, { 174,  21 }, { 174,  42 },
    { 149,  42 }, { 149,  21 }, { 149,   0 },
    { 124,   0 }, { 124,  21 }, { 124,  42 },
    { 174,  64 }, { 149,  64 }, { 124,  64 }  // right thumb cluster
}, {
    // left
    4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4,
    2, 2, 2,
    // right
    4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4,
    2, 2, 2
} };
#endif
