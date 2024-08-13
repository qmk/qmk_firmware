#include "quantum.h"

const is31fl3731_led_t PROGMEM g_is31fl3731_leds[IS31FL3731_LED_COUNT] = {
    /* Refer to IS31 manual for these locations
     *   driver
     *   |  R location
     *   |  |       G location
     *   |  |       |       B location
     *   |  |       |       | */
    {0, C1_10, C2_10, C4_11}, // RGB101
    {0, C1_11, C2_11, C3_11}, // RGB102
    {0, C1_12, C2_12, C3_12}, // RGB103
    {0, C1_13, C2_13, C3_13}, // RGB104
    {0, C1_14, C2_14, C3_14}, // RGB105
    {0, C1_15, C2_15, C3_15}, // RGB106
    {0, C1_16, C2_16, C3_16}, // RGB107
    {1, C1_1, C3_2, C4_2},    // RGB108
    {1, C1_2, C2_2, C4_3},    // RGB109
    {1, C1_3, C2_3, C3_3},    // RGB1010
    {1, C1_4, C2_4, C3_4},    // RGB1011
    {1, C1_5, C2_5, C3_5},    // RGB1012
    {1, C1_6, C2_6, C3_6},    // RGB1013
    {1, C1_7, C2_7, C3_7},    // RGB1015
    {1, C1_8, C2_8, C3_8},    // RGB1016
};