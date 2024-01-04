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

#include "quantum.h"

// clang-format off
#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    // left
    {  0,  7,  8, 15, 16, 20 },
    {  1,  6,  9, 14, 17, 21 },
    {  2,  5, 10, 13, 18, 22 },
    {  3,  4, 11, 12, 19, 23 },
    { NO_LED, 28, 24, 26, 27, 25 },
    // right
    { 29, 36, 37, 44, 45, 49 },
    { 30, 35, 38, 43, 46, 50 },
    { 31, 34, 39, 42, 47, 51 },
    { 32, 33, 40, 41, 48, 52 },
    { NO_LED, 57, 53, 55, 56, 54 }
}, {
    // left
    {   0,   0 }, {   0,  16 }, {   0,  32 }, {   0,  48 }, // col 1
    {  20,  48 }, {  20,  32 }, {  20,  16 }, {  20,   0 }, // col 2
    {  41,   0 }, {  41,  16 }, {  41,  32 }, {  41,  48 },
    {  61,  48 }, {  61,  32 }, {  61,  16 }, {  61,   0 },
    {  81,   0 }, {  81,  16 }, {  81,  32 }, {  81,  48 },
    { 102,   0 }, { 102,  16 }, { 102,  32 }, { 102,  48 },
    { 102,  64 }, {  81,  64 }, {  61,  56 }, {  81,  56 }, { 102,  56 }, // left thumb cluster
    // right
    { 224,   0 }, { 224,  16 }, { 224,  32 }, { 224,  48 }, // col 12
    { 204,  48 }, { 204,  32 }, { 204,  16 }, { 204,   0 }, // col 11
    { 183,   0 }, { 183,  16 }, { 183,  32 }, { 183,  48 },
    { 163,  48 }, { 163,  32 }, { 163,  16 }, { 163,   0 },
    { 142,   0 }, { 142,  16 }, { 142,  32 }, { 142,  48 },
    { 122,   0 }, { 122,  16 }, { 122,  32 }, { 122,  48 },
    { 122,  64 }, { 142,  64 }, { 163,  56 }, { 142,  56 }, { 122,  56 } // right thumb cluster
}, {
    // left
    2, 2, 2, 2, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    2, 2, 2, 2, 2,
    // right
    2, 2, 2, 2, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    2, 2, 2, 2, 2
} };
#endif
// clang-format on
