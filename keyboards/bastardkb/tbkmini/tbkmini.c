/**
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

#include "tbkmini.h"

// clang-format off
#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    // left
    {  0,  5,  6, 11, 12, 15 },
    {  1,  4,  7, 10, 13, 16 },
    {  2,  3,  8,  9, 14, 17 },
    { NO_LED, 18, NO_LED, 19, 20, NO_LED },
    // right
    { 21, 26, 27, 32, 33, 36 },
    { 22, 25, 28, 31, 34, 37 },
    { 23, 24, 29, 30, 35, 38 },
    { NO_LED, 39, NO_LED, 40, 41, NO_LED }
}, {
    // left
    {   0,   0 }, {   0,  21 }, {   0,  42 }, // col 1
    {  20,  42 }, {  20,  21 }, {  20,   0 }, // col 2
    {  41,   0 }, {  41,  21 }, {  41,  42 },
    {  61,  42 }, {  61,  21 }, {  61,   0 },
    {  81,   0 }, {  81,  21 }, {  81,  42 },
    { 102,   0 }, { 102,  21 }, { 102,  42 },
    {  61,  64 }, {  81,  64 }, { 102,  64 }, // left thumb cluster
    // right
    { 224,   0 }, { 224,  21 }, { 224,  42 }, // col 12
    { 204,  42 }, { 204,  21 }, { 204,   0 }, // col 11
    { 183,   0 }, { 183,  21 }, { 183,  42 },
    { 163,  42 }, { 163,  21 }, { 163,   0 },
    { 142,   0 }, { 142,  21 }, { 142,  42 },
    { 122,   0 }, { 122,  21 }, { 122,  42 },
    { 163,  64 }, { 142,  64 }, { 122,  64 }  // right thumb cluster
}, {
    // left
    2, 2, 2, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4,
    2, 2, 2,
    // right
    2, 2, 2, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4,
    2, 2, 2
} };
#endif
// clang-format on
