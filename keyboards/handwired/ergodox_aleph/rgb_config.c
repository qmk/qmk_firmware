#ifdef RGB_MATRIX_ENABLE

#include "rgb_config.h"

const is31_led g_is31_leds[DRIVER_LED_TOTAL] = {
   /* Refer to IS31 manual for these locations
    *   driver
    *   |  R location
    *   |  |       G location
    *   |  |       |       B location
    *   |  |       |       | */
       {0, G_2,    H_2,    I_2}, // LED1
       {0, D_2,    E_2,    F_2}, // LED2
       {0, A_2,    B_2,    C_2}, // LED3
       {0, J_1,    K_1,    L_1}, // LED4
       {0, G_1,    H_1,    I_1}, // LED5
       {0, D_1,    E_1,    F_1}, // LED6
       {0, A_1,    B_1,    C_1}, // LED7
       {0, G_4,    H_4,    I_4}, // LED8
       {0, D_4,    E_4,    F_4}, // LED9
       {0, A_4,    B_4,    C_4}, // LED10
       {0, J_3,    K_3,    L_3}, // LED11
       {0, G_3,    H_3,    I_3}, // LED12
       {0, D_3,    E_3,    F_3}, // LED13
       {0, A_3,    B_3,    C_3}, // LED14
       {0, D_6,    E_6,    F_6}, // LED15
       {0, A_6,    B_6,    C_6}, // LED16
       {0, J_5,    K_5,    L_5}, // LED17
       {0, G_5,    H_5,    I_5}, // LED18
       {0, D_5,    E_5,    F_5}, // LED19
       {0, A_5,    B_5,    C_5}, // LED20
       {0, D_9,    E_9,    F_9}, // LED21
       {0, A_9,    B_9,    C_9}, // LED22
       {0, G_8,    H_8,    I_8}, // LED23
       {0, D_8,    E_8,    F_8}, // LED24
       {0, A_8,    B_8,    C_8}, // LED25
       {0, J_7,    K_7,    L_7}, // LED26
       {0, G_7,    H_7,    I_7}, // LED27
       {0, D_7,    E_7,    F_7}, // LED28
       {0, A_7,    B_7,    C_7}, // LED29
       {0, G_9,    H_9,    I_9}, // LED30
       {0, G_11,   H_11,   I_11}, // LED31
       {0, D_11,   E_11,   F_11}, // LED32
       {0, A_11,   B_11,   C_11}, // LED33
       {0, J_11,   K_11,   L_11}, // LED34
       {0, J_10,   K_10,   L_10}, // LED35
       {0, G_10,   H_10,   I_10}, // LED36
       {0, D_10,   E_10,   F_10}, // LED37
       {0, A_10,   B_10,   C_10}  // LED38
};

led_config_t g_led_config = { {
    // Left side
    {NO_LED, NO_LED, NO_LED, 21, 30},
    {NO_LED, NO_LED, NO_LED, 22, 31},
    {     1,      8, NO_LED, 23, 32},
    {     2,      9,     15, 24, 33},
    {     3,     10,     16, 25, 34},
    {     4,     11,     17, 26, 35},
    {     5,     12,     18, 27, 36},
    {     6,     13,     19, 28, 37},
    {     7,     14,     20, 29, 38},

    // TODO(stillinbeta): right hand
    {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
    {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
    {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
    {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
    {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
    {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
    {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
    {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
    {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
  },
  {
   {0, 6}, {24, 6}, {39, 2}, {55, 0}, {71, 2}, {87, 4}, {102, 4},
   {0, 22}, {24, 22}, {39, 18}, {55, 16}, {71, 18}, {87, 20}, {102, 20},
   {0, 37}, {24, 37}, {39, 33}, {55, 31}, {71, 33}, {87, 35},
   {0, 53}, {24, 53}, {39, 49}, {55, 47}, {71, 49}, {87, 51}, {102, 43}, {8, 69},
   {24, 69}, {39, 65}, {55, 63}, {71, 65}, {94, 79}, {110, 79}, {110, 94}, {79, 94},
  },
  {
    FLG, FLG, FLG, FLG, FLG, FLG, FLG,
    FLG, FLG, FLG, FLG, FLG, FLG, FLG,
    FLG, FLG, FLG, FLG, FLG, FLG,
    FLG, FLG, FLG, FLG, FLG, FLG, FLG, FLG,
    FLG, FLG, FLG, FLG, FLG, FLG, FLG, FLG
  }
};

#endif
