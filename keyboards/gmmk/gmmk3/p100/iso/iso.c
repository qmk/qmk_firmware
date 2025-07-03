/* Copyright 2024 Glorious, LLC
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
#define __ NO_LED

/* Refer to AW20216S manual for these locations
 *   driver
 *   |     R location
 *   |     |          G location
 *   |     |          |          B location
 *   |     |          |          | */
const aw20216s_led_t PROGMEM g_aw20216s_leds[AW20216S_LED_COUNT] = {
    {0, SW1_CS1, SW1_CS2, SW1_CS3},        // 0 ESC
    {0, SW2_CS1, SW2_CS2, SW2_CS3},        // 1 F1
    {0, SW3_CS1, SW3_CS2, SW3_CS3},        // 2 F2
    {0, SW4_CS1, SW4_CS2, SW4_CS3},        // 3 F3
    {0, SW5_CS1, SW5_CS2, SW5_CS3},        // 4 F4
    {0, SW6_CS1, SW6_CS2, SW6_CS3},        // 5 F5
    {0, SW7_CS1, SW7_CS2, SW7_CS3},        // 6 F6
    {0, SW8_CS1, SW8_CS2, SW8_CS3},        // 7 F7
    {0, SW9_CS1, SW9_CS2, SW9_CS3},        // 8 F8
    {0, SW10_CS1, SW10_CS2, SW10_CS3},     // 9 F9
    {0, SW11_CS1, SW11_CS2, SW11_CS3},     // 10 F10
    {0, SW12_CS1, SW12_CS2, SW12_CS3},     // 11 F11
    {1, SW1_CS1, SW1_CS2, SW1_CS3},        // 12 F12
    {1, SW2_CS4, SW2_CS5, SW2_CS6},        // 13 PrtSc
    {1, SW3_CS1, SW3_CS2, SW3_CS3},        // 14 ScrLock
    {1, SW4_CS1, SW4_CS2, SW4_CS3},        // 15 Pause

    {0, SW1_CS4, SW1_CS5, SW1_CS6},        // 16 ~
    {0, SW2_CS4, SW2_CS5, SW2_CS6},        // 17 1
    {0, SW3_CS4, SW3_CS5, SW3_CS6},        // 18 2
    {0, SW4_CS4, SW4_CS5, SW4_CS6},        // 19 3
    {0, SW5_CS4, SW5_CS5, SW5_CS6},        // 20 4
    {0, SW6_CS4, SW6_CS5, SW6_CS6},        // 21 5
    {0, SW7_CS4, SW7_CS5, SW7_CS6},        // 22 6
    {0, SW8_CS4, SW8_CS5, SW8_CS6},        // 23 7
    {0, SW9_CS4, SW9_CS5, SW9_CS6},        // 24 8
    {0, SW10_CS4, SW10_CS5, SW10_CS6},     // 25 9
    {0, SW11_CS4, SW11_CS5, SW11_CS6},     // 26 0
    {0, SW12_CS4, SW12_CS5, SW12_CS6},     // 27 -
    {1, SW5_CS1, SW5_CS2, SW5_CS3},        // 28 =
    {1, SW7_CS1, SW7_CS2, SW7_CS3},        // 29 BS
    {1, SW6_CS4, SW6_CS5, SW6_CS6},        // 30 INS
    {1, SW5_CS4, SW5_CS5, SW5_CS6},        // 31 Home
    {1, SW4_CS4, SW4_CS5, SW4_CS6},        // 32 PGUP
    {1, SW1_CS7, SW1_CS8, SW1_CS9},        // 33 NumLock
    {1, SW2_CS7, SW2_CS8, SW2_CS9},        // 34 Num/
    {1, SW3_CS7, SW3_CS8, SW3_CS9},        // 35 Num*
    {1, SW4_CS7, SW4_CS8, SW4_CS9},        // 36 Num-

    {0, SW1_CS7, SW1_CS8, SW1_CS9},        // 37 TAB
    {0, SW2_CS7, SW2_CS8, SW2_CS9},        // 38 Q
    {0, SW3_CS7, SW3_CS8, SW3_CS9},        // 39 W
    {0, SW4_CS7, SW4_CS8, SW4_CS9},        // 40 E
    {0, SW5_CS7, SW5_CS8, SW5_CS9},        // 41 R
    {0, SW6_CS7, SW6_CS8, SW6_CS9},        // 42 T
    {0, SW7_CS7, SW7_CS8, SW7_CS9},        // 43 Y
    {0, SW8_CS7, SW8_CS8, SW8_CS9},        // 44 U
    {0, SW9_CS7, SW9_CS8, SW9_CS9},        // 45 I
    {0, SW10_CS7, SW10_CS8, SW10_CS9},     // 46 O
    {0, SW11_CS7, SW11_CS8, SW11_CS9},     // 47 P
    {0, SW12_CS7, SW12_CS8, SW12_CS9},     // 48 [
    {1, SW8_CS1, SW8_CS2, SW8_CS3},        // 49 ]
    {1, SW9_CS1, SW9_CS2, SW9_CS3},        // 50 (#)
    {1, SW3_CS4, SW3_CS5, SW3_CS6},        // 51 Delete
    {1, SW2_CS1, SW2_CS2, SW2_CS3},        // 52 End
    {1, SW7_CS4, SW7_CS5, SW7_CS6},        // 53 PGDN
    {1, SW5_CS7, SW5_CS8, SW5_CS9},        // 54 Num7
    {1, SW6_CS7, SW6_CS8, SW6_CS9},        // 55 Num8
    {1, SW7_CS7, SW7_CS8, SW7_CS9},        // 56 Num9
    {1, SW8_CS7, SW8_CS8, SW8_CS9},        // 57 Num+

    {0, SW1_CS10, SW1_CS11, SW1_CS12},     // 58 CAPS
    {0, SW2_CS10, SW2_CS11, SW2_CS12},     // 59 A
    {0, SW3_CS10, SW3_CS11, SW3_CS12},     // 60 S
    {0, SW4_CS10, SW4_CS11, SW4_CS12},     // 61 D
    {0, SW5_CS10, SW5_CS11, SW5_CS12},     // 62 F
    {0, SW6_CS10, SW6_CS11, SW6_CS12},     // 63 G
    {0, SW7_CS10, SW7_CS11, SW7_CS12},     // 64 H
    {0, SW8_CS10, SW8_CS11, SW8_CS12},     // 65 J
    {0, SW9_CS10, SW9_CS11, SW9_CS12},     // 66 K
    {0, SW10_CS10, SW10_CS11, SW10_CS12},  // 67 L
    {0, SW11_CS10, SW11_CS11, SW11_CS12},  // 68 ;
    {0, SW12_CS10, SW12_CS11, SW12_CS12},  // 69 '
    {1, SW11_CS1, SW11_CS2, SW11_CS3},     // 70 ENTER
    {1, SW9_CS7, SW9_CS8, SW9_CS9},        // 71 Num4
    {1, SW10_CS7, SW10_CS8, SW10_CS9},     // 72 Num5
    {1, SW11_CS7, SW11_CS8, SW11_CS9},     // 73 Num6

    {0, SW1_CS13, SW1_CS14, SW1_CS15},     // 74 L_SHIFT
    {0, SW4_CS16, SW4_CS17, SW4_CS18},     // 75 (\)
    {0, SW2_CS13, SW2_CS14, SW2_CS15},     // 76 Z
    {0, SW3_CS13, SW3_CS14, SW3_CS15},     // 77 X
    {0, SW4_CS13, SW4_CS14, SW4_CS15},     // 78 C
    {0, SW5_CS13, SW5_CS14, SW5_CS15},     // 79 V
    {0, SW6_CS13, SW6_CS14, SW6_CS15},     // 80 B
    {0, SW7_CS13, SW7_CS14, SW7_CS15},     // 81 N
    {0, SW8_CS13, SW8_CS14, SW8_CS15},     // 82 M
    {0, SW9_CS13, SW9_CS14, SW9_CS15},     // 83 ,
    {0, SW10_CS13, SW10_CS14, SW10_CS15},  // 84 .
    {0, SW11_CS13, SW11_CS14, SW11_CS15},  // 85 /
    {1, SW8_CS4, SW8_CS5, SW8_CS6},        // 86 R_SHIFT
    {1, SW9_CS4, SW9_CS5, SW9_CS6},        // 87 UP
    {1, SW1_CS10, SW1_CS11, SW1_CS12},     // 88 Num1
    {1, SW2_CS10, SW2_CS11, SW2_CS12},     // 89 Num2
    {1, SW3_CS10, SW3_CS11, SW3_CS12},     // 90 Num3
    {1, SW4_CS10, SW4_CS11, SW4_CS12},     // 91 NumEnter

    {0, SW1_CS16, SW1_CS17, SW1_CS18},     // 92 L_CTRL
    {0, SW2_CS16, SW2_CS17, SW2_CS18},     // 93 L_WIN
    {0, SW3_CS16, SW3_CS17, SW3_CS18},     // 94 L_ALT
    {0, SW6_CS16, SW6_CS17, SW6_CS18},     // 95 SPACE
    {0, SW9_CS16, SW9_CS17, SW9_CS18},     // 96 R_ALT
    {0, SW10_CS16, SW10_CS17, SW10_CS18},  // 97 FN
    {0, SW11_CS16, SW11_CS17, SW11_CS18},  // 98 APP
    {0, SW12_CS16, SW12_CS17, SW12_CS18},  // 99 R_CTRL
    {1, SW10_CS4, SW10_CS5, SW10_CS6},     // 100 LEFT
    {1, SW11_CS4, SW11_CS5, SW11_CS6},     // 101 DOWN
    {1, SW5_CS10, SW5_CS11, SW5_CS12},     // 102 RIGHT
    {1, SW6_CS10, SW6_CS11, SW6_CS12},     // 103 Num0
    {1, SW7_CS10, SW7_CS11, SW7_CS12},     // 104 Num.

    {1, SW1_CS13, SW1_CS14, SW1_CS15},     // 105 SLED1
    {1, SW2_CS13, SW2_CS14, SW2_CS15},     // 106 SLED2
    {1, SW3_CS13, SW3_CS14, SW3_CS15},     // 107 SLED3
    {1, SW4_CS13, SW4_CS14, SW4_CS15},     // 108 SLED4
    {1, SW5_CS13, SW5_CS14, SW5_CS15},     // 109 SLED5
    {1, SW6_CS13, SW6_CS14, SW6_CS15},     // 110 SLED6
    {1, SW7_CS13, SW7_CS14, SW7_CS15},     // 111 SLED7
    {1, SW8_CS13, SW8_CS14, SW8_CS15},     // 112 SLED8
    {1, SW9_CS13, SW9_CS14, SW9_CS15},     // 113 SLED9
    {1, SW10_CS13, SW10_CS14, SW10_CS15},  // 114 SLED10

    {1, SW1_CS16, SW1_CS17, SW1_CS18},     // 115 SLED11
    {1, SW2_CS16, SW2_CS17, SW2_CS18},     // 116 SLED12
    {1, SW3_CS16, SW3_CS17, SW3_CS18},     // 117 SLED13
    {1, SW4_CS16, SW4_CS17, SW4_CS18},     // 118 SLED14
    {1, SW5_CS16, SW5_CS17, SW5_CS18},     // 119 SLED15
    {1, SW6_CS16, SW6_CS17, SW6_CS18},     // 120 SLED16
    {1, SW7_CS16, SW7_CS17, SW7_CS18},     // 121 SLED17
    {1, SW8_CS16, SW8_CS17, SW8_CS18},     // 122 SLED18
    {1, SW9_CS16, SW9_CS17, SW9_CS18},     // 123 SLED19
    {1, SW10_CS16, SW10_CS17, SW10_CS18},  // 124 SLED20

    {1, SW10_CS1, SW10_CS2, SW10_CS3},     // 125 LOGO
};

led_config_t g_led_config = {
    {   
        { 74, 75, 31, 100, 99, 102, 92, 5},
        { 38, 37, 59, 0, 76, 32, 16, 17},
        { 39, 58, 60, __, 77, 53, 1, 18},
        { 40, 3, 61, 4, 78, 87, 2, 19},
        { 41, 42, 62, 63, 79, 80, 21, 20},
        { 44, 43, 65, 64, 82, 81, 22, 23},
        { 45, 49, 66, 6, 83, 51, 28, 24},
        { 46, 7, 67, 101, 84, 30, 8, 25},
        { 47, 48, 68, 69, 98, 85, 27, 26},
        { 93, 86, 97, 94, 95, 96, 15, 13},
        { 14, 29, 50, 11, 70, 12, 9, 10},
        { 54, 71, 88, 57, 33, __, __, __},
        { 55, 72, 89, 103, 34, __, 52, __},
        { 56, 73, 90, 104, 35, 36, 91, __},
    },
    {
        {0,0},           {21,0},  {31,0},  {42,0},  {52,0},  {68,0},  {78,0},  {89,0},   {99,0},   {115,0},  {125,0},  {136,0},  {146,0},  {159,0},  {169,0},  {180,0},                      
        {0,15}, {10,15}, {21,15}, {31,15}, {42,15}, {52,15}, {63,15}, {73,15}, {83,15},  {94,15},  {104,15}, {115,15}, {125,15}, {141,15}, {159,15}, {169,15}, {180,15}, {193,15}, {203,15}, {214,15}, {224,15},
        {3,27}, {16,27}, {26,27}, {36,27}, {47,27}, {57,27}, {68,27}, {78,27}, {89,27},  {99,27},  {109,27}, {120,27}, {130,27}, {143,27}, {159,27}, {169,27}, {180,27}, {193,27}, {203,27}, {214,27}, {224,34},
        {4,40}, {18,40}, {29,40}, {39,40}, {50,40}, {60,40}, {70,40}, {81,40}, {91,40},  {102,40}, {112,40}, {123,40},           {139,40},                               {193,40}, {203,40}, {214,40},
        {1,52}, {12,52}, {23,52}, {34,52}, {44,52}, {55,52}, {65,52}, {76,52}, {86,52},  {96,52},  {107,52}, {117,52},           {137,52},           {169,52},           {193,52}, {203,52}, {214,52}, {224,58},
        {1,64}, {14,64}, {27,64},                            {66,64},                              {105,64}, {118,64}, {131,64}, {145,64}, {159,64}, {169,64}, {180,64}, {198,64},           {214,64},
        // Lef and right side lights
        {0, 15},  {0, 20},  {0, 25},  {0, 30},  {0, 35},  {0, 40},  {0, 45},  {0, 50},  {0, 55},  {0, 60},
        {224, 15},  {224, 20},  {224, 25},  {224, 30},  {224, 35},  {224, 40},  {224, 45},  {224, 50},  {224, 55},  {224, 60},
        // logo
        {214, 0},
    },
    {
        // Keyboard RGB Matrix
        4,    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    4,          4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    4,    4,    4, 4, 4, 4,
        4, 4, 4,          4,          4, 4, 4, 4, 4, 4, 4, 4,    4,
        // Lef and right side lights
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        // Logo 
        8,
    }
};
#endif // RGB_MATRIX_ENABLE

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