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

#include "nk_plus.h"

#ifdef RGB_MATRIX_ENABLE
// clang-format off
led_config_t g_led_config = { {
    {   0,  1,   2,      3,   4,      5,      6,      7,   8,      9,     10,     11,     12, 13,     14, 15, 16 },
    {  33, 32,  31,     30,  29,     28,     27,     26,  25,     24,     23,     22,     21, 20,     19, 18, 17 },
    {  34, 35,  36,     37,  38,     39,     40,     41,  42,     43,     44,     45,     46, 47, NO_LED, 48, 49 },
    {  65, 64,  63, NO_LED,  62,     61,     60,     59,  58,     57,     56,     55,     54, 53,     52, 51, 50 },
    {  66, 67,  68,     69,  70, NO_LED, NO_LED, NO_LED,  71, NO_LED, NO_LED, NO_LED, NO_LED, 72,     73, 74, 75 }
}, {

    {  0,0  }, { 13,0  }, { 32,0  }, { 45,0  }, { 58,0  }, { 70,0  }, { 83,0  }, { 96,0  }, {109,0  }, {122,0  }, {134,0  }, {147,0  }, {160,0  }, {173,0  }, {186,0  }, {205,0  }, {224,0  },
    {224,16 }, {208,16 }, {192,16 }, {179,16 }, {166,16 }, {154,16 }, {141,16 }, {128,16 }, {115,16 }, {102,16 }, { 90,16 }, { 77,16 }, { 64,16 }, { 51,16 }, { 35,16 }, { 13,16 }, {  0,16 },
    {  0,32 }, { 13,32 }, { 37,32 }, { 54,32 }, { 67,32 }, { 80,32 }, { 93,32 }, {106,32 }, {118,32 }, {131,32 }, {144,32 }, {157,32 }, {170,32 }, {182,32 }, {203,32 }, {224,32 }, 
    {224,48 }, {211,48 }, {194,48 }, {176,48 }, {163,48 }, {150,48 }, {138,48 }, {125,48 }, {112,48 }, { 99,48 }, { 86,48 }, { 74,48 }, { 61,48 }, { 40,48 }, { 13,48 }, {  0,48 },
    {  0,64 }, { 13,64 }, { 35,64 }, { 51,64 }, { 67,64 }, {122,64 }, {176,64 }, {198,64 }, {211,64 }, {224,64 }
}, {
    1, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1,
    1, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1,
    1, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1,
    1, 1, 1, 1, 1, 4, 1, 1, 1,1 
} };
// clang-format on
#endif
