#include "orthograph.h"

const is31_led g_is31_leds[DRIVER_LED_TOTAL] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
    {0, B_6,    C_6,    D_6},
    {0, B_13,   C_13,   D_13},

    {0, E_6,    F_6,    G_6},
    {0, E_13,   F_13,   G_13},

    {0, H_6,    I_6,    A_6},
    {0, H_13,   I_13,   A_13}

    
    
};

led_config_t g_led_config = { {
    {   0,   1,   2,   3,   4,   5 }
}, {
    {   0,   0 }, {  20,   0 }, {  40,   0 }, {  61,   0 }, {  81,   0 }, { 101,   0 }
}, {
    1, 4, 4, 4, 4, 1
} };
