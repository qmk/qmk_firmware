/*
Copyright 2022 Stefan Sundin "4pplet" <4pplet@protonmail.com>

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
#include "rev_a.h"

#ifdef RGB_MATRIX_ENABLE
const is31fl3733_led_t PROGMEM g_is31fl3733_leds[RGB_MATRIX_LED_COUNT] = {
    { 0, K_2,  J_2,  L_2 }, //D402
    { 0, K_3,  J_3,  L_3 }, //D403
    { 0, K_4,  J_4,  L_4 }, //D404
    { 0, K_5,  J_5,  L_5 }, //D405
    { 0, K_6,  J_6,  L_6 }, //D406
    { 0, K_7,  J_7,  L_7 }, //D407
    { 0, K_8,  J_8,  L_8 }, //D408
    { 0, K_9,  J_9,  L_9 }, //D409
    { 0, K_10, J_10, L_10 }, //D410
    { 0, K_11, J_11, L_11 }, //D411
    { 0, K_12, J_12, L_12 }, //D412
    { 0, K_13, J_13, L_13 }, //D413
    { 0, K_14, J_14, L_14 }, //D414
    { 0, K_15, J_15, L_15 }, //D415
    { 0, K_1,  J_1,  L_1 }, //D401
    { 0, H_4,  G_4,  I_4 }, //D420
    { 0, H_5,  G_5,  I_5 }, //D421
    { 0, H_6,  G_6,  I_6 }, //D422
    { 0, H_7,  G_7,  I_7 }, //D423
    { 0, H_8,  G_8,  I_8 }, //D424
    { 0, H_9,  G_9,  I_9 }, //D425
    { 0, H_10, G_10, I_10 }, //D426
    { 0, H_11, G_11, I_11 }, //D427
    { 0, H_12, G_12, I_12 }, //D428
    { 0, H_13, G_13, I_13 }, //D429
    { 0, H_14, G_14, I_14 }, //D430
    { 0, H_15, G_15, I_15 }, //D431
    { 0, K_16, J_16, L_16 }, //D416
    { 0, H_2,  G_2,  I_2 }, //D418
    { 0, H_3,  G_3,  I_3 }, //D419
    { 0, E_5,  D_5,  F_5 }, //D437
    { 0, E_6,  D_6,  F_6 }, //D438
    { 0, E_7,  D_7,  F_7 }, //D439
    { 0, E_8,  D_8,  F_8 }, //D440
    { 0, E_9,  D_9,  F_9 }, //D441
    { 0, E_10, D_10, F_10 }, //D442
    { 0, E_11, D_11, F_11 }, //D443
    { 0, E_12, D_12, F_12 }, //D444
    { 0, E_13, D_13, F_13 }, //D445
    { 0, E_14, D_14, F_14 }, //D446
    { 0, H_16, G_16, I_16 }, //D432
    { 0, H_1,  G_1,  I_1 }, //D417
    { 0, E_3,  D_3,  F_3 }, //D435
    { 0, E_4,  D_4,  F_4 }, //D436
    { 0, B_2,  A_2,  C_2 }, //D450
    { 0, B_3,  A_3,  C_3 }, //D451
    { 0, B_4,  A_4,  C_4 }, //D452
    { 0, B_6,  A_6,  C_6 }, //D454
    { 0, B_8,  A_8,  C_8 }, //D456
    { 0, B_9,  A_9,  C_9 }, //D457
    { 0, B_10, A_10, C_10 }, //D458
    { 0, B_12, A_12, C_12 }, //D460
    { 0, B_13, A_13, C_13 }, //D461
    { 0, E_15, D_15, F_15 }, //D447
    { 0, E_1,  D_1,  F_1 }, //D433
    { 0, E_2,  D_2,  F_2 }, //D434
    { 0, B_1,  A_1,  C_1 }, //D449
    { 0, B_7,  A_7,  C_7 }, //D455
    { 0, B_11, A_11, C_11 }, //D459
    { 0, B_14, A_14, C_14 }, //D462
    { 0, B_15,  A_15,  C_15 }, //D463
    { 0, B_16,  A_16,  C_16 } //D464
};

led_config_t g_led_config = {
    {
    #define XXX NO_LED

    {   0,   2,   4,   6,   8,  10,  12 },
    {   1,   3,   5,   7,   9,  11, XXX },
    {  14,  16,  18,  20,  22,  24,  26 },
    {  15,  17,  19,  21,  23,  25,  13 },
    {  28,  30,  32,  34,  36,  38,  40 },
    {  29,  31,  33,  35,  37,  39, XXX },
    {  41,  43,  45,  47,  49,  51, XXX },
    {  42,  44,  46,  48,  50,  52,  27 },
    {  54,  55, XXX,  57, XXX,  60,  53 },
    {  56, XXX, XXX,  58,  59,  61, XXX },

    }, {
    {  0,0  }, { 16,0  }, { 32,0  }, { 48,0  }, { 65,0  }, { 81,0  }, { 97,0  }, {113,0  }, {129,0  }, {145,0  },
    {161,0  }, {178,0  }, {194,0  }, {218,0  }, {  4,16 }, { 24,16 }, { 40,16 }, { 57,16 }, { 73,16 }, { 89,16 },
    {105,16 }, {121,16 }, {137,16 }, {153,16 }, {170,16 }, {186,16 }, {202,16 }, {224,24 }, {  6,32 }, { 28,32 },
    { 44,32 }, { 61,32 }, { 77,32 }, { 93,32 }, {109,32 }, {125,32 }, {141,32 }, {157,32 }, {174,32 }, {190,32 },
    {206,32 }, {  2,48 }, { 20,48 }, { 36,48 }, { 52,48 }, { 69,48 }, { 85,48 }, {101,48 }, {117,48 }, {133,48 },
    {149,48 }, {165,48 }, {182,48 }, {212,48 }, {  2,64 }, { 22,64 }, { 42,64 }, {103,64 }, {163,64 }, {184,64 },
    {204,64 }, {224,64 },
    }, {
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
        8, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
        1, 1, 1, 4, 1, 1, 1, 1
    }
};

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) {
        return false;
    }

    if (host_keyboard_led_state().caps_lock && CAPS_LOCK_ENABLE) {
        for (uint8_t i = led_min; i <= led_max; i++) {
            if (g_led_config.flags[i] & CAPS_LED_GROUP) {
                rgb_matrix_set_color(i, CAPS_LOCK_COLOR);
            }
        }
    }

    return true;
}
#endif
