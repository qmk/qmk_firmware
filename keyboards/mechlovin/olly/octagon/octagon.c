/* Copyright 2022 Team Mechlovin
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

const is31_led PROGMEM g_is31_leds[LED_MATRIX_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *    driver
 *    |  LED address
 *    |  | */
    { 0, C1_1  },  { 0, C1_2 },  { 0, C1_3  },  { 0, C1_4 },  { 0, C1_5  },  { 0, C1_6 },  { 0, C1_7  },  { 0, C1_8 },  { 0, C1_9  },  { 0, C1_10 },  { 0, C1_11  },  { 0, C1_12 },  { 0, C1_13  },  { 0, C1_14 },  { 0, C1_15  },  { 0, C1_16 },
    { 0, C2_1  },  { 0, C2_2 },  { 0, C2_3  },  { 0, C2_4 },  { 0, C2_5  },  { 0, C2_6 },  { 0, C2_7  },  { 0, C2_8 },  { 0, C2_9  },  { 0, C2_10 },  { 0, C2_11  },  { 0, C2_12 },  { 0, C2_13  },  { 0, C2_14 },  { 0, C2_15  },  { 0, C2_16 },
    { 0, C3_1  },  { 0, C3_2 },  { 0, C3_3  },  { 0, C3_4 },  { 0, C3_5  },  { 0, C3_6 },  { 0, C3_7  },  { 0, C3_8 },  { 0, C3_9  },  { 0, C3_10 },  { 0, C3_11  },  { 0, C3_12 },  { 0, C3_13  },  { 0, C3_14 },                  { 0, C3_16 },
    { 0, C4_1  },  { 0, C4_2 },  { 0, C4_3  },  { 0, C4_4 },  { 0, C4_5  },  { 0, C4_6 },  { 0, C4_7  },  { 0, C4_8 },  { 0, C4_9  },  { 0, C4_10 },  { 0, C4_11  },  { 0, C4_12 },  { 0, C4_13  },  { 0, C4_14 },                  { 0, C4_16 },
    { 0, C5_1  },  { 0, C5_2 },  { 0, C5_3  },  { 0, C5_4 },  { 0, C5_5  },  { 0, C5_6 },  { 0, C5_7  },  { 0, C5_8 },  { 0, C5_9  },  { 0, C5_10 },  { 0, C5_11  },  { 0, C5_12 },  { 0, C5_13  },  { 0, C5_14 },                  { 0, C5_16 },
    { 0, C6_1  },  { 0, C6_2 },  { 0, C6_3  },                                             { 0, C6_7  },                                              { 0, C6_11  },  { 0, C6_12 },  { 0, C6_13  },  { 0, C6_14 },  { 0, C6_15  },  { 0, C6_16 },
    { 0, C3_15 },  { 0, C4_15 }, { 0, C5_15 },  // Lock Indicator
    { 0, C7_13 },  { 0, C7_14 }, { 0, C7_15 }, { 0, C7_16 }, // Layer Indicator
};

led_config_t g_led_config = {
{
        // Key Matrix to LED Index
    { 0,             1,             2,             3,             4,             5,             6,             7,             8,             9,            10,            11,            12,            13,            14,             15},
    {16,            17,            18,            19,            20,            21,            22,            23,            24,            25,            26,            27,            28,            29,            30,             31},
    {32,            33,            34,            35,            36,            37,            38,            39,            40,            41,            42,            43,            44,            45,                            46},
    {47,            48,            49,            50,            51,            52,            53,            54,            55,            56,            57,            58,            59,            60,                            61},
    {62,            63,            64,            65,            66,            67,            68,            69,            70,            71,            72,            73,            74,            75,                            76},
    {77,            78,            79,                                                         80,                                                         81,            82,            83,            84,            85,             86},
}, {
        //LED Index to Physical Positon
  {0, 0},     {15,  0},      {30,  0},      {45,  0},      {60,  0},      {75,  0},      {90,  0},      {105, 0},      {119, 0},      {134, 0},      {149, 0},      {164, 0},      {179, 0},      {194, 0},      {209, 0},      {224, 0},
  {0,13},     {15, 13},      {30, 13},      {45, 13},      {60, 13},      {75, 13},      {90, 13},      {105,13},      {119,13},      {134,13},      {149,13},      {164,13},      {179,13},      {194,13},      {209,13},      {224,13},
  {0,26},     {15, 26},      {30, 26},      {45, 26},      {60, 26},      {75, 26},      {90, 26},      {105,26},      {119,26},      {134,26},      {149,26},      {164,26},      {179,26},      {194,26},                     {224,26},
  {0,38},     {15, 38},      {30, 38},      {45, 38},      {60, 38},      {75, 38},      {90, 38},      {105,38},      {119,38},      {134,38},      {149,38},      {164,38},      {179,38},      {194,38},                     {224,38},
  {0,51},     {15, 51},      {30, 51},      {45, 51},      {60, 51},      {75, 51},      {90, 51},      {105,51},      {119,51},      {134,51},      {149,51},      {164,51},      {179,51},      {194,51},                     {224,51},
  {0,64},     {15, 64},      {30, 64},                                                   {90, 64},                                                   {149,64},      {164,64},      {179,64},      {194,64},      {209,64},      {224,64},
    }, {
       1,            1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,
       1,            1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,
       1,            1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,                            1,
       1,            1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,                            1,
       1,            1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,                            1,
       1,            1,             1,                                                          1,                                                          1,             1,             1,             1,             1,             1,
    } 
};


bool led_matrix_indicators_kb(void) {
    if (!led_matrix_indicators_user()) { return false; }
    if (host_keyboard_led_state().caps_lock) {
        led_matrix_set_value(87, 0xFF);
        led_matrix_set_value(47, 0xFF);
    } else {
        led_matrix_set_value(87, 0x00);
    }
    if (host_keyboard_led_state().num_lock) {
        led_matrix_set_value(88, 0xFF);
    } else {
        led_matrix_set_value(88, 0x00);
    }
    if (host_keyboard_led_state().scroll_lock) {
        led_matrix_set_value(89, 0xFF);
    } else {
        led_matrix_set_value(89, 0x00);
    }
    return true;
}


layer_state_t layer_state_set_kb(layer_state_t state) {
  // if on layer 1, turn on L1 LED, otherwise off.
    if (get_highest_layer(state) == 0) {
        led_matrix_set_value(90, 0xFF);
    } else {
        led_matrix_set_value(90, 0x00);
    }
  // if on layer 2, turn on L2 LED, otherwise off.
    if (get_highest_layer(state) == 1) {
        led_matrix_set_value(91, 0xFF);
    } else {
        led_matrix_set_value(91, 0x00);
    }

  // if on layer 3, turn on L3 LED, otherwise off.
    if (get_highest_layer(state) == 2) {
        led_matrix_set_value(92, 0xFF);
    } else {
        led_matrix_set_value(92, 0x00);
    }

  // if on layer 4, turn on L4 LED, otherwise off.
    if (get_highest_layer(state) == 3) {
        led_matrix_set_value(93, 0xFF);
    } else {
        led_matrix_set_value(93, 0x00);
    }
    return layer_state_set_user(state);
}