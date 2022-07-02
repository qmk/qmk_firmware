/* Copyright 2022 Envious Design
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
#include "rgb.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
  // Key Matrix to LED Index
	{ 0, NO_LED, 1, 2, 3, 4, NO_LED, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 },
	{ 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, NO_LED, 29, 30, 31, 32 },
	{ 33, NO_LED, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, NO_LED, 47, 48, 49},
	{ 50, NO_LED, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 46, NO_LED, NO_LED, NO_LED },
	{ 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, NO_LED, 75, NO_LED, NO_LED, 76, NO_LED },
	{ 77, 78, NO_LED, 79, NO_LED, NO_LED, 80, NO_LED, NO_LED, NO_LED, 81, 82, NO_LED, 83, 84, 85, 86, 87}
}, {
	// LED Index to Physical Position
    {  0,0  }, { 26,0  }, { 39,0  }, { 52,0  }, { 65,0  }, { 84,0  }, { 97,0  }, {110,0  }, {123,0  }, {143,0  }, 
    {156,0  }, {169,0  }, {182,0  }, {198,0  }, {211,0  }, {224,0  }, {  0,17 }, { 13,17 }, { 26,17 }, { 39,17 }, 
    { 52,17 }, { 65,17 }, { 78,17 }, { 91,17 }, {104,17 }, {117,17 }, {130,17 }, {143,17 }, {156,17 }, {175,17 }, 
    {198,17 }, {211,17 }, {224,17 }, {  3,29 }, { 19,29 }, { 32,29 }, { 45,29 }, { 58,29 }, { 71,29 }, { 84,29 }, 
    { 97,29 }, {110,29 }, {123,29 }, {136,29 }, {149,29 }, {162,29 }, {175,29 }, {198,29 }, {211,29 }, {224,29 }, 
    {  5,41 }, { 23,41 }, { 36,41 }, { 49,41 }, { 62,41 }, { 75,41 }, { 88,41 }, {101,41 }, {114,41 }, {127,41 }, 
    {140,41 }, {153,41 }, {166,41 }, {  2,52 }, { 16,52 }, { 29,52 }, { 42,52 }, { 55,52 }, { 68,52 }, { 81,52 }, 
    { 94,52 }, {107,52 }, {120,52 }, {133,52 }, {146,52 }, {170,52 }, {211,52 }, {  2,64 }, { 18,64 }, { 34,64 }, 
    { 83,64 }, {131,64 }, {148,64 }, {164,64 }, {180,64 }, {198,64 }, {211,64 }, {224,64 }, 
}, {
  // LED Index to Flag
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    8, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4
} };
#endif
