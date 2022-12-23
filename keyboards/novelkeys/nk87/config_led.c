/* Copyright 2022 Kirill Malgichev (@makirill)
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
#include "config_led.h"
#include "quantum.h"

#include "indicator.h"


#ifdef RGB_MATRIX_ENABLE


const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |      G location
 *   |  |      |      B location
 *   |  |      |      | */
    {0, B_1,   A_1,   C_1},  // 0  LA1
    {0, E_1,   D_1,   F_1},  // 1  LA2
    {0, H_1,   G_1,   I_1},  // 2  LA3
    {0, K_1,   J_1,   L_1},  // 3  LA4
    {0, B_2,   A_2,   C_2},  // 4  LA5
    {0, E_2,   D_2,   F_2},  // 5  LA6
    {0, H_2,   G_2,   I_2},  // 6  LA7
    {0, K_2,   J_2,   L_2},  // 7  LA8
    {0, B_3,   A_3,   C_3},  // 8  LA9
    {0, E_3,   D_3,   F_3},  // 9  LA10
    {0, H_3,   G_3,   I_3},  // 10 LA11
    {0, K_3,   J_3,   L_3},  // 11 LA12
    {0, B_4,   A_4,   C_4},  // 12 LA13
    {0, E_4,   D_4,   F_4},  // 13 LA14
    {0, H_4,   G_4,   I_4},  // 14 LA15
    {0, K_4,   J_4,   L_4},  // 15 LA16
    {0, B_5,   A_5,   C_5},  // 16 LA17
    {0, E_5,   D_5,   F_5},  // 17 LA18
    {0, H_5,   G_5,   I_5},  // 18 LA19
    {0, K_5,   J_5,   L_5},  // 19 LA20
    {0, B_6,   A_6,   C_6},  // 20 LA21
    {0, E_6,   D_6,   F_6},  // 21 LA22
    {0, H_6,   G_6,   I_6},  // 22 LA23
    {0, K_6,   J_6,   L_6},  // 23 LA24
    {0, B_7,   A_7,   C_7},  // 24 LA25
    {0, E_7,   D_7,   F_7},  // 25 LA26
    {0, H_7,   G_7,   I_7},  // 26 LA27
    {0, K_7,   J_7,   L_7},  // 27 LA28
    {0, B_8,   A_8,   C_8},  // 28 LA29
    {0, E_8,   D_8,   F_8},  // 29 LA30
    {0, H_8,   G_8,   I_8},  // 30 LA31
    {0, K_8,   J_8,   L_8},  // 31 LA32
    {0, B_9,   A_9,   C_9},  // 32 LA33
    {0, E_9,   D_9,   F_9},  // 33 LA34
    {0, H_9,   G_9,   I_9},  // 34 LA35
    {0, K_9,   J_9,   L_9},  // 35 LA36
    {0, B_10,  A_10,  C_10}, // 36 LA37
    {0, E_10,  D_10,  F_10}, // 37 LA38
    {0, H_10,  G_10,  I_10}, // 38 LA39
    {0, K_10,  J_10,  L_10}, // 39 LA40
    {0, B_11,  A_11,  C_11}, // 40 LA41
    {0, E_11,  D_11,  F_11}, // 41 LA42
    {0, H_11,  G_11,  I_11}, // 42 LA43
    {0, K_11,  J_11,  L_11}, // 43 LA44
    {0, B_12,  A_12,  C_12}, // 44 LA45
    {0, E_12,  D_12,  F_12}, // 45 LA46
    {0, H_12,  G_12,  I_12}, // 46 LA47
    {0, K_12,  J_12,  L_12}, // 47 LA48
    {0, B_13,  A_13,  C_13}, // 48 LA49
    {0, E_13,  D_13,  F_13}, // 49 LA50
    {0, H_13,  G_13,  I_13}, // 50 LA51
    {0, K_13,  J_13,  L_13}, // 51 LA52
    {0, B_14,  A_14,  C_14}, // 52 LA53
    {0, E_14,  D_14,  F_14}, // 53 LA54
    {0, H_14,  G_14,  I_14}, // 54 LA55
    {0, K_14,  J_14,  L_14}, // 55 LA56
    {0, B_15,  A_15,  C_15}, // 56 LA57
    {0, E_15,  D_15,  F_15}, // 57 LA58
    {0, H_15,  G_15,  I_15}, // 58 LA59
    {0, K_15,  J_15,  L_15}, // 59 LA60
    {0, E_16,  D_16,  F_16}, // 60 LA62
    {0, H_16,  G_16,  I_16}, // 61 LA63
    {0, K_16,  J_16,  L_16}, // 62 LA64
    {1, B_1,   A_1,   C_1},  // 63 LB1
    {1, B_2,   A_2,   C_2},  // 64 LB5
    {1, B_3,   A_3,   C_3},  // 65 LB9
    {1, K_3,   J_3,   L_3},  // 66 LB12
    {1, B_4,   A_4,   C_4},  // 67 LB13
    {1, B_5,   A_5,   C_5},  // 68 LB17
    {1, B_6,   A_6,   C_6},  // 69 LB21
    {1, B_7,   A_7,   C_7},  // 70 LB25
    {1, B_8,   A_8,   C_8},  // 71 LB29
    {1, B_9,   A_9,   C_9},  // 71 LB33
    {1, B_10,  A_10,  C_10}, // 73 LB37
    {1, B_11,  A_11,  C_11}, // 74 LB41
    {1, B_12,  A_12,  C_12}, // 75 LB45
    {1, B_13,  A_13,  C_13}, // 76 LB49
    {1, H_13,  G_13,  I_13}, // 77 LB51
    {1, K_13,  J_13,  L_13}, // 78 LB52
    {1, B_14,  A_14,  C_14}, // 79 LB53
    {1, H_14,  G_14,  I_14}, // 80 LB55
    {1, K_14,  J_14,  L_14}, // 81 LB56
    {1, B_15,  A_15,  C_15}, // 82 LB57
    {1, H_15,  G_15,  I_15}, // 83 LB59
    {1, K_15,  J_15,  L_15}, // 84 LB60
    {1, B_16,  A_16,  C_16}, // 85 LB61
    {1, K_16,  J_16,  L_16}, // 86 LB64
    {1, H_16,  G_16,  I_16}, // 87 LB63
    {1, K_12,  J_12,  L_12} // 88 LB48
};

//   1     2     3      4     5     6     7     8     9    10    11    12    13    14    15    16    17      Indicators
// LB1,  LB5,  LB9,  LB13, LB17, LB21, LB25, LB29, LB33, LB37, LB41, LB45, LB49, LB53, LB57, LB61, LB64,   1 (LB63 Blue channel)
// LA1,  LA5,  LA9,  LA13, LA17, LA21, LA25, LA29, LA33, LA37, LA41, LA45, LA49, LA53, LB52, LB56, LB60,   2 (LB63 Red/Green channel)
// LA2,  LA6,  LA10, LA14, LA18, LA22, LA26, LA30, LA34, LA38, LA42, LA46, LA50,  ---, LB51, LB55, LB59,   3 (LB48 Blue channel)
// LA3,  LA7,  LA11, LA15, LA19, LA23, LA27, LA31, LA35, LA39, LA43, LA47, LA54, LA55,  ---,  ---,  ---,   4
// LA4,  ---,   LA8, LA12, LA16, LA20, LA24, LA28, LA32, LA36, LA40, LA44, LA51,  ---,  ---, LA52,  ---,   5
// LA57, LA58, LA59,  ---,  ---,  ---, LA60,  ---,  ---,  ---,  ---, LA62, LA63, LA64, LA48, LA56, LB12    6
led_config_t g_led_config = { {
    {     63,     64,      65,      67,      68,      69,      70,      71,      72,      73,      74,      75,      76,      79,      82,      85,      86 },
    {      0,      4,       8,      12,      16,      20,      24,      28,      32,      36,      40,      44,      48,      52,      78,      81,      84 },
    {      1,      5,       9,      13,      17,      21,      25,      29,      33,      37,      41,      45,      49,  NO_LED,      77,      80,      83 },
    {      2,      6,      10,      14,      18,      22,      26,      30,      34,      38,      42,      46,      53,      54,  NO_LED,  NO_LED,  NO_LED },
    {      3, NO_LED,       7,      11,      15,      19,      23,      27,      31,      35,      39,      43,      50,  NO_LED,  NO_LED,      51,  NO_LED },
    {     56,     57,      58,  NO_LED,  NO_LED,  NO_LED,      59,  NO_LED,  NO_LED,  NO_LED,  NO_LED,      60,      61,      62,      47,      55,      66 },
}, {
    {   0, 12 }, {   0, 25 }, {   0, 38 }, {   0, 51 }, {  14, 12 }, {  14, 25 }, {  14, 38 }, { 28,  51 }, {  28, 12 }, {  28, 25 },
    {  28, 38 }, {  42, 51 }, {  42, 12 }, {  42, 25 }, {  42, 38 }, {  56, 51 }, {  56, 12 }, { 56,  25 }, {  56, 38 }, {  70, 51 },
    {  70, 12 }, {  70, 25 }, {  70, 38 }, {  84, 51 }, {  84, 12 }, {  84, 25 }, {  84, 38 }, { 98,  51 }, {  98, 12 }, {  98, 25 },
    {  98, 38 }, { 112, 51 }, { 112, 12 }, { 112, 25 }, { 112, 38 }, { 126, 51 }, { 126, 12 }, { 126, 25 }, { 126, 38 }, { 140, 51 },
    { 140, 12 }, { 140, 25 }, { 140, 38 }, { 154, 51 }, { 154, 12 }, { 154, 25 }, { 154, 38 }, { 196, 64 }, { 168, 12 }, { 168, 25 },
    { 168, 51 }, { 210, 51 }, { 182, 12 }, { 168, 38 }, { 182, 38 }, { 210, 64 }, {   0, 64 }, {  14, 64 }, {  28, 64 }, {  84, 64 },
    { 154, 64 }, { 168, 64 }, { 182, 64 }, {   0,  0 }, { 14,   0 }, {  28,  0 }, { 224, 64 }, {  42,  0 }, {  56,  0 }, {  70,  0 },
    {  84,  0 }, {  98,  0 }, { 112,  0 }, { 126,  0 }, { 140,  0 }, { 154,  0 }, { 168,  0 }, { 196, 25 }, { 196,  0 }, { 182,  0 },
    { 210, 25 }, { 210, 12 }, { 196,  0 }, { 224, 25 }, { 224, 12 }, { 210,  0 }, { 224,  0 }, { 224,  0 }, { 224,  0 }
}, {
    4, 4, 4, 1, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    1, 4, 4, 4, 4, 4, 1, 1, 1, 4,
    1, 1, 1, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 8, 8
} };


/* Indicator LEDS are part of the LED driver
 * Top LED is blue only. LED driver 2 RGB 63 Blue channel
 * Middle LED is blue and red. LED driver 2 RGB 63 Red and Green channel
 * Bottom LED is red only LED driver 2 RGB 48 Blue channel.
 */
void indicators_update(uint8_t caps, uint8_t fn1, uint8_t fn2) {
    rgb_matrix_set_color(87, fn1, fn1, caps);
    rgb_matrix_set_color(88, 0, 0, fn2);
}

#endif // RGB_MATRIX_ENABLE