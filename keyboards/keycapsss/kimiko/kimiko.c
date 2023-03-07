/* Copyright 2020 @ben_roe (keycapsss.com)
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
#include "kimiko.h"

#ifdef RGB_MATRIX_ENABLE

//Thanks to Ben (keycapsss) for helpipng me to create g_led_config

// Physical LED position
// X 0   16  32  48  64  80  96    112 128 144 160 176 208 224
//   -----------------------------------------------------------|  Y
//   5   4   3   2   1   0             0   1   2   3   4   5    |  0
//   6   7   8   9   10  11            11  10  9   8   7   6    |  16
//   17  16  15  14  13  12            12  13  14  15  16  17   |  32
//   18  19  20  21  22  23  24    24  23  22  21  20  19  18   |  48
//           29  28  27  26  25    25  26  27  28  29           |  64

led_config_t g_led_config = { {
    // Key Matrix to LED Index
    { 5,  4,  3,  2,  1,  0  },
    { 6,  7,  8,  9,  10, 11 },
    { 17, 16, 15, 14, 13, 12 },
    { 18, 19, 20, 21, 22, 23 },
    { 29, 28, 27, 26, 25, 24 },
    { 35, 34, 33, 32, 31, 30 },
    { 36, 37, 38, 39, 40, 41 },
    { 47, 46, 45, 44, 43, 42 },
    { 48, 49, 50, 51, 52, 53 },
    { 59, 58, 57, 56, 55, 54 }
}, {
    // LED Index to Physical Position
    // Left half
    { 80, 0 },  { 64, 0 },  { 48, 0 },  { 32, 0 },  { 16, 0 },  { 0, 0 },
    { 0, 16 },  { 16, 16 }, { 32, 16 }, { 48, 16 }, { 64, 16 }, { 80, 16 },
    { 80, 32 }, { 64, 32 }, { 48, 32 }, { 32, 32 }, { 16, 32 }, { 0, 32 },
    { 0, 48 },  { 16, 48 }, { 32, 48 }, { 48, 48 }, { 64, 48 }, { 80, 48 },
    { 96, 48 }, { 96, 64 }, { 80, 64 }, { 64, 64 }, { 48, 64 }, { 32, 64 },
    // Right half
    { 128, 0 }, { 144, 0 }, { 160, 0 }, { 176, 0 }, { 208, 0 }, { 224, 0 },
    { 224, 16 }, { 208, 16 }, { 176, 16 }, { 160, 16 }, { 144, 16 }, { 128, 16 },
    { 128, 32 }, { 144, 32 }, { 160, 32 }, { 176, 32 }, { 208, 32 }, { 224, 32 },
    { 224, 48 }, { 208, 48 }, { 176, 48 }, { 160, 48 }, { 144, 48 }, { 128, 48 },
    { 112, 48 }, { 112, 64 }, { 128, 64 }, { 144, 64 }, { 160, 64 }, { 176, 64 }

}, {
    // LED Index to Flag
    // 0x01 = 1 = modifier key
    // 0x02 = 2 = underglow
    // 0x04 = 4 = key backlight
    // 0x08 = 8 = keyboard state indication
    // Left half
    4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 1,
    4, 4, 4, 4, 4, 1,
    4, 4, 1, 1, 1, 1,
    // Right half
    4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4,
    1, 4, 4, 4, 4, 4,
    4, 4, 1, 1, 1, 1
} };

#endif // RGB_MATRIX_ENABLE