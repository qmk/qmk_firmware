/* Copyright 2017 Jason Williams (Wilba)
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

#include <quantum.h>
#include <i2c_master.h>
#include <led_tables.h>
#include <rgb_matrix.h>
#include "drivers/led/issi/is31fl3731.h"
#include "ws2812.h"
#include "rev1_qmk.h"

#ifdef RGB_MATRIX_ENABLE
LED_TYPE rgb_matrix_ws2812_array[WS2812_LED_TOTAL];

const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |      G location
 *   |  |      |      B location
 *   |  |      |      | */
    {0, C1_1,   C3_2,   C4_2}, //A1
    {0, C1_2,   C2_2,   C4_3}, //A2
    {0, C1_3,   C2_3,   C3_3}, //A3
    {0, C1_4,   C2_4,   C3_4}, //A4
    {0, C1_5,   C2_5,   C3_5}, //A5
    {0, C1_6,   C2_6,   C3_6}, //A6
    {0, C1_7,   C2_7,   C3_7}, //A7
    {0, C1_8,   C2_8,   C3_8}, //A8
    {0, C9_1,   C8_1,   C7_1}, //A9
    {0, C9_2,   C8_2,   C7_2}, //A10
    {0, C9_3,   C8_3,   C7_3}, //A11
    {0, C9_4,   C8_4,   C7_4}, //A12
    {0, C9_5,   C8_5,   C7_5}, //A13
    {0, C9_6,   C8_6,   C7_6}, //A14
    {0, C9_7,   C8_7,   C6_6}, //A15
    {0, C9_8,   C7_7,   C6_7}, //A16

    {0, C1_9,   C3_10,  C4_10}, //B1
    {0, C1_10,  C2_10,  C4_11}, //B2
    {0, C1_11,  C2_11,  C3_11}, //B3
    {0, C1_12,  C2_12,  C3_12}, //B4
    {0, C1_13,  C2_13,  C3_13}, //B5
    {0, C1_14,  C2_14,  C3_14}, //B6
    {0, C1_15,  C2_15,  C3_15}, //B7
    {0, C1_16,  C2_16,  C3_16}, //B8
    {0, C9_9,   C8_9,   C7_9},  //B9
    {0, C9_10,  C8_10,  C7_10}, //B10
    {0, C9_11,  C8_11,  C7_11}, //B11
    {0, C9_12,  C8_12,  C7_12}, //B12
    {0, C9_13,  C8_13,  C7_13}, //B13
    {0, C9_14,  C8_14,  C7_14}, //B14
    {0, C9_15,  C8_15,  C6_14}, //B15
    {0, C9_16,  C7_15,  C6_15}, //B16

    {1, C1_1,   C3_2,   C4_2}, //C1
    {1, C1_2,   C2_2,   C4_3}, //C2
    {1, C1_3,   C2_3,   C3_3}, //C3
    {1, C1_4,   C2_4,   C3_4}, //C4
    {1, C1_5,   C2_5,   C3_5}, //C5
    {1, C1_6,   C2_6,   C3_6}, //C6
    {1, C1_7,   C2_7,   C3_7}, //C7
    {1, C1_8,   C2_8,   C3_8}, //C8
    {1, C9_1,   C8_1,   C7_1}, //C9
    {1, C9_2,   C8_2,   C7_2}, //C10
    {1, C9_3,   C8_3,   C7_3}, //C11
    {1, C9_4,   C8_4,   C7_4}, //C12
    {1, C9_5,   C8_5,   C7_5}, //C13
    {1, C9_6,   C8_6,   C7_6}, //C14
    {1, C9_7,   C8_7,   C6_6}, //C15
    {1, C9_8,   C7_7,   C6_7}, //C16

    {1, C1_9,   C3_10,  C4_10}, //D1
    {1, C1_10,  C2_10,  C4_11}, //D2
    {1, C1_11,  C2_11,  C3_11}, //D3
    {1, C1_12,  C2_12,  C3_12}, //D4
    {1, C1_13,  C2_13,  C3_13}, //D5
    {1, C1_14,  C2_14,  C3_14}, //D6
    {1, C1_15,  C2_15,  C3_15}, //D7
    {1, C1_16,  C2_16,  C3_16}, //D8
    {1, C9_9,    C8_9,   C7_9},  //D9
    {1, C9_10,  C8_10,  C7_10}, //D10
    {1, C9_11,  C8_11,  C7_11}, //D11
    {1, C9_12,  C8_12,  C7_12}, //D12
    {1, C9_13,  C8_13,  C7_13}, //D13
    {1, C9_14,  C8_14,  C7_14}, //D14
    {1, C9_15,  C8_15,  C6_14}, //D15
    {1, C9_16,  C7_15,  C6_15}, //D16

    //fake underglows 1- 20
    {2, 0, 0, 0},
    {2, 0, 0, 0},
    {2, 0, 0, 0},
    {2, 0, 0, 0},
    {2, 0, 0, 0},
    {2, 0, 0, 0},
    {2, 0, 0, 0},
    {2, 0, 0, 0},
    {2, 0, 0, 0},
    {2, 0, 0, 0},
    {2, 0, 0, 0},
    {2, 0, 0, 0},
    {2, 0, 0, 0},
    {2, 0, 0, 0},
    {2, 0, 0, 0},
    {2, 0, 0, 0},
    {2, 0, 0, 0},
    {2, 0, 0, 0},
    {2, 0, 0, 0},
    {2, 0, 0, 0}
};

__attribute__ ((weak))
led_config_t g_led_config = { {
    { 15, 14, 13,     12,     11, 10,      9,      8,     16, 17,     18, 19, 20, 21 },
    {  6,  5,  4,      3,      2,  1,      0,     24,     25, 26,     27, 28, 29, 30 },
    {  7, 45, 44,     43,     42, 41,     40,     48,     49, 50,     51, 52, 23, 22 },
    { 46, 36, 35,     34,     33, 32,     56,     57,     58, 59, NO_LED, 53, 54, 31 },
    { 47, 39, 38, NO_LED, NO_LED, 37, NO_LED, NO_LED, NO_LED, 60,     61, 62, 63, 55 }
}, {
    // LA1..LA16
    {104, 16}, {88 , 16}, {72 , 16}, {56 , 16}, {40 , 16}, {24 , 16}, {4  , 16}, {6  , 32},
    {112,  0}, {96 ,  0}, {80 ,  0}, {64 ,  0}, {48 ,  0}, {32 ,  0}, {16 ,  0}, {0  ,  0},

    // LB1..LB16
    {128,  0}, {144,  0}, {160,  0}, {176,  0}, {192,  0}, {208,  0}, {224,  0}, {214, 32},
    {120, 16}, {136, 16}, {152, 16}, {168, 16}, {184, 16}, {200, 16}, {220, 16}, {224, 48},

    // LC1..LC16
    {100, 48}, {84 , 48}, {68 , 48}, {52 , 48}, {36 , 48}, {102, 64}, {42 , 64}, {22 , 64},
    {108, 32}, {92 , 32}, {76 , 32}, {60 , 32}, {44 , 32}, {28 , 32}, {10 , 48}, {2  , 64},

    // LD1..LD16
    {124, 32}, {140, 32}, {156, 32}, {172, 32}, {188, 32}, {180, 48}, {202, 48}, {224, 64},
    {116, 48}, {132, 48}, {148, 48}, {164, 48}, {160, 64},  {176, 64}, {192, 64}, {208, 64},

    //RGB UNDERGLOW
    {27 , 3}, {64 , 3}, {100, 3}, {137, 3}, {173, 3}, {209, 3}, {242, 4}, {255, 8}, {255,32}, {255,64},
    {241,64}, {212,64}, {173,64}, {137,64}, {100,64}, {63 ,64}, {28 ,64}, {0  ,64}, {0  ,32}, {0  , 8} //20
}, {
    4, 4, 4, 4, 4, 4, 1, 1,
    4, 4, 4, 4, 4, 4, 4, 1,
    4, 4, 4, 4, 4, 4, 1, 1,
    4, 4, 4, 4, 4, 4, 1, 1,
    4, 4, 4, 4, 4, 4, 1, 1,
    4, 4, 4, 4, 4, 4, 1, 1,
    4, 4, 4, 4, 4, 1, 1, 1,
    4, 4, 4, 4, 1, 1, 1, 4,

    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3
} };

//Custom Driver
static void init(void) {
    i2c_init();
    IS31FL3731_init(DRIVER_ADDR_1);
    IS31FL3731_init(DRIVER_ADDR_2);
    for (int index = 0; index < ISSI_DRIVER_TOTAL; index++) {
        bool enabled = true;
        IS31FL3731_set_led_control_register(index, enabled, enabled, enabled);
    }
    IS31FL3731_update_led_control_registers(DRIVER_ADDR_1, 0);
    IS31FL3731_update_led_control_registers(DRIVER_ADDR_2, 1);
    
    //RGB Underglow ws2812
    
}

static void flush(void) {
    IS31FL3731_update_pwm_buffers(DRIVER_ADDR_1, 0);
    IS31FL3731_update_pwm_buffers(DRIVER_ADDR_2, 1);
    ws2812_setleds(rgb_matrix_ws2812_array, WS2812_LED_TOTAL);
}

static void set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    if (index < ISSI_DRIVER_TOTAL) {
        IS31FL3731_set_color(index, red, green, blue);
    } else {
        rgb_matrix_ws2812_array[index - ISSI_DRIVER_TOTAL].r = red;
        rgb_matrix_ws2812_array[index - ISSI_DRIVER_TOTAL].g = green;
        rgb_matrix_ws2812_array[index - ISSI_DRIVER_TOTAL].b = blue;
    }
}

static void set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
    IS31FL3731_set_color_all( red, green, blue );
    for (uint8_t i = 0; i < WS2812_LED_TOTAL; i++) {
        rgb_matrix_ws2812_array[i].r = red;
        rgb_matrix_ws2812_array[i].g = green;
        rgb_matrix_ws2812_array[i].b = blue;
    }
}


const rgb_matrix_driver_t rgb_matrix_driver = {
    .init = init,
    .flush = flush,
    .set_color = set_color,
    .set_color_all = set_color_all
};

#endif
