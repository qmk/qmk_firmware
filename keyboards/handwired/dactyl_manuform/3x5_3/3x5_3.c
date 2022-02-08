/*
Copyright 2021 @dlford

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "3x5_3.h"

#ifdef RGB_MATRIX_ENABLE

// LED Layout
// Columns
// 0   1   2   3   4   5   6   7   8   9   10  11
// Physical (Center: 133)
// 20  41  61  81  102 122 143 163 183 204 224 244
//                                                  Rows  Physical (Center: 54)
// 17  12  11  06  05          23  24  29  30  35   0     21
// 16  13  10  07  04          22  25  28  31  34   1     43
// 15  14  09  08  03          21  26  27  32  33   2     64
//             02  01  00  18  19  20               3     85

led_config_t g_led_config = { {
    // Key matrix to LED index
    // Left 1-18
            {17, 12, 11,  6,  5},
            {16, 13, 10,  7,  4},
            {15, 14,  9,  8,  3},
    {NO_LED, NO_LED,  2,  1,  0},
                                    // Right 1-18
                                    {23, 24, 29, 30, 35},
                                    {22, 25, 28, 31, 34},
                                    {21, 26, 27, 32, 33},
                                    {18, 19, 20, NO_LED, NO_LED},
}, {
    // LED index to physical position
    // Left 1-18
    {122,85},{102,85},{81,85},{102,64},{102,43},{102,21},
    {81,21},{81,43},{81,64},{61,64},{61,43},{61,21},
    {41,21},{41,43},{41,64},{20,64},{20,43},{20,21},
    // Right 1-18
    {143,85},{163,85},{183,85},{163,64},{163,43},{163,21},
    {183,21},{183,43},{183,64},{204,64},{204,43},{204,21},
    {224,21},{224,43},{224,64},{244,64},{244,43},{244,21}
}, {
    // LED index to flag
    // Left 1-18
    4,4,4,4,4,4,
    4,4,4,4,4,4,
    4,4,4,4,4,4,
    // Right 1-18
    4,4,4,4,4,4,
    4,4,4,4,4,4,
    4,4,4,4,4,4
} };

#endif
