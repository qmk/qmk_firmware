 /* Copyright 2021 18438880
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

const is31fl3731_led_t PROGMEM g_is31fl3731_leds[IS31FL3731_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
	{0, C1_3,  C2_3,  C3_3},// BL1
    {0, C1_4,  C2_4,  C3_4},// BL2
    {0, C1_5,  C2_5,  C3_5},// BL3
    {0, C1_11, C2_11, C3_11},// BL4
    {0, C1_12, C2_12, C3_12},// BL5
    {0, C1_13, C2_13, C3_13},// BL6
    {0, C1_6,  C2_6,  C3_6},// BL7
    {0, C1_7,  C2_7,  C3_7},//BL8 
    {0, C1_8,  C2_8,  C3_8},// BL9
    {0, C1_14, C2_14, C3_14},// BL10
    {0, C1_15, C2_15, C3_15},// BL11
    {0, C1_16,C2_16,C3_16},// BL12
    {0, C7_1,  C8_1,  C9_1},// BL13
    {0, C9_2,  C8_2,  C7_2},// BL14
    {0, C9_3, C8_3, C7_3},//BL15
    {0, C9_5, C8_5, C7_5},// BL16
    {0, C9_6, C8_6, C7_6},// BL17
	
};

led_config_t g_led_config = {
    {
        { 0,      1,       2,      3},
        { 4,      5,       6,      7},
        { 8,      9,      10, NO_LED},
        { 11,     12,     13,     14},
        { 15,     16, NO_LED, NO_LED},
    },
    {
        { 48, 32},{ 48, 48},{ 64, 48},{ 80, 48},
        { 16, 32},{ 16, 48}, { 32, 48},{ 64, 64},
        { 80, 16},{ 64, 32},{ 80, 32},
        {112,  0},{128,  0},{144,  0},{160,  0},
        {128, 16},{144, 16}
    },
    {
        4, 4, 4, 1,
        1, 1, 4, 1,
        1, 4, 4,
        1, 4, 4, 4,
        4, 4
    }
};
#endif
