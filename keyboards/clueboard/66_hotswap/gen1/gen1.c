/* Copyright 2017 Clueboard <info@clueboard.co>
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
#include "gen1.h"
#include "is31fl3731-simple.h"

void matrix_init_kb(void) {
}

void matrix_scan_kb(void) {
}

#ifdef LED_MATRIX_ENABLE
const is31_led g_is31_leds[LED_DRIVER_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *  driver
 *  |   LED address
 *  |   | */
    {0, C1_1},  // k00  KC_GESC
    {0, C1_2},  // k01 KC_1
    {0, C1_3},  // k02 KC_2
    {0, C1_4},  // k03 KC_3
    {0, C1_5},  // k04 KC_4
    {0, C1_6},  // k05 KC_5
    {0, C1_7},  // k06 KC_6
    {0, C1_8},  // k07 KC_7
    {0, C1_9},  // k50 KC_8
    {0, C1_10}, // k51 KC_9
    {0, C1_11}, // k52 KC_0
    {0, C1_12}, // k53 KC_MINS
    {0, C1_13}, // k54 KC_EQL
    {0, C1_14}, // k55 KC_BSPC
    {0, C1_15}, // k57 KC_PGUP
    {0, C2_1},  // k10 KC_TAB
    {0, C2_2},  // k11 KC_Q
    {0, C2_3},  // k12 KC_W
    {0, C2_4},  // k13 KC_E
    {0, C2_5},  // k14 KC_R
    {0, C2_6},  // k15 KC_T
    {0, C2_7},  // k16 KC_Y
    {0, C2_8},  // k17 KC_U
    {0, C2_9},  // k60 KC_I
    {0, C2_10}, // k61 KC_O
    {0, C2_11}, // k62 KC_P
    {0, C2_12}, // k63 KC_LBRC
    {0, C2_13}, // k64 KC_RBRC
    {0, C2_14}, // k65 KC_BSLS
    {0, C2_15}, // k67 KC_PGDN
    {0, C3_1},  // k20 KC_CAPS
    {0, C3_2},  // k21 KC_A
    {0, C3_3},  // k22 KC_S
    {0, C3_4},  // k23 KC_D
    {0, C3_5},  // k24 KC_F
    {0, C3_6},  // k25 KC_G
    {0, C3_7},  // k26 KC_H
    {0, C3_8},  // k27 KC_J
    {0, C3_9},  // k70 KC_K
    {0, C3_10}, // k71 KC_L
    {0, C3_11}, // k72 KC_SCLN
    {0, C3_12}, // k73 KC_QUOT
    {0, C3_14}, // k75 KC_ENT
    {0, C4_1},  // k30 KC_LSFT
    {0, C4_3},  // k32 KC_Z
    {0, C4_4},  // k33 KC_X
    {0, C4_5},  // k34 KC_C
    {0, C4_6},  // k35 KC_V
    {0, C4_7},  // k36 KC_B
    {0, C4_8},  // k37 KC_N
    {0, C4_9},  // k80 KC_M
    {0, C4_10}, // k81 KC_COMM
    {0, C4_11}, // k82 KC_DOT
    {0, C4_12}, // k83 KC_SLSH
    {0, C4_13}, // k85 KC_RSFT
    {0, C4_14}, // k86 KC_UP
    {0, C5_1},  // k40 KC_LCTL
    {0, C5_2},  // k41 KC_LGUI
    {0, C5_3},  // k42 KC_LALT
    {0, C5_4},  // Unassociated between LALT and SPACE_2.75
    {0, C5_5},  // k45 KC_SPC SPACE_2.75
    {0, C5_6},  // k45 KC_SPC SPACE_6.75
    {0, C5_7},  // k46 KC_SPC SPACE_2.25
    {0, C5_8},  // Unassociated between SPACE_2.25 and SPACE_1.25
    {0, C5_9},  // k90 KC_RGUI
    {0, C5_10}, // k92 KC_RALT
    {0, C5_11}, // k93 MO(_FL)
    {0, C5_12}, // k94 KC_RCTL
    {0, C5_13}, // k95 KC_LEFT
    {0, C5_14}, // k96 KC_DOWN
    {0, C5_15}  // k97 KC_RGHT
};

const led_matrix g_leds[LED_DRIVER_LED_COUNT] = {

    /*{row | col << 4}
      |            LED_ROW_COL(row, col)
      |             |            modifier
      |             |            | */
    {{0|(1<<4)},   {0, 0}, 1},           // k00  KC_GESC
    {{0|(2<<4)},   {14.45, 0}, 0},       // k01 KC_1
    {{0|(3<<4)},   {28.9, 0}, 0},        // k02 KC_2
    {{0|(4<<4)},   {43.35, 0}, 0},       // k03 KC_3
    {{0|(5<<4)},   {57.8, 0}, 0},        // k04 KC_4
    {{0|(6<<4)},   {72.25, 0}, 0},       // k05 KC_5
    {{0|(7<<4)},   {86.7, 0}, 0},        // k06 KC_6
    {{0|(8<<4)},   {101.2, 0}, 0},       // k07 KC_7
    {{0|(9<<4)},   {115.6, 0}, 0},       // k50 KC_8
    {{0|(10<<4)},  {130, 0}, 0},         // k51 KC_9
    {{0|(11<<4)},  {144.5, 0}, 0},       // k52 KC_0
    {{0|(12<<4)},  {159, 0}, 0},         // k53 KC_MINS
    {{0|(13<<4)},  {173.4, 0}, 0},       // k54 KC_EQL
    {{0|(14<<4)},  {195.1, 0}, 1},       // k55 KC_BSPC
    {{0|(15<<4)},  {224, 0}, 1},         // k57 KC_PGUP

    {{1|(0<<4)},   {3.6125, 16}, 1},     // k10 KC_TAB
    {{1|(1<<4)},   {21.675, 16}, 0},     // k11 KC_Q
    {{1|(2<<4)},   {36.125, 16}, 0},     // k12 KC_W
    {{1|(3<<4)},   {50.575, 16}, 0},     // k13 KC_E
    {{1|(4<<4)},   {65.025, 16}, 0},     // k14 KC_R
    {{1|(5<<4)},   {79.475, 16}, 0},     // k15 KC_T
    {{1|(6<<4)},   {93.925, 16}, 0},     // k16 KC_Y
    {{1|(7<<4)},   {108.375, 16}, 0},    // k17 KC_U
    {{1|(8<<4)},   {122.825, 16}, 0},    // k60 KC_I
    {{1|(9<<4)},   {137.275, 16}, 0},    // k61 KC_O
    {{1|(10<<4)},  {151.725, 16}, 0},    // k62 KC_P
    {{1|(11<<4)},  {166.175, 16}, 0},    // k63 KC_LBRC
    {{1|(12<<4)},  {180.625, 16}, 0},    // k64 KC_RBRC
    {{1|(13<<4)},  {198.6875, 16}, 1},   // k65 KC_BSLS
    {{1|(14<<4)},  {224, 16}, 1},        // k67 KC_PGDN

    {{2|(0<<4)},   {5.41875, 32}, 1},    // k20 KC_CAPS
    {{2|(1<<4)},   {25.2875, 32}, 0},    // k21 KC_A
    {{2|(2<<4)},   {39.7375, 32}, 0},    // k22 KC_S
    {{2|(3<<4)},   {54.1875, 32}, 0},    // k23 KC_D
    {{2|(4<<4)},   {68.6375, 32}, 0},    // k24 KC_F
    {{2|(5<<4)},   {83.0875, 32}, 0},    // k25 KC_G
    {{2|(6<<4)},   {97.5375, 32}, 0},    // k26 KC_H
    {{2|(7<<4)},   {111.9875, 32}, 0},   // k27 KC_J
    {{2|(8<<4)},   {126.4375, 32}, 0},   // k70 KC_K
    {{2|(9<<4)},   {140.8875, 32}, 0},   // k71 KC_L
    {{2|(10<<4)},  {155.3375, 32}, 0},   // k72 KC_SCLN
    {{2|(11<<4)},  {169.7875, 32}, 0},   // k73 KC_QUOT
    {{2|(12<<4)},  {184.2375, 32}, 1},   // k75 KC_ENT

    {{3|(0<<4)},   {16.25625, 48}, 1},   // k30 KC_LSFT
    {{3|(1<<4)},   {32.5125, 48}, 0},    // k32 KC_Z
    {{3|(2<<4)},   {46.9625, 48}, 0},    // k33 KC_X
    {{3|(3<<4)},   {61.4125, 48}, 0},    // k34 KC_C
    {{3|(4<<4)},   {75.8625, 48}, 0},    // k35 KC_V
    {{3|(5<<4)},   {90.3125, 48}, 0},    // k36 KC_B
    {{3|(6<<4)},   {104.7625, 48}, 0},   // k37 KC_N
    {{3|(7<<4)},   {119.2125, 48}, 0},   // k80 KC_M
    {{3|(8<<4)},   {133.6625, 48}, 0},   // k81 KC_COMM
    {{3|(9<<4)},   {148.1125, 48}, 0},   // k82 KC_DOT
    {{3|(10<<4)},  {162.5625, 48}, 0},   // k83 KC_SLSH
    {{3|(11<<4)},  {187.85, 48}, 1},     // k85 KC_RSFT
    {{3|(12<<4)},  {209.525, 48}, 1},    // k86 KC_UP

    {{4|(0<<4)},   {9.03125, 64}, 1},    // k40 KC_LCTL
    {{4|(1<<4)},   {27.09375, 64}, 1},   // k41 KC_LGUI
    {{4|(2<<4)},   {45.15625, 64}, 1},   // k42 KC_LALT
    {{4|(3<<4)},   {59.45, 64}, 1},      // Unassociated between LALT and SPACE_2.75
    {{4|(4<<4)},   {73.9, 64}, 1},       // k45 KC_SPC SPACE_2.75
    {{4|(5<<4)},   {88.35, 64}, 1},      // k45 KC_SPC SPACE_6.25
    {{4|(6<<4)},   {102.8, 64}, 1},      // k46 KC_SPC SPACE_2.25
    {{4|(7<<4)},   {117.40625, 64}, 1},  // Unassociated between SPACE_2.25 and SPACE_2.75
    {{4|(8<<4)},   {135.46875, 64}, 1},  // k90 KC_RGUI
    {{4|(9<<4)},   {153.53125, 64}, 1},  // k92 KC_RALT
    {{4|(10<<4)},  {167.98125, 64}, 1},  // k93 MO(_FL)
    {{4|(11<<4)},  {186.04375, 64}, 1},  // k94 KC_RCTL
    {{4|(12<<4)},  {195.075, 64}, 1},    // k95 KC_LEFT
    {{4|(13<<4)},  {209.525, 64}, 1},    // k96 KC_DOWN
    {{4|(14<<4)},  {224, 64}, 1}         // k97 KC_RGHT
};
#endif
