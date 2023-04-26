/* Copyright 2023 JUKAIE <lice@jukaie.com>
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

#include "jk01.h"

#ifdef RGB_MATRIX_ENABLE

const aw_led g_aw_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |     R location
 *   |     |          G location
 *   |     |          |          B location
 *   |     |          |          | */
    //{0, CS1_SW4,   CS2_SW4,   CS3_SW4},   //   0, k00, Esc

    {0, CS1_SW1,   CS2_SW1,   CS3_SW1},   //   0, k13, Esc
    {0, CS1_SW2,   CS2_SW2,   CS3_SW2},   //   1, k26, F1
    {0, CS1_SW3,   CS2_SW3,   CS3_SW3},   //   2, k36, F2
    {0, CS1_SW4,   CS2_SW4,   CS3_SW4},   //   3, k31, F3
    {0, CS1_SW5,   CS2_SW5,   CS3_SW5},   //   4, k33, F4
    {0, CS1_SW6,   CS2_SW6,   CS3_SW6},   //   5, k07, F5
    {0, CS1_SW7,   CS2_SW7,   CS3_SW7},   //   6, k63, F6
    {0, CS1_SW8,   CS2_SW8,   CS3_SW8},   //   7, k71, F7
    {0, CS1_SW9,   CS2_SW9,   CS3_SW9},   //   8, k76, F8
    {0, CS1_SW10,  CS2_SW10,  CS3_SW10},  //   9, ka6, F9
    {0, CS1_SW11,  CS2_SW11,  CS3_SW11},  //  10, ka7, F10
    {0, CS1_SW12,  CS2_SW12,  CS3_SW12},  //  11, ka3, F11
    {1, CS1_SW1,   CS2_SW1,   CS3_SW1},   //  12, ka5, F12
    {1, CS4_SW2,   CS5_SW2,   CS6_SW2},   //  13, k97, Printscreen
    {1, CS4_SW5,   CS5_SW5,   CS6_SW5},   //  14, k02, Del

    {0, CS4_SW1,   CS5_SW1,   CS6_SW1},   //  15, k16, `
    {0, CS4_SW2,   CS5_SW2,   CS6_SW2},   //  16, k17, 1
    {0, CS4_SW3,   CS5_SW3,   CS6_SW3},   //  17, k27, 2
    {0, CS4_SW4,   CS5_SW4,   CS6_SW4},   //  18, k37, 3
    {0, CS4_SW5,   CS5_SW5,   CS6_SW5},   //  19, k47, 4
    {0, CS4_SW6,   CS5_SW6,   CS6_SW6},   //  20, k46, 5
    {0, CS4_SW7,   CS5_SW7,   CS6_SW7},   //  21, k56, 6
    {0, CS4_SW8,   CS5_SW8,   CS6_SW8},   //  22, k57, 7
    {0, CS4_SW9,   CS5_SW9,   CS6_SW9},   //  23, k67, 8
    {0, CS4_SW10,  CS5_SW10,  CS6_SW10},  //  24, k77, 9
    {0, CS4_SW11,  CS5_SW11,  CS6_SW11},  //  25, k87, 0
    {0, CS4_SW12,  CS5_SW12,  CS6_SW12},  //  26, k86, -
    {1, CS1_SW5,   CS2_SW5,   CS3_SW5},   //  27, k66, =
    {1, CS1_SW7,   CS2_SW7,   CS3_SW7},   //  28, ka1, Backspace
    {1, CS1_SW2,   CS2_SW2,   CS3_SW2},   //  29, kc6, Home

    {0, CS7_SW1,   CS8_SW1,   CS9_SW1},   //  30, k11, Tab
    {0, CS7_SW2,   CS8_SW2,   CS9_SW2},   //  31, k10, Q
    {0, CS7_SW3,   CS8_SW3,   CS9_SW3},   //  32, k20, W
    {0, CS7_SW4,   CS8_SW4,   CS9_SW4},   //  33, k30, E
    {0, CS7_SW5,   CS8_SW5,   CS9_SW5},   //  34, k40, R
    {0, CS7_SW6,   CS8_SW6,   CS9_SW6},   //  35, k41, T
    {0, CS7_SW7,   CS8_SW7,   CS9_SW7},   //  36, k51, Y
    {0, CS7_SW8,   CS8_SW8,   CS9_SW8},   //  37, k50, U
    {0, CS7_SW9,   CS8_SW9,   CS9_SW9},   //  38, k60, I
    {0, CS7_SW10,  CS8_SW10,  CS9_SW10},  //  39, k70, O
    {0, CS7_SW11,  CS8_SW11,  CS9_SW11},  //  40, k80, P
    {0, CS7_SW12,  CS8_SW12,  CS9_SW12},  //  41, k81, [
    {1, CS1_SW8,   CS2_SW8,   CS3_SW8},   //  42, k61, ]
    {1, CS1_SW9,   CS2_SW9,   CS3_SW9},   //  43, ka2, "\\"
    {1, CS4_SW3,   CS5_SW3,   CS6_SW3},   //  44, k65, End

    {0, CS10_SW1,  CS11_SW1,  CS12_SW1},  //  45, k21, Caps Lock
    {0, CS10_SW2,  CS11_SW2,  CS12_SW2},  //  46, k12, A
    {0, CS10_SW3,  CS11_SW3,  CS12_SW3},  //  47, k22, S
    {0, CS10_SW4,  CS11_SW4,  CS12_SW4},  //  48, k32, D
    {0, CS10_SW5,  CS11_SW5,  CS12_SW5},  //  49, k42, F
    {0, CS10_SW6,  CS11_SW6,  CS12_SW6},  //  50, k43, G
    {0, CS10_SW7,  CS11_SW7,  CS12_SW7},  //  51, k53, H
    {0, CS10_SW8,  CS11_SW8,  CS12_SW8},  //  52, k52, J
    {0, CS10_SW9,  CS11_SW9,  CS12_SW9},  //  53, k62, K
    {0, CS10_SW10, CS11_SW10, CS12_SW10}, //  54, k72, L
    {0, CS10_SW11, CS11_SW11, CS12_SW11}, //  55, k82, ;
    {0, CS10_SW12, CS11_SW12, CS12_SW12}, //  56, k83, '
    {1, CS1_SW11,  CS2_SW11,  CS3_SW11},  //  57, ka4, Enter
    {1, CS4_SW4,   CS5_SW4,   CS6_SW4},   //  58, k15, PgUp

    {0, CS13_SW1,  CS14_SW1,  CS15_SW1},  //  59, k00, Shift_L
    {0, CS13_SW2,  CS14_SW2,  CS15_SW2},  //  60, k14, Z
    {0, CS13_SW3,  CS14_SW3,  CS15_SW3},  //  61, k24, X
    {0, CS13_SW4,  CS14_SW4,  CS15_SW4},  //  62, k34, C
    {0, CS13_SW5,  CS14_SW5,  CS15_SW5},  //  63, k44, V
    {0, CS13_SW6,  CS14_SW6,  CS15_SW6},  //  64, k45, B
    {0, CS13_SW7,  CS14_SW7,  CS15_SW7},  //  65, k55, N
    {0, CS13_SW8,  CS14_SW8,  CS15_SW8},  //  66, k54, M
    {0, CS13_SW9,  CS14_SW9,  CS15_SW9},  //  67, k64, ,
    {0, CS13_SW10, CS14_SW10, CS15_SW10}, //  68, k74, .
    {0, CS13_SW11, CS14_SW11, CS15_SW11}, //  69, k85, /
    {1, CS4_SW8,   CS5_SW8,   CS6_SW8},   //  70, k91, Shift_R
    {1, CS4_SW9,   CS5_SW9,   CS6_SW9},   //  71, k35, Up
    {1, CS4_SW7,   CS5_SW7,   CS6_SW7},   //  72, k25, PgDn

    {0, CS16_SW1,  CS17_SW1,  CS18_SW1},  //  73, k06, Ctrl_L
    {0, CS16_SW2,  CS17_SW2,  CS18_SW2},  //  74, k90, Win_L
    {0, CS16_SW3,  CS17_SW3,  CS18_SW3},  //  75, k93, Alt_L
    {0, CS16_SW6,  CS17_SW6,  CS18_SW6},  //  76, k94, Space
    {0, CS16_SW9,  CS17_SW9,  CS18_SW9},  //  77, k95, Alt_R
    {0, CS16_SW10, CS17_SW10, CS18_SW10}, //  78, k92, FN
    {0, CS16_SW12, CS17_SW12, CS18_SW12}, //  79, k04, Ctrl_R
    {1, CS4_SW10,  CS5_SW10,  CS6_SW10},  //  80, k03, Left
    {1, CS4_SW11,  CS5_SW11,  CS6_SW11},  //  81, k73, Down
    {1, CS10_SW5,  CS11_SW5,  CS12_SW5},  //  82, k05, Right

    {1, CS10_SW10, CS11_SW10, CS12_SW10}, //  83, kb0, Z1
    {1, CS10_SW11, CS11_SW11, CS12_SW11}, //  84, kb1, Z2
};

#define __ NO_LED
//#define RGB_LAYOUT LAYOUT

led_config_t g_led_config = {

{
    { 59, __, 14, 80, 79, 82, 73,  5},
    { 31, 30, 46,  0, 60, 58, 15, 16},
    { 32, 45, 47, __, 61, 72, 1 , 17},
    { 33,  3, 48, 4, 62, 71,   2, 18},
    { 34, 35, 49, 50, 63, 64, 20, 19},
    { 37, 36, 52, 51, 66, 65, 21, 22},
    { 38, 42, 53,  6, 67, 44, 27, 23},
    { 39,  7, 54, 81, 68, __,  8, 24},
    { 40, 41, 55, 56, __, 69, 26, 25},
    { 74, 70, 78, 75, 76, 77, __, 13},
    { __, 28, 43, 11, 57, 12,  9, 10},
    { 83, 84, __, __, __, __, 29, __}
},
{
    { 0, 0}, //   0, k13, Esc
    { 20, 0}, //   1, k26, F1
    { 30, 0}, //   2, k36, F2
    { 40, 0}, //   3, k31, F3
    { 50, 0}, //   4, k33, F4
    { 60, 0}, //   5, k07, F5
    { 70, 0}, //   6, k63, F6
    { 80, 0}, //   7, k71, F7
    { 90, 0}, //   8, k76, F8
    { 100,0}, //   9, ka6, F9
    { 110,0}, //  10, ka7, F10
    { 120,0}, //  11, ka3, F11
    { 130,0}, //  12, ka5, F12
    { 140,0}, //  13, k97, Printscreen
    { 150,0}, //  14, k02, Del

    { 0, 10}, //  15, k16, `
    { 10, 10}, //  16, k17, 1
    { 20, 10}, //  17, k27, 2
    { 30, 10}, //  18, k37, 3
    { 40, 10}, //  19, k47, 4
    { 50, 10}, //  20, k46, 5
    { 60, 10}, //  21, k56, 6
    { 70, 10}, //  22, k57, 7
    { 80, 10}, //  23, k67, 8
    { 90, 10}, //  24, k77, 9
    { 100,10}, //  25, k87, 0
    { 110,10}, //  26, k86, -
    { 120,10}, //  27, k66, =
    { 130,10}, //  28, ka1, Backspace
    { 150,10}, //  29, kc6, Home

    { 0, 20}, //  30, k11, Tab
    { 15, 20}, //  31, k10, Q
    { 25, 20}, //  32, k20, W
    { 35, 20}, //  33, k30, E
    { 45, 20}, //  34, k40, R
    { 55, 20}, //  35, k41, T
    { 65, 20}, //  36, k51, Y
    { 75, 20}, //  37, k50, U
    { 85, 20}, //  38, k60, I
    { 95, 20}, //  39, k70, O
    { 105,20}, //  40, k80, P
    { 115,20}, //  41, k81, [
    { 125,20}, //  42, k61, ]
    { 135,20}, //  43, ka2, "\\"
    { 150,20}, //  44, k65, End

    { 0, 30}, //  45, k21, Caps Lock
    { 17, 30}, //  46, k12, A
    { 27, 30}, //  47, k22, S
    { 37, 30}, //  48, k32, D
    { 47, 30}, //  49, k42, F
    { 57, 30}, //  50, k43, G
    { 67, 30}, //  51, k53, H
    { 77, 30}, //  52, k52, J
    { 87, 30}, //  53, k62, K
    { 97, 30}, //  54, k72, L
    { 107,30}, //  55, k82, ;
    { 117,30}, //  56, k83, '
    { 127,30}, //  57, ka4, Enter
    { 150,30}, //  58, k15, PgUp

    { 0, 40}, //  59, k00, Shift_L
    { 22, 40}, //  60, k14, Z
    { 32, 40}, //  61, k24, X
    { 42, 40}, //  62, k34, C
    { 52, 40}, //  63, k44, V
    { 62, 40}, //  64, k45, B
    { 72, 40}, //  65, k55, N
    { 82, 40}, //  66, k54, M
    { 92, 40}, //  67, k64, ,
    { 102, 40}, //  68, k74, .
    { 112,40}, //  69, k85, /
    { 122,40}, //  70, k91, Shift_R
    { 140,40}, //  70, k35, Up
    { 150,40}, //  72, k25, PgDn

    { 0, 50}, //  73, k06, Ctrl_L
    { 12, 50}, //  74, k90, Win_L
    { 25, 50}, //  75, k93, Alt_L
    { 37, 50}, //  76, k94, Space
    { 100, 50}, //  77, k95, Alt_R
    { 110, 50}, //  78, k92, FN
    { 120, 50}, //  79, k04, Ctrl_R
    { 130, 50}, //  80, k03, Left
    { 140, 50}, //  81, k73, Down
    { 150, 50}, //  82, k05, Right

    { 0, 1}, // 83, kb0, Z1
    { 0, 2}, // 84, kb1, Z2
},
{
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    8, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
}
};
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

#ifdef ENCODER_ENABLE

bool encoder_update_kb(uint8_t index, bool clockwise) {

    if (!encoder_update_user(index, clockwise)) { return false; }
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLD);
        } else {
            tap_code(KC_VOLU);
        }
    }
    return true;
}
#endif

