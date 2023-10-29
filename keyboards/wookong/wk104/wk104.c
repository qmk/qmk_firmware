/* Copyright 2023 Gyphae Team <https://github.com/gyphae>
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

#ifdef RGB_MATRIX_ENABLE
#define __ NO_LED
led_config_t g_led_config = {
	{
        // Key Matrix to LED Index
        {  0, __,  1,  2,  3,  4, __,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, __, __, __ },
        { 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16 },
        { 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57 },
        { 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, __, 61, __, __, __, 60, 59, 58, __ },
        { 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, __, 85, __, __, 86, __, 87, 88, 89, __ },
        {103,102,101, __, __, __,100, __, __, __, 99, 98, 97, 96, 95, 94, 93, __, 92, 91, 90 },
    },
    {
        // LED Index to Physical Position
        {0,0},           {13,0},  {24,0},  {34,0},  {45,0},            {68,0},  {78,0},  {89,0},  {102,0},  {112,0},  {123,0},  {133,0},  {159,0},  {169,0},  {180,0},  {193,0},
        {0,15}, {10,15}, {21,15}, {31,15}, {42,15}, {52,15}, {63,15}, {73,15}, {83,15}, {94,15},  {104,15}, {115,15}, {125,15}, {141,15}, {159,15}, {169,15}, {180,15}, {193,15}, {203,15}, {214,15}, {224,15},
        {3,27}, {16,27}, {26,27}, {36,27}, {47,27}, {57,27}, {68,27}, {78,27}, {89,27}, {99,27},  {109,27}, {120,27}, {130,27}, {143,27}, {159,27}, {169,27}, {180,27}, {193,27}, {203,27}, {214,27}, {224,27},
        {4,40}, {18,40}, {29,40}, {39,40}, {50,40}, {60,40}, {70,40}, {81,40}, {91,40}, {102,40}, {112,40}, {123,40},           {139,40},                               {193,40}, {203,40}, {214,40}, 
        {7,52}, {23,52}, {34,52}, {44,52}, {55,52}, {65,52}, {76,52}, {86,52}, {96,52}, {107,52}, {116,52},           {137,52},                     {169,52},           {193,52}, {203,52}, {214,52},
        {1,64}, {14,64}, {27,64},                            {66,64},                             {105,64}, {118,64}, {131,64}, {145,64}, {159,64}, {169,64}, {180,64},           {198,64}, {214,64}, {224,58},
    },
    {
        // RGB LED Index to Flag
        1,    1, 1, 1, 1,    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 1, 8, 4, 4, 4,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 4, 4, 4, 4,
        8, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    1,          4, 4, 4, 
        1,    4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    1,       1,    4, 4, 4,
        1, 1, 1,          4,          1, 1, 1, 1, 1, 1, 1,    1, 4, 1,
    }
};

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
#ifdef CAPS_LOCK_LED_INDEX	
	if (host_keyboard_led_state().caps_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(CAPS_LOCK_LED_INDEX, 255, 255, 255);
    } else {
        if (!rgb_matrix_get_flags()) {
           RGB_MATRIX_INDICATOR_SET_COLOR(CAPS_LOCK_LED_INDEX, 0, 0, 0);
        }
    }
#endif

#ifdef NUM_LOCK_LED_INDEX
	if (host_keyboard_led_state().num_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(NUM_LOCK_LED_INDEX, 255, 255, 255);
    } else {
        if (!rgb_matrix_get_flags()) {
           RGB_MATRIX_INDICATOR_SET_COLOR(NUM_LOCK_LED_INDEX, 0, 0, 0);
        }
    }
#endif
    return true;
}

#endif // RGB_MATRIX_ENABLE