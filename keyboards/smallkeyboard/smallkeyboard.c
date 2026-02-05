/* Copyright 2021 zhouqiong19840119
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
    {0, C1_3, C2_3, C3_3},     // BL1
    {0, C1_4, C2_4, C3_4},     // BL2
    {0, C1_5, C2_5, C3_5},     // BL3
    {0, C1_11, C2_11, C3_11},  // BL4
    {0, C1_12, C2_12, C3_12},  // BL5
    {0, C1_13, C2_13, C3_13},  // BL6
};
#endif
