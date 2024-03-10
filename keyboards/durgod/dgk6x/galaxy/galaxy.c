/* Copyright 2021 Don Kjer 
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

const is31fl3733_led_t PROGMEM g_is31fl3733_leds[IS31FL3733_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */

   {0, SW3_CS1,   SW2_CS1,   SW1_CS1},  // Esc
   {0, SW3_CS2,   SW2_CS2,   SW1_CS2},  // F1
   {0, SW3_CS3,   SW2_CS3,   SW1_CS3},  // F2
   {0, SW3_CS4,   SW2_CS4,   SW1_CS4},  // F3
   {0, SW3_CS5,   SW2_CS5,   SW1_CS5},  // F4
   {0, SW3_CS6,   SW2_CS6,   SW1_CS6},  // F5
   {0, SW3_CS7,   SW2_CS7,   SW1_CS7},  // F6
   {0, SW3_CS8,   SW2_CS8,   SW1_CS8},  // F7
   {0, SW3_CS9,   SW2_CS9,   SW1_CS9},  // F8
   {0, SW3_CS10,  SW2_CS10,  SW1_CS10}, // F9
   {0, SW3_CS11,  SW2_CS11,  SW1_CS11}, // F10
   {0, SW3_CS12,  SW2_CS12,  SW1_CS12}, // F11
   {0, SW3_CS13,  SW2_CS13,  SW1_CS13}, // F12
   {0, SW3_CS14,  SW2_CS14,  SW1_CS14}, // PrtSc
   {0, SW3_CS15,  SW2_CS15,  SW1_CS15}, // Pause
   {0, SW3_CS16,  SW2_CS16,  SW1_CS16}, // Del

   {0, SW6_CS1,   SW5_CS1,   SW4_CS1},  // `
   {0, SW6_CS2,   SW5_CS2,   SW4_CS2},  // 1
   {0, SW6_CS3,   SW5_CS3,   SW4_CS3},  // 2
   {0, SW6_CS4,   SW5_CS4,   SW4_CS4},  // 3
   {0, SW6_CS5,   SW5_CS5,   SW4_CS5},  // 4
   {0, SW6_CS6,   SW5_CS6,   SW4_CS6},  // 5
   {0, SW6_CS7,   SW5_CS7,   SW4_CS7},  // 6
   {0, SW6_CS8,   SW5_CS8,   SW4_CS8},  // 7
   {0, SW6_CS9,   SW5_CS9,   SW4_CS9},  // 8
   {0, SW6_CS10,  SW5_CS10,  SW4_CS10}, // 9
   {0, SW6_CS11,  SW5_CS11,  SW4_CS11}, // 0
   {0, SW6_CS12,  SW5_CS12,  SW4_CS12}, // -
   {0, SW6_CS13,  SW5_CS13,  SW4_CS13}, // =
   {0, SW6_CS14,  SW5_CS14,  SW4_CS14}, // Bksp
   {0, SW6_CS15,  SW5_CS15,  SW4_CS15}, // Home

   {0, SW9_CS1,   SW8_CS1,   SW7_CS1},  // Tab
   {0, SW9_CS2,   SW8_CS2,   SW7_CS2},  // Q
   {0, SW9_CS3,   SW8_CS3,   SW7_CS3},  // W
   {0, SW9_CS4,   SW8_CS4,   SW7_CS4},  // E
   {0, SW9_CS5,   SW8_CS5,   SW7_CS5},  // R
   {0, SW9_CS6,   SW8_CS6,   SW7_CS6},  // T
   {0, SW9_CS7,   SW8_CS7,   SW7_CS7},  // Y
   {0, SW9_CS8,   SW8_CS8,   SW7_CS8},  // U
   {0, SW9_CS9,   SW8_CS9,   SW7_CS9},  // I
   {0, SW9_CS10,  SW8_CS10,  SW7_CS10}, // O
   {0, SW9_CS11,  SW8_CS11,  SW7_CS11}, // P
   {0, SW9_CS12,  SW8_CS12,  SW7_CS12}, // [
   {0, SW9_CS13,  SW8_CS13,  SW7_CS13}, // ]
   {0, SW9_CS14,  SW8_CS14,  SW7_CS14}, // Pipe
   {0, SW9_CS15,  SW8_CS15,  SW7_CS15}, // End

   {0, SW12_CS1,   SW11_CS1,   SW10_CS1},  // Caps
   {0, SW12_CS2,   SW11_CS2,   SW10_CS2},  // A
   {0, SW12_CS3,   SW11_CS3,   SW10_CS3},  // S
   {0, SW12_CS4,   SW11_CS4,   SW10_CS4},  // D
   {0, SW12_CS5,   SW11_CS5,   SW10_CS5},  // F
   {0, SW12_CS6,   SW11_CS6,   SW10_CS6},  // G
   {0, SW12_CS7,   SW11_CS7,   SW10_CS7},  // H
   {0, SW12_CS8,   SW11_CS8,   SW10_CS8},  // J
   {0, SW12_CS9,   SW11_CS9,   SW10_CS9},  // K
   {0, SW12_CS10,  SW11_CS10,  SW10_CS10}, // L
   {0, SW12_CS11,  SW11_CS11,  SW10_CS11}, // :
   {0, SW12_CS12,  SW11_CS12,  SW10_CS12}, // '
   {0, SW12_CS14,  SW11_CS14,  SW10_CS14}, // Enter
   {0, SW12_CS15,  SW11_CS15,  SW10_CS15}, // PgUp

   {1, SW3_CS1,   SW2_CS1,   SW1_CS1},  // LShift
   {1, SW3_CS3,   SW2_CS3,   SW1_CS3},  // Z
   {1, SW3_CS4,   SW2_CS4,   SW1_CS4},  // X
   {1, SW3_CS5,   SW2_CS5,   SW1_CS5},  // C
   {1, SW3_CS6,   SW2_CS6,   SW1_CS6},  // V
   {1, SW3_CS7,   SW2_CS7,   SW1_CS7},  // B
   {1, SW3_CS8,   SW2_CS8,   SW1_CS8},  // N
   {1, SW3_CS9,   SW2_CS9,   SW1_CS9},  // M
   {1, SW3_CS10,  SW2_CS10,  SW1_CS10}, // <
   {1, SW3_CS11,  SW2_CS11,  SW1_CS11}, // >
   {1, SW3_CS12,  SW2_CS12,  SW1_CS12}, // ?
   {1, SW3_CS13,  SW2_CS13,  SW1_CS13}, // RShift
   {1, SW3_CS14,  SW2_CS14,  SW1_CS14}, // Up
   {1, SW3_CS15,  SW2_CS15,  SW1_CS15}, // PgDn

   {1, SW6_CS1,   SW5_CS1,   SW4_CS1},  // LCtrl
   {1, SW6_CS2,   SW5_CS2,   SW4_CS2},  // LAlt
   {1, SW6_CS3,   SW5_CS3,   SW4_CS3},  // LGUI
   {1, SW6_CS7,   SW5_CS7,   SW4_CS7},  // Space
   {1, SW6_CS10,  SW5_CS10,  SW4_CS10}, // RAlt
   {1, SW6_CS11,  SW5_CS11,  SW4_CS11}, // Fn1
   {1, SW6_CS12,  SW5_CS12,  SW4_CS12}, // Fn2
   {1, SW6_CS13,  SW5_CS13,  SW4_CS13}, // Left
   {1, SW6_CS14,  SW5_CS14,  SW4_CS14}, // Down
   {1, SW6_CS15,  SW5_CS15,  SW4_CS15}  // Right
};

led_config_t g_led_config = {{
    { 0,  1,      2,  3,      4,      5,      6,  7,      8,      9,  10, 11, 12,     13, 14, 15     },
    { 16, 17,     18, 19,     20,     21,     22, 23,     24,     25, 26, 27, 28,     29, 30, NO_LED },
    { 31, 32,     33, 34,     35,     36,     37, 38,     39,     40, 41, 42, 43,     44, 45, NO_LED },
    { 46, 47,     48, 49,     50,     51,     52, 53,     54,     55, 56, 57, NO_LED, 58, 59, NO_LED },
    { 60, NO_LED, 61, 62,     63,     64,     65, 66,     67,     68, 69, 70, 71,     72, 73, NO_LED },
    { 74, 75,     76, NO_LED, NO_LED, NO_LED, 77, NO_LED, NO_LED, 78, 79, 80, 81,     82, 83, NO_LED }
}, {
    {  0,  0 }, { 16,  0 }, { 32,  0 }, { 48,  0 }, { 64,  0 }, { 80,  0 }, { 96,   0 }, { 112,  0 }, { 128,  0 }, { 144,  0 }, { 160,  0 }, { 176,  0 }, { 192,  0 }, { 208,  0 }, { 224,  0 }, { 240,  0 },
    {  0, 13 }, { 16, 13 }, { 32, 13 }, { 48, 13 }, { 64, 13 }, { 80, 13 }, { 96,  13 }, { 112, 13 }, { 128, 13 }, { 144, 13 }, { 160, 13 }, { 176, 13 }, { 192, 13 },              { 216, 13 }, { 240, 13 },
    {  4, 26 }, { 24, 26 }, { 40, 26 }, { 56, 26 }, { 72, 26 }, { 88, 26 }, { 104, 26 }, { 120, 26 }, { 136, 26 }, { 152, 26 }, { 168, 26 }, { 184, 26 }, { 200, 26 },              { 220, 26 }, { 240, 26 },
    {  6, 38 }, { 28, 38 }, { 44, 38 }, { 60, 38 }, { 76, 38 }, { 92, 38 }, { 108, 38 }, { 124, 38 }, { 140, 38 }, { 156, 38 }, { 172, 38 }, { 188, 38 },                           { 214, 38 }, { 240, 38 },
    { 10, 51 },             { 36, 51 }, { 52, 51 }, { 68, 51 }, { 84, 51 }, { 100, 51 }, { 116, 51 }, { 132, 51 }, { 148, 51 }, { 164, 51 }, { 180, 51 },              { 202, 51 }, { 224, 51 }, { 240, 51 },
    {  2, 64 }, { 22, 64 }, { 42, 64 },                                     { 101, 64 },                                        { 160, 64 }, { 176, 64 }, { 192, 64 }, { 208, 64 }, { 224, 64 }, { 240, 64 }
}, {
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    1, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,       1, 4,
    1,    4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    1, 4, 4,
    1, 1, 1,          4,          1, 1, 1, 4, 4, 4
}};
#endif /* RGB_MATRIX_ENABLE */
