/**
 * dp60.c
 *
  Copyright 2020 astro <yuleiz@gmail.com>
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

#ifdef RGB_MATRIX_ENABLE
const is31fl3731_led_t PROGMEM g_is31fl3731_leds[IS31FL3731_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
    {0, C1_9,   C3_10,  C4_10}, // RGB101
    {0, C1_10,  C2_10,  C4_11}, // RGB102
    {0, C1_11,  C2_11,  C3_11}, // RGB103
    {0, C1_12,  C2_12,  C3_12}, // RGB104
    {0, C1_13,  C2_13,  C3_13}, // RGB105
    {0, C1_14,  C2_14,  C3_14}, // RGB106
    {0, C1_15,  C2_15,  C3_15}, // RGB107
    {1, C5_1,   C4_1,   C6_1}, // RGB108
    {1, C1_1,   C3_2,   C4_2}, // RGB109
    {1, C1_2,   C2_2,   C4_3}, // RGB1010
    {1, C1_3,   C2_3,   C3_3}, // RGB1011
    {1, C1_4,   C2_4,   C3_4}, // RGB1012
    {1, C1_5,   C2_5,   C3_5}, // RGB1013
    {1, C1_6,   C2_6,   C3_6}, // RGB1014
    {1, C1_7,   C2_7,   C3_7}, // RGB1015-2
    {1, C1_8,   C2_8,   C3_8}, // RGB1015

    {0, C5_9,   C4_9,   C6_9}, // RGB201
    {0, C5_16,  C4_16,  C6_16}, // RGB202
    {0, C9_9,   C8_9,   C7_9}, // RGB203
    {0, C9_10,  C8_10,  C7_10}, // RGB204
    {0, C9_11,  C8_11,  C7_11}, // RGB205
    {0, C9_12,  C8_12,  C7_12}, // RGB206
    {0, C1_16,  C2_16,  C3_16}, // RGB207
    {1, C5_8,   C4_8,   C6_8}, // RGB208
    {1, C9_1,   C8_1,   C7_1}, // RGB209
    {1, C9_2,   C8_2,   C7_2}, // RGB2010
    {1, C9_3,   C8_3,   C7_3}, // RGB2011
    {1, C9_4,   C8_4,   C7_4}, // RGB2012
    {1, C9_5,   C8_5,   C7_5}, // RGB2013
    {1, C9_6,   C8_6,   C7_6}, // RGB2014

    {0, C5_1,   C4_1,   C6_1}, // RGB301
    {0, C5_8,   C4_8,   C6_8}, // RGB302
    {0, C1_1,   C3_2,   C4_2}, // RGB303
    {0, C9_13,  C8_13,  C7_13}, // RGB304
    {0, C9_14,  C8_14,  C7_14}, // RGB305
    {0, C9_15,  C8_15,  C6_14}, // RGB306
    {0, C9_16,  C7_15,  C6_15}, // RGB307
    {1, C1_9,   C3_10,  C4_10}, // RGB308
    {1, C1_10,  C2_10,  C4_11}, // RGB309
    {1, C1_11,  C2_11,  C3_11}, // RGB3010
    {1, C1_12,  C2_12,  C3_12}, // RGB3011
    {1, C1_13,  C2_13,  C3_13}, // RGB3012
    {1, C1_14,  C2_14,  C3_14}, // RGB3014
    {1, C9_7,   C8_7,   C6_6}, // RGB3013-2
    {1, C9_8,   C7_7,   C6_7}, // RGB3013

    {0, C9_1,   C8_1,   C7_1}, // RGB401-2
    {0, C9_2,   C8_2,   C7_2}, // RGB401
    {0, C9_3,   C8_3,   C7_3}, // RGB4014
    {0, C9_4,   C8_4,   C7_4}, // RGB402
    {0, C1_2,   C2_2,   C4_3}, // RGB403
    {0, C1_3,   C2_3,   C3_3}, // RGB404
    {0, C1_4,   C2_4,   C3_4}, // RGB405
    {0, C1_5,   C2_5,   C3_5}, // RGB406
    {0, C1_6,   C2_6,   C3_6}, // RGB407
    {1, C5_9,   C4_9,   C6_9}, // RGB408
    {1, C5_16,  C4_16,  C6_16}, // RGB409
    {1, C9_9,   C8_9,   C7_9}, // RGB4010
    {1, C9_10,  C8_10,  C7_10}, // RGB4011
    {1, C9_11,  C8_11,  C7_11}, // RGB4012
    {1, C1_15,  C2_15,  C3_15}, // RGB4012-2
    {1, C1_16,  C2_16,  C3_16}, // RGB4013

    {0, C9_8,   C7_7,   C6_7}, // RGB501
    {0, C9_7,   C8_7,   C6_6}, // RGB502
    {0, C9_6,   C8_6,   C7_6}, // RGB503
    {0, C9_5,   C8_5,   C7_5}, // RGBSP1
    {0, C1_8,   C2_8,   C3_8}, // RGB506-2
    {0, C1_7,   C2_7,   C3_7}, // RGB506-3
    {1, C9_12,  C8_12,  C7_12}, // RGBSP2
    {1, C9_13,  C8_13,  C7_13}, // RGB507
    {1, C9_14,  C8_14,  C7_14}, // RGB508
    {1, C9_15,  C8_15,  C6_14}, // RGB509
    {1, C9_16,  C7_15,  C6_15}  // RGB5010
};
#endif

#ifdef WEBUSB_ENABLE
#include "webusb.h"
#include "dynamic_keymap.h"


webusb_pos_t webusb_keymap[] = {
    {0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {4, 7}, {0, 7}, {0, 8}, {0, 9}, {0, 10}, {0, 11}, {0, 13},

    {1, 0}, {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6}, {1, 7}, {1, 8}, {1, 9}, {1, 10}, {1, 11}, {1, 12}, {1, 13},

    {2, 0}, {2, 1}, {2, 2}, {2, 3}, {2, 4}, {2, 5}, {2, 6}, {2, 7}, {2, 8}, {2, 9}, {2, 10}, {2, 11}, {2, 13},

    {3, 0}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {3, 6}, {3, 7}, {3, 8}, {3, 9}, {3, 10}, {3, 11}, {3, 13},

    {4, 0}, {4, 1}, {4, 2}, {4, 6}, {4, 10}, {4, 11}, {4, 12}, {4, 13},
};
#endif
