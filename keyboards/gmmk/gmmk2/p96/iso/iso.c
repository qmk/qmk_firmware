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

#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE

const aw20216s_led_t PROGMEM g_aw20216s_leds[AW20216S_LED_COUNT] = {
/* Refer to AW20216S manual for these locations
 *   driver
 *   |     R location
 *   |     |          G location
 *   |     |          |          B location
 *   |     |          |          | */
    {0, SW1_CS1,   SW1_CS2,   SW1_CS3},   //   0, k00, Esc
    {0, SW2_CS1,   SW2_CS2,   SW2_CS3},   //   1, k10, F1
    {0, SW3_CS1,   SW3_CS2,   SW3_CS3},   //   2, k20, F2
    {0, SW4_CS1,   SW4_CS2,   SW4_CS3},   //   3, k30, F3
    {0, SW5_CS1,   SW5_CS2,   SW5_CS3},   //   4, k40, F4
    {0, SW6_CS1,   SW6_CS2,   SW6_CS3},   //   5, k50, F5
    {0, SW7_CS1,   SW7_CS2,   SW7_CS3},   //   6, k60, F6
    {0, SW8_CS1,   SW8_CS2,   SW8_CS3},   //   7, k70, F7
    {0, SW9_CS1,   SW9_CS2,   SW9_CS3},   //   8, k80, F8
    {0, SW10_CS1,  SW10_CS2,  SW10_CS3},  //   9, k90, F9
    {0, SW11_CS1,  SW11_CS2,  SW11_CS3},  //  10, ka0, F10
    {0, SW12_CS1,  SW12_CS2,  SW12_CS3},  //  11, kb0, F11
    {1, SW1_CS1,   SW1_CS2,   SW1_CS3},   //  12, kc0, F12
    {1, SW2_CS4,   SW2_CS5,   SW2_CS6},   //  13, kd0, Printscreen
    {1, SW3_CS4,   SW3_CS5,   SW3_CS6},   //  14, k06, Delete
    {1, SW2_CS1,   SW2_CS2,   SW2_CS3},   //  15, k16, Insert
    {1, SW4_CS4,   SW4_CS5,   SW4_CS6},   //  16, k26, Page Up
    {1, SW7_CS4,   SW7_CS5,   SW7_CS6},   //  17, k36, Page Down

    {0, SW1_CS4,   SW1_CS5,   SW1_CS6},   //  18, k01, `
    {0, SW2_CS4,   SW2_CS5,   SW2_CS6},   //  19, k11, 1
    {0, SW3_CS4,   SW3_CS5,   SW3_CS6},   //  20, k21, 2
    {0, SW4_CS4,   SW4_CS5,   SW4_CS6},   //  21, k31, 3
    {0, SW5_CS4,   SW5_CS5,   SW5_CS6},   //  22, k41, 4
    {0, SW6_CS4,   SW6_CS5,   SW6_CS6},   //  23, k51, 5
    {0, SW7_CS4,   SW7_CS5,   SW7_CS6},   //  24, k61, 6
    {0, SW8_CS4,   SW8_CS5,   SW8_CS6},   //  25, k71, 7
    {0, SW9_CS4,   SW9_CS5,   SW9_CS6},   //  26, k81, 8
    {0, SW10_CS4,  SW10_CS5,  SW10_CS6},  //  27, k91, 9
    {0, SW11_CS4,  SW11_CS5,  SW11_CS6},  //  28, ka1, 0
    {0, SW12_CS4,  SW12_CS5,  SW12_CS6},  //  29, kb1, -
    {1, SW5_CS1,   SW5_CS2,   SW5_CS3},   //  30, kc1, =
    {1, SW7_CS1,   SW7_CS2,   SW7_CS3},   //  31, kd1, Backspace
    {1, SW1_CS7,   SW1_CS8,   SW1_CS9},   //  32, k46, Num Lock
    {1, SW2_CS7,   SW2_CS8,   SW2_CS9},   //  33, k56, Num /
    {1, SW3_CS7,   SW3_CS8,   SW3_CS9},   //  34, k66, Num *
    {1, SW4_CS7,   SW4_CS8,   SW4_CS9},   //  35, k76, Num -

    {0, SW1_CS7,   SW1_CS8,   SW1_CS9},   //  36, k02, Tab
    {0, SW2_CS7,   SW2_CS8,   SW2_CS9},   //  37, k12, Q
    {0, SW3_CS7,   SW3_CS8,   SW3_CS9},   //  38, k22, W
    {0, SW4_CS7,   SW4_CS8,   SW4_CS9},   //  39, k32, E
    {0, SW5_CS7,   SW5_CS8,   SW5_CS9},   //  40, k42, R
    {0, SW6_CS7,   SW6_CS8,   SW6_CS9},   //  41, k52, T
    {0, SW7_CS7,   SW7_CS8,   SW7_CS9},   //  42, k62, Y
    {0, SW8_CS7,   SW8_CS8,   SW8_CS9},   //  43, k72, U
    {0, SW9_CS7,   SW9_CS8,   SW9_CS9},   //  44, k82, I
    {0, SW10_CS7,  SW10_CS8,  SW10_CS9},  //  45, k92, O
    {0, SW11_CS7,  SW11_CS8,  SW11_CS9},  //  46, ka2, P
    {0, SW12_CS7,  SW12_CS8,  SW12_CS9},  //  47, kb2, [
    {1, SW8_CS1,   SW8_CS2,   SW8_CS3},   //  48, kc2, ]
    {1, SW11_CS1,  SW11_CS2,  SW11_CS3},  //  49, kd3, Enter
    {1, SW5_CS7,   SW5_CS8,   SW5_CS9},   //  50, k86, Num 7
    {1, SW6_CS7,   SW6_CS8,   SW6_CS9},   //  51, k96, Num 8
    {1, SW7_CS7,   SW7_CS8,   SW7_CS9},   //  52, ka6, Num 9
    {1, SW8_CS7,   SW8_CS8,   SW8_CS9},   //  53, kb6, Num +

    {0, SW1_CS10,  SW1_CS11,  SW1_CS12},  //  54, k03, Caps Lock
    {0, SW2_CS10,  SW2_CS11,  SW2_CS12},  //  55, k13, A
    {0, SW3_CS10,  SW3_CS11,  SW3_CS12},  //  56, k23, S
    {0, SW4_CS10,  SW4_CS11,  SW4_CS12},  //  57, k33, D
    {0, SW5_CS10,  SW5_CS11,  SW5_CS12},  //  58, k43, F
    {0, SW6_CS10,  SW6_CS11,  SW6_CS12},  //  59, k53, G
    {0, SW7_CS10,  SW7_CS11,  SW7_CS12},  //  60, k63, H
    {0, SW8_CS10,  SW8_CS11,  SW8_CS12},  //  61, k73, J
    {0, SW9_CS10,  SW9_CS11,  SW9_CS12},  //  62, k83, K
    {0, SW10_CS10, SW10_CS11, SW10_CS12}, //  63, k93, L
    {0, SW11_CS10, SW11_CS11, SW11_CS12}, //  64, ka3, ;
    {0, SW12_CS10, SW12_CS11, SW12_CS12}, //  65, kb3, '
    {1, SW10_CS1,  SW10_CS2,  SW10_CS3},  //  66, kc3, #
    {1, SW9_CS7,   SW9_CS8,   SW9_CS9},   //  67, ka7, Num 4
    {1, SW10_CS7,  SW10_CS8,  SW10_CS9},  //  68, kb7, Num 5
    {1, SW11_CS7,  SW11_CS8,  SW11_CS9},  //  69, kc7, Num 6

    {0, SW1_CS13,  SW1_CS14,  SW1_CS15},  //  70, k04, Shift_L
    {0, SW12_CS13, SW12_CS14, SW12_CS15}, //  71, k14, "\\"
    {0, SW2_CS13,  SW2_CS14,  SW2_CS15},  //  72, k24, Z
    {0, SW3_CS13,  SW3_CS14,  SW3_CS15},  //  73, k34, X
    {0, SW4_CS13,  SW4_CS14,  SW4_CS15},  //  74, k44, C
    {0, SW5_CS13,  SW5_CS14,  SW5_CS15},  //  75, k54, V
    {0, SW6_CS13,  SW6_CS14,  SW6_CS15},  //  76, k64, B
    {0, SW7_CS13,  SW7_CS14,  SW7_CS15},  //  77, k74, N
    {0, SW8_CS13,  SW8_CS14,  SW8_CS15},  //  78, k84, M
    {0, SW9_CS13,  SW9_CS14,  SW9_CS15},  //  79, k94, ,
    {0, SW10_CS13, SW10_CS14, SW10_CS15}, //  80, ka4, .
    {0, SW11_CS13, SW11_CS14, SW11_CS15}, //  81, kb4, /
    {1, SW8_CS4,   SW8_CS5,   SW8_CS6},   //  82, kd4, Shift_R
    {1, SW9_CS4,   SW9_CS5,   SW9_CS6},   //  83, k17, Up
    {1, SW1_CS10,  SW1_CS11,  SW1_CS12},  //  84, k67, Num 1
    {1, SW2_CS10,  SW2_CS11,  SW2_CS12},  //  85, k77, Num 2
    {1, SW3_CS10,  SW3_CS11,  SW3_CS12},  //  86, k87, Num 3
    {1, SW4_CS10,  SW4_CS11,  SW4_CS12},  //  87, k97, Enter_R

    {0, SW1_CS16,  SW1_CS17,  SW1_CS18},  //  88, k05, Ctrl_L
    {0, SW2_CS16,  SW2_CS17,  SW2_CS18},  //  89, k15, Win_L
    {0, SW3_CS16,  SW3_CS17,  SW3_CS18},  //  90, k25, Alt_L
    {0, SW6_CS16,  SW6_CS17,  SW6_CS18},  //  91, k65, Space
    {0, SW9_CS16,  SW9_CS17,  SW9_CS18},  //  92, k95, Alt_R
    {0, SW10_CS16, SW10_CS17, SW10_CS18}, //  93, ka5, FN
    {0, SW12_CS16, SW12_CS17, SW12_CS18}, //  94, kc5, Ctrl_R
    {1, SW10_CS4,  SW10_CS5,  SW10_CS6},  //  95, k07, Left
    {1, SW11_CS4,  SW11_CS5,  SW11_CS6},  //  96, k27, Down
    {1, SW5_CS10,  SW5_CS11,  SW5_CS12},  //  97, k37, Right
    {1, SW6_CS10,  SW6_CS11,  SW6_CS12},  //  98, k47, Num 0
    {1, SW7_CS10,  SW7_CS11,  SW7_CS12},  //  99, k57, Num .

    {1, SW1_CS13,  SW1_CS14,  SW1_CS15},  // 101, LED 1
    {1, SW2_CS13,  SW2_CS14,  SW2_CS15},  // 102, LED 2
    {1, SW3_CS13,  SW3_CS14,  SW3_CS15},  // 103, LED 3
    {1, SW4_CS13,  SW4_CS14,  SW4_CS15},  // 104, LED 4
    {1, SW5_CS13,  SW5_CS14,  SW5_CS15},  // 105, LED 5
    {1, SW6_CS13,  SW6_CS14,  SW6_CS15},  // 106, LED 6
    {1, SW7_CS13,  SW7_CS14,  SW7_CS15},  // 107, LED 7
    {1, SW8_CS13,  SW8_CS14,  SW8_CS15},  // 108, LED 8
    {1, SW9_CS13,  SW9_CS14,  SW9_CS15},  // 109, LED 9
    {1, SW10_CS13, SW10_CS14, SW10_CS15}, // 110, LED 10
    {1, SW1_CS16,  SW1_CS17,  SW1_CS18},  // 111, LED 11
    {1, SW2_CS16,  SW2_CS17,  SW2_CS18},  // 112, LED 12
    {1, SW3_CS16,  SW3_CS17,  SW3_CS18},  // 113, LED 13
    {1, SW4_CS16,  SW4_CS17,  SW4_CS18},  // 114, LED 14
    {1, SW5_CS16,  SW5_CS17,  SW5_CS18},  // 115, LED 15
    {1, SW6_CS16,  SW6_CS17,  SW6_CS18},  // 116, LED 16
    {1, SW7_CS16,  SW7_CS17,  SW7_CS18},  // 117, LED 17
    {1, SW8_CS16,  SW8_CS17,  SW8_CS18},  // 118, LED 18
    {1, SW9_CS16,  SW9_CS17,  SW9_CS18},  // 119, LED 19
    {1, SW10_CS16, SW10_CS17, SW10_CS18}  // 120, LED 20
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
