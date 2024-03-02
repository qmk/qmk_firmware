/*
Copyright 2022 Mechlovin'

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

#include "quantum.h"



const is31fl3731_led_t PROGMEM g_is31fl3731_leds[LED_MATRIX_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *    driver
 *    |  LED address
 *    |  | */
    { 0, C2_1  },  { 0, C2_2 },  { 0, C2_3  },  { 0, C2_4 },  { 0, C2_5  },  { 0, C2_6 },  { 0, C2_7  },  { 0, C2_8 },  { 0, C2_9  },  { 0, C2_10 },  { 0, C2_11  },  { 0, C2_12 },  { 0, C2_13  },  { 0, C2_14 },  { 0, C2_15  },  { 0, C2_16 },
    { 0, C3_1  },  { 0, C3_2 },  { 0, C3_3  },  { 0, C3_4 },  { 0, C3_5  },  { 0, C3_6 },  { 0, C3_7  },  { 0, C3_8 },  { 0, C3_9  },  { 0, C3_10 },  { 0, C3_11  },  { 0, C3_12 },  { 0, C3_13  },  { 0, C3_14 },                  { 0, C3_16 },
    { 0, C4_1  },  { 0, C4_2 },  { 0, C4_3  },  { 0, C4_4 },  { 0, C4_5  },  { 0, C4_6 },  { 0, C4_7  },  { 0, C4_8 },  { 0, C4_9  },  { 0, C4_10 },  { 0, C4_11  },  { 0, C4_12 },  { 0, C4_13  },  { 0, C4_14 },                  { 0, C4_16 },
    { 0, C5_1  },  { 0, C5_2 },  { 0, C5_3  },  { 0, C5_4 },  { 0, C5_5  },  { 0, C5_6 },  { 0, C5_7  },  { 0, C5_8 },  { 0, C5_9  },  { 0, C5_10 },  { 0, C5_11  },  { 0, C5_12 },  { 0, C5_13  },  { 0, C5_14 },                  { 0, C5_16 },
    { 0, C6_1  },  { 0, C6_2 },  { 0, C6_3  },                                             { 0, C6_7  },                                              { 0, C6_11  },  { 0, C6_12 },                  { 0, C6_14 },  { 0, C6_15  },  { 0, C6_16 },
};

led_config_t g_led_config = {
{
        // Key Matrix to LED Index
    { 0,             1,             2,             3,             4,             5,             6,             7,             8,             9,            10,            11,            12,            13,            14,             15},
    {16,            17,            18,            19,            20,            21,            22,            23,            24,            25,            26,            27,            28,        NO_LED,            29,             30},
    {31,            32,            33,            34,            35,            36,            37,            38,            39,            40,            41,            42,            43,            44,        NO_LED,             45},
    {46,            47,            48,            49,            50,            51,            52,            53,            54,            55,            56,            57,            58,        NO_LED,            59,             60},
    {61,            62,            63,        NO_LED,        NO_LED,        NO_LED,            64,        NO_LED,        NO_LED,        NO_LED,            65,            66,        NO_LED,            67,            68,             69},
}, {
        //LED Index to Physical Positon
  {0, 0},     {15,  0},      {30,  0},      {45,  0},      {60,  0},      {75,  0},      {90,  0},      {105, 0},      {119, 0},      {134, 0},      {149, 0},      {164, 0},      {179, 0},      {194, 0},      {209, 0},      {224, 0},
  {0,16},     {15, 16},      {30, 16},      {45, 16},      {60, 16},      {75, 16},      {90, 16},      {105,16},      {119,16},      {134,16},      {149,16},      {164,16},      {179,16},      {209,16},                     {224,16},
  {0,32},     {15, 32},      {30, 32},      {45, 32},      {60, 32},      {75, 32},      {90, 32},      {105,32},      {119,32},      {134,32},      {149,32},      {164,32},      {179,32},      {194,32},                     {224,32},
  {0,48},     {15, 48},      {30, 48},      {45, 48},      {60, 48},      {75, 48},      {90, 48},      {105,48},      {119,48},      {134,48},      {149,48},      {164,48},      {179,48},      {209,48},                     {224,48},
  {0,64},     {15, 64},      {30, 64},                                                   {90, 64},                                                   {149,64},      {164,64},                     {194,64},      {209,64},      {224,64},
    }, {
       1,            1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,
       1,            1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,                            1,
       1,            1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,                            1,
       1,            1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,                            1,
       1,            1,             1,                                                          1,                                                          1,             1,                            1,             1,             1,
    } 
};

bool led_matrix_indicators_kb(void) {
    if (!led_matrix_indicators_user()) {
    	return false;
    }
    if (host_keyboard_led_state().caps_lock) {
        led_matrix_set_value(31, 0xFF);
    }
    return true;
}