/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>
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

#include "iso.h"

#ifdef RGB_MATRIX_ENABLE

const aw_led g_aw_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |     R location
 *   |     |          G location
 *   |     |          |          B location
 *   |     |          |          | */
    {0, CS1_SW1,   CS2_SW1,   CS3_SW1},   //   0, k00, Esc
    {0, CS1_SW2,   CS2_SW2,   CS3_SW2},   //   1, k10, F1
    {0, CS1_SW3,   CS2_SW3,   CS3_SW3},   //   2, k20, F2
    {0, CS1_SW4,   CS2_SW4,   CS3_SW4},   //   3, k30, F3
    {0, CS1_SW5,   CS2_SW5,   CS3_SW5},   //   4, k40, F4
    {0, CS1_SW6,   CS2_SW6,   CS3_SW6},   //   5, k50, F5
    {0, CS1_SW7,   CS2_SW7,   CS3_SW7},   //   6, k60, F6
    {0, CS1_SW8,   CS2_SW8,   CS3_SW8},   //   7, k70, F7
    {0, CS1_SW9,   CS2_SW9,   CS3_SW9},   //   8, k80, F8
    {0, CS1_SW10,  CS2_SW10,  CS3_SW10},  //   9, k90, F9
    {0, CS1_SW11,  CS2_SW11,  CS3_SW11},  //  10, ka0, F10
    {0, CS1_SW12,  CS2_SW12,  CS3_SW12},  //  11, kb0, F11
    {1, CS1_SW1,   CS2_SW1,   CS3_SW1},   //  12, kc0, F12
    {1, CS4_SW2,   CS5_SW2,   CS6_SW2},   //  13, kd0, Printscreen
    {1, CS4_SW3,   CS5_SW3,   CS6_SW3},   //  14, k06, Delete
    {1, CS1_SW2,   CS2_SW2,   CS3_SW2},   //  15, k16, Insert
    {1, CS4_SW4,   CS5_SW4,   CS6_SW4},   //  16, k26, Page Up
    {1, CS4_SW7,   CS5_SW7,   CS6_SW7},   //  17, k36, Page Down

    {0, CS4_SW1,   CS5_SW1,   CS6_SW1},   //  18, k01, `
    {0, CS4_SW2,   CS5_SW2,   CS6_SW2},   //  19, k11, 1
    {0, CS4_SW3,   CS5_SW3,   CS6_SW3},   //  20, k21, 2
    {0, CS4_SW4,   CS5_SW4,   CS6_SW4},   //  21, k31, 3
    {0, CS4_SW5,   CS5_SW5,   CS6_SW5},   //  22, k41, 4
    {0, CS4_SW6,   CS5_SW6,   CS6_SW6},   //  23, k51, 5
    {0, CS4_SW7,   CS5_SW7,   CS6_SW7},   //  24, k61, 6
    {0, CS4_SW8,   CS5_SW8,   CS6_SW8},   //  25, k71, 7
    {0, CS4_SW9,   CS5_SW9,   CS6_SW9},   //  26, k81, 8
    {0, CS4_SW10,  CS5_SW10,  CS6_SW10},  //  27, k91, 9
    {0, CS4_SW11,  CS5_SW11,  CS6_SW11},  //  28, ka1, 0
    {0, CS4_SW12,  CS5_SW12,  CS6_SW12},  //  29, kb1, -
    {1, CS1_SW5,   CS2_SW5,   CS3_SW5},   //  30, kc1, =
    {1, CS1_SW7,   CS2_SW7,   CS3_SW7},   //  31, kd1, Backspace
    {1, CS7_SW1,   CS8_SW1,   CS9_SW1},   //  32, k46, Num Lock
    {1, CS7_SW2,   CS8_SW2,   CS9_SW2},   //  33, k56, Num /
    {1, CS7_SW3,   CS8_SW3,   CS9_SW3},   //  34, k66, Num *
    {1, CS7_SW4,   CS8_SW4,   CS9_SW4},   //  35, k76, Num -

    {0, CS7_SW1,   CS8_SW1,   CS9_SW1},   //  36, k02, Tab
    {0, CS7_SW2,   CS8_SW2,   CS9_SW2},   //  37, k12, Q
    {0, CS7_SW3,   CS8_SW3,   CS9_SW3},   //  38, k22, W
    {0, CS7_SW4,   CS8_SW4,   CS9_SW4},   //  39, k32, E
    {0, CS7_SW5,   CS8_SW5,   CS9_SW5},   //  40, k42, R
    {0, CS7_SW6,   CS8_SW6,   CS9_SW6},   //  41, k52, T
    {0, CS7_SW7,   CS8_SW7,   CS9_SW7},   //  42, k62, Y
    {0, CS7_SW8,   CS8_SW8,   CS9_SW8},   //  43, k72, U
    {0, CS7_SW9,   CS8_SW9,   CS9_SW9},   //  44, k82, I
    {0, CS7_SW10,  CS8_SW10,  CS9_SW10},  //  45, k92, O
    {0, CS7_SW11,  CS8_SW11,  CS9_SW11},  //  46, ka2, P
    {0, CS7_SW12,  CS8_SW12,  CS9_SW12},  //  47, kb2, [
    {1, CS1_SW8,   CS2_SW8,   CS3_SW8},   //  48, kc2, ]
    {1, CS1_SW11,  CS2_SW11,  CS3_SW11},  //  49, kd3, Enter
    {1, CS7_SW5,   CS8_SW5,   CS9_SW5},   //  50, k86, Num 7
    {1, CS7_SW6,   CS8_SW6,   CS9_SW6},   //  51, k96, Num 8
    {1, CS7_SW7,   CS8_SW7,   CS9_SW7},   //  52, ka6, Num 9
    {1, CS7_SW8,   CS8_SW8,   CS9_SW8},   //  53, kb6, Num +

    {0, CS10_SW1,  CS11_SW1,  CS12_SW1},  //  54, k03, Caps Lock
    {0, CS10_SW2,  CS11_SW2,  CS12_SW2},  //  55, k13, A
    {0, CS10_SW3,  CS11_SW3,  CS12_SW3},  //  56, k23, S
    {0, CS10_SW4,  CS11_SW4,  CS12_SW4},  //  57, k33, D
    {0, CS10_SW5,  CS11_SW5,  CS12_SW5},  //  58, k43, F
    {0, CS10_SW6,  CS11_SW6,  CS12_SW6},  //  59, k53, G
    {0, CS10_SW7,  CS11_SW7,  CS12_SW7},  //  60, k63, H
    {0, CS10_SW8,  CS11_SW8,  CS12_SW8},  //  61, k73, J
    {0, CS10_SW9,  CS11_SW9,  CS12_SW9},  //  62, k83, K
    {0, CS10_SW10, CS11_SW10, CS12_SW10}, //  63, k93, L
    {0, CS10_SW11, CS11_SW11, CS12_SW11}, //  64, ka3, ;
    {0, CS10_SW12, CS11_SW12, CS12_SW12}, //  65, kb3, '
    {1, CS1_SW10,  CS2_SW10,  CS3_SW10},  //  66, kc3, #
    {1, CS7_SW9,   CS8_SW9,   CS9_SW9},   //  67, ka7, Num 4
    {1, CS7_SW10,  CS8_SW10,  CS9_SW10},  //  68, kb7, Num 5
    {1, CS7_SW11,  CS8_SW11,  CS9_SW11},  //  69, kc7, Num 6

    {0, CS13_SW1,  CS14_SW1,  CS15_SW1},  //  70, k04, Shift_L
    {0, CS13_SW12, CS14_SW12, CS15_SW12}, //  71, k14, "\\"
    {0, CS13_SW2,  CS14_SW2,  CS15_SW2},  //  72, k24, Z
    {0, CS13_SW3,  CS14_SW3,  CS15_SW3},  //  73, k34, X
    {0, CS13_SW4,  CS14_SW4,  CS15_SW4},  //  74, k44, C
    {0, CS13_SW5,  CS14_SW5,  CS15_SW5},  //  75, k54, V
    {0, CS13_SW6,  CS14_SW6,  CS15_SW6},  //  76, k64, B
    {0, CS13_SW7,  CS14_SW7,  CS15_SW7},  //  77, k74, N
    {0, CS13_SW8,  CS14_SW8,  CS15_SW8},  //  78, k84, M
    {0, CS13_SW9,  CS14_SW9,  CS15_SW9},  //  79, k94, ,
    {0, CS13_SW10, CS14_SW10, CS15_SW10}, //  80, ka4, .
    {0, CS13_SW11, CS14_SW11, CS15_SW11}, //  81, kb4, /
    {1, CS4_SW8,   CS5_SW8,   CS6_SW8},   //  82, kd4, Shift_R
    {1, CS4_SW9,   CS5_SW9,   CS6_SW9},   //  83, k17, Up
    {1, CS10_SW1,  CS11_SW1,  CS12_SW1},  //  84, k67, Num 1
    {1, CS10_SW2,  CS11_SW2,  CS12_SW2},  //  85, k77, Num 2
    {1, CS10_SW3,  CS11_SW3,  CS12_SW3},  //  86, k87, Num 3
    {1, CS10_SW4,  CS11_SW4,  CS12_SW4},  //  87, k97, Enter_R

    {0, CS16_SW1,  CS17_SW1,  CS18_SW1},  //  88, k05, Ctrl_L
    {0, CS16_SW2,  CS17_SW2,  CS18_SW2},  //  89, k15, Win_L
    {0, CS16_SW3,  CS17_SW3,  CS18_SW3},  //  90, k25, Alt_L
    {0, CS16_SW6,  CS17_SW6,  CS18_SW6},  //  91, k65, Space
    {0, CS16_SW9,  CS17_SW9,  CS18_SW9},  //  92, k95, Alt_R
    {0, CS16_SW10, CS17_SW10, CS18_SW10}, //  93, ka5, FN
    {0, CS16_SW12, CS17_SW12, CS18_SW12}, //  94, kc5, Ctrl_R
    {1, CS4_SW10,  CS5_SW10,  CS6_SW10},  //  95, k07, Left
    {1, CS4_SW11,  CS5_SW11,  CS6_SW11},  //  96, k27, Down
    {1, CS10_SW5,  CS11_SW5,  CS12_SW5},  //  97, k37, Right
    {1, CS10_SW6,  CS11_SW6,  CS12_SW6},  //  98, k47, Num 0
    {1, CS10_SW7,  CS11_SW7,  CS12_SW7},  //  99, k57, Num .

    {1, CS13_SW1,  CS14_SW1,  CS15_SW1},  // 101, LED 1
    {1, CS13_SW2,  CS14_SW2,  CS15_SW2},  // 102, LED 2
    {1, CS13_SW3,  CS14_SW3,  CS15_SW3},  // 103, LED 3
    {1, CS13_SW4,  CS14_SW4,  CS15_SW4},  // 104, LED 4
    {1, CS13_SW5,  CS14_SW5,  CS15_SW5},  // 105, LED 5
    {1, CS13_SW6,  CS14_SW6,  CS15_SW6},  // 106, LED 6
    {1, CS13_SW7,  CS14_SW7,  CS15_SW7},  // 107, LED 7
    {1, CS13_SW8,  CS14_SW8,  CS15_SW8},  // 108, LED 8
    {1, CS13_SW9,  CS14_SW9,  CS15_SW9},  // 109, LED 9
    {1, CS13_SW10, CS14_SW10, CS15_SW10}, // 110, LED 10
    {1, CS16_SW1,  CS17_SW1,  CS18_SW1},  // 111, LED 11
    {1, CS16_SW2,  CS17_SW2,  CS18_SW2},  // 112, LED 12
    {1, CS16_SW3,  CS17_SW3,  CS18_SW3},  // 113, LED 13
    {1, CS16_SW4,  CS17_SW4,  CS18_SW4},  // 114, LED 14
    {1, CS16_SW5,  CS17_SW5,  CS18_SW5},  // 115, LED 15
    {1, CS16_SW6,  CS17_SW6,  CS18_SW6},  // 116, LED 16
    {1, CS16_SW7,  CS17_SW7,  CS18_SW7},  // 117, LED 17
    {1, CS16_SW8,  CS17_SW8,  CS18_SW8},  // 118, LED 18
    {1, CS16_SW9,  CS17_SW9,  CS18_SW9},  // 119, LED 19
    {1, CS16_SW10, CS17_SW10, CS18_SW10}  // 120, LED 20
};

#define __ NO_LED

led_config_t g_led_config = {{
    { 0, 18, 36, 54, 70, 88, 14, 95},
    { 1, 19, 37, 55, 71, 89, 15, 83},
    { 2, 20, 38, 56, 72, 90, 16, 96},
    { 3, 21, 39, 57, 73, __, 17, 97},
    { 4, 22, 40, 58, 74, __, 32, 98},
    { 5, 23, 41, 59, 75, __, 33, 99},
    { 6, 24, 42, 60, 76, 91, 34, 84},
    { 7, 25, 43, 61, 77, __, 35, 85},
    { 8, 26, 44, 62, 78, __, 50, 86},
    { 9, 27, 45, 63, 79, 92, 51, 87},
    {10, 28, 46, 64, 80, 93, 52, 67},
    {11, 29, 47, 65, 81, __, 53, 68},
    {12, 30, 48, 66, __, 94, __, 69},
    {13, 31, __, 49, 82, __, __, __}
}, {
    { 11,    0}, //   0, k00, Esc
    { 22,    0}, //   1, k10, F1
    { 33,    0}, //   2, k20, F2
    { 44,    0}, //   3, k30, F3
    { 55,    0}, //   4, k40, F4
    { 66,    0}, //   5, k50, F5
    { 77,    0}, //   6, k60, F6
    { 88,    0}, //   7, k70, F7
    { 99,    0}, //   8, k80, F8
    { 110,   0}, //   9, k90, F9
    { 121,   0}, //  10, ka0, F10
    { 132,   0}, //  11, kb0, F11
    { 143,   0}, //  12, kc0, F12
    { 154,   0}, //  13, kd0, Printscreen
    { 165,   0}, //  14, k06, Delete
    { 176,   0}, //  15, k16, Insert
    { 187,   0}, //  16, k26, Page Up
    { 198,   0}, //  17, k36, Page Down
    {  11,  11}, //  18, k01, `
    {  22,  11}, //  19, k11, 1
    {  33,  11}, //  20, k21, 2
    {  44,  11}, //  21, k31, 3
    {  55,  11}, //  22, k41, 4
    {  66,  11}, //  23, k51, 5
    {  77,  11}, //  24, k61, 6
    {  88,  11}, //  25, k71, 7
    {  99,  11}, //  26, k81, 8
    { 110,  11}, //  27, k91, 9
    { 121,  11}, //  28, ka1, 0
    { 132,  11}, //  29, kb1, -
    { 143,  11}, //  30, kc1, =
    { 154,  11}, //  31, kd1, Backspace
    { 165,  11}, //  32, k46, Num Lock
    { 176,  11}, //  33, k56, Num /
    { 187,  11}, //  34, k66, Num *
    { 198,  11}, //  35, k76, Num -
    {  11,  22}, //  36, k02, Tab
    {  22,  22}, //  37, k12, Q
    {  33,  22}, //  38, k22, W
    {  44,  22}, //  39, k32, E
    {  55,  22}, //  40, k42, R
    {  66,  22}, //  41, k52, T
    {  77,  22}, //  42, k62, Y
    {  88,  22}, //  43, k72, U
    {  99,  22}, //  44, k82, I
    { 110,  22}, //  45, k92, O
    { 121,  22}, //  46, ka2, P
    { 132,  22}, //  47, kb2, [
    { 143,  22}, //  48, kc2, ]
    { 154,  22}, //  49, kd3, Enter
    { 165,  22}, //  50, k86, Num 7
    { 176,  22}, //  51, k96, Num 8
    { 187,  22}, //  52, ka6, Num 9
    { 198,  22}, //  53, kb6, Num +
    {  11,  33}, //  54, k03, Caps Lock
    {  22,  33}, //  55, k13, A
    {  33,  33}, //  56, k23, S
    {  44,  33}, //  57, k33, D
    {  55,  33}, //  58, k43, F
    {  66,  33}, //  59, k53, G
    {  77,  33}, //  60, k63, H
    {  88,  33}, //  61, k73, J
    {  99,  33}, //  62, k83, K
    { 110,  33}, //  63, k93, L
    { 121,  33}, //  64, ka3, ;
    { 132,  33}, //  65, kb3, '
    { 143,  33}, //  66, kc3, #
    { 165,  33}, //  67, ka7, Num 4
    { 176,  33}, //  68, kb7, Num 5
    { 187,  33}, //  69, kc7, Num 6
    {  11,  44}, //  70, k04, Shift_L
    {  22,  44}, //  71, k14, "\\"
    {  33,  44}, //  72, k24, Z
    {  44,  44}, //  73, k34, X
    {  55,  44}, //  74, k44, C
    {  66,  44}, //  75, k54, V
    {  77,  44}, //  76, k64, B
    {  88,  44}, //  77, k74, N
    {  99,  44}, //  78, k84, M
    { 110,  44}, //  79, k94, ,
    { 121,  44}, //  80, ka4, .
    { 132,  44}, //  81, kb4, /
    { 143,  44}, //  82, kd4, Shift_R
    { 154,  44}, //  83, k17, Up
    { 165,  44}, //  84, k67, Num 1
    { 176,  44}, //  85, k77, Num 2
    { 187,  44}, //  86, k87, Num 3
    { 198,  44}, //  87, k97, Enter_R
    {  11,  55}, //  88, k05, Ctrl_L
    {  22,  55}, //  89, k15, Win_L
    {  33,  55}, //  90, k25, Alt_L
    {  77,  55}, //  91, k65, Space
    { 110,  55}, //  92, k95, Alt_R
    { 121,  55}, //  93, ka5, FN
    { 132,  55}, //  94, kc5, Ctrl_R
    { 143,  55}, //  95, k07, Left
    { 154,  55}, //  96, k27, Down
    { 165,  55}, //  97, k37, Right
    { 176,  55}, //  98, k47, Num 0
    { 187,  55}, //  99, k57, Num .
    {   0,   0}, // 101, LED 1
    {   0,   6}, // 102, LED 2
    {   0,  12}, // 103, LED 3
    {   0,  18}, // 104, LED 4
    {   0,  24}, // 105, LED 5
    {   0,  30}, // 106, LED 6
    {   0,  36}, // 107, LED 7
    {   0,  42}, // 108, LED 8
    {   0,  48}, // 109, LED 9
    {   0,  54}, // 110, LED 10
    { 209,   0}, // 111, LED 11
    { 209,   6}, // 112, LED 12
    { 209,  12}, // 113, LED 13
    { 209,  18}, // 114, LED 14
    { 209,  24}, // 115, LED 15
    { 209,  30}, // 116, LED 16
    { 209,  36}, // 117, LED 17
    { 209,  42}, // 118, LED 18
    { 209,  48}, // 119, LED 19
    { 209,  54}  // 120, LED 20
}, {
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2
} };
#endif

#ifdef EEPROM_ENABLE

#include "spi_master.h"

void spi_init(void) {
    static bool is_initialised = false;
    if (!is_initialised) {
        is_initialised = true;

        // Try releasing special pins for a short time
        setPinInput(SPI_SCK_PIN);
        setPinInput(SPI_MOSI_PIN);
        setPinInput(SPI_MISO_PIN);

        chThdSleepMilliseconds(10);

        palSetPadMode(PAL_PORT(SPI_SCK_PIN), PAL_PAD(SPI_SCK_PIN), PAL_MODE_ALTERNATE(SPI_SCK_PAL_MODE) | PAL_OUTPUT_TYPE_PUSHPULL | PAL_OUTPUT_SPEED_HIGHEST | PAL_WB32_CURRENT_LEVEL3);
        palSetPadMode(PAL_PORT(SPI_MOSI_PIN), PAL_PAD(SPI_MOSI_PIN), PAL_MODE_ALTERNATE(SPI_MOSI_PAL_MODE) | PAL_OUTPUT_TYPE_PUSHPULL | PAL_OUTPUT_SPEED_HIGHEST);
        palSetPadMode(PAL_PORT(SPI_MISO_PIN), PAL_PAD(SPI_MISO_PIN), PAL_MODE_ALTERNATE(SPI_MISO_PAL_MODE) | PAL_OUTPUT_TYPE_PUSHPULL | PAL_OUTPUT_SPEED_HIGHEST);
    }
}

#endif
