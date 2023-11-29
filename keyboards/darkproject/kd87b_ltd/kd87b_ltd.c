/* Copyright 2023 SHVD3x
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

const aw20216s_led_t g_aw20216s_leds[RGB_MATRIX_LED_COUNT] = {
/* Each AW20216S channel is controlled by a register at some offset between 0x00
 * and 0xD7 inclusive.
 * See drivers/led/aw20216s.h for the mapping between register offsets and
 * driver pin locations.
 *   driver
 *   |  R location
 *   |  |          G location
 *   |  |          |          B location
 *   |  |          |          | */
    //{0, CS1_SW1,   CS2_SW1,   CS3_SW1},   //   0, Esc
    
    {0, CS1_SW1,   CS2_SW1,   CS3_SW1},   //   0, Esc
    {0, CS1_SW2,   CS2_SW2,   CS3_SW2},   //   1, F1
    {0, CS1_SW3,   CS2_SW3,   CS3_SW3},   //   2, F2
    {0, CS1_SW4,   CS2_SW4,   CS3_SW4},   //   3, F3
    {0, CS1_SW5,   CS2_SW5,   CS3_SW5},   //   4, F4
    {0, CS1_SW6,   CS2_SW6,   CS3_SW6},   //   5, F5
    {0, CS1_SW7,   CS2_SW7,   CS3_SW7},   //   6, F6
    {0, CS1_SW8,   CS2_SW8,   CS3_SW8},   //   7, F7
    {0, CS1_SW9,   CS2_SW9,   CS3_SW9},   //   8, F8
    {0, CS1_SW10,  CS2_SW10,  CS3_SW10},  //   9, F9
    {0, CS1_SW11,  CS2_SW11,  CS3_SW11},  //  10, F10
    {0, CS1_SW12,  CS2_SW12,  CS3_SW12},  //  11, F11
    {1, CS1_SW1,   CS2_SW1,   CS3_SW1},   //  12, F12
    {1, CS4_SW2,   CS5_SW2,   CS6_SW2},   //  13, Printscreen
    {1, CS1_SW3,   CS2_SW3,   CS3_SW3},   //  14, ScrollLock
    {1, CS1_SW4,   CS2_SW4,   CS3_SW4},   //  15, PauseBreak

    {0, CS4_SW1,   CS5_SW1,   CS6_SW1},   //  16, `
    {0, CS4_SW2,   CS5_SW2,   CS6_SW2},   //  17, 1
    {0, CS4_SW3,   CS5_SW3,   CS6_SW3},   //  18, 2
    {0, CS4_SW4,   CS5_SW4,   CS6_SW4},   //  19, 3
    {0, CS4_SW5,   CS5_SW5,   CS6_SW5},   //  20, 4
    {0, CS4_SW6,   CS5_SW6,   CS6_SW6},   //  21, 5
    {0, CS4_SW7,   CS5_SW7,   CS6_SW7},   //  22, 6
    {0, CS4_SW8,   CS5_SW8,   CS6_SW8},   //  23, 7
    {0, CS4_SW9,   CS5_SW9,   CS6_SW9},   //  24, 8
    {0, CS4_SW10,  CS5_SW10,  CS6_SW10},  //  25, 9
    {0, CS4_SW11,  CS5_SW11,  CS6_SW11},  //  26, 0
    {0, CS4_SW12,  CS5_SW12,  CS6_SW12},  //  27, -
    {1, CS1_SW5,   CS2_SW5,   CS3_SW5},   //  28, =
    {1, CS1_SW7,   CS2_SW7,   CS3_SW7},   //  29, Backspace
    {1, CS1_SW2,   CS2_SW2,   CS3_SW2},   //  30, Insert
    {1, CS4_SW5,   CS5_SW5,   CS6_SW5},   //  31, Home
    {1, CS4_SW4,   CS5_SW4,   CS6_SW4},   //  32, Pageup

    {0, CS7_SW1,   CS8_SW1,   CS9_SW1},   //  33, Tab
    {0, CS7_SW2,   CS8_SW2,   CS9_SW2},   //  34, Q
    {0, CS7_SW3,   CS8_SW3,   CS9_SW3},   //  35, W
    {0, CS7_SW4,   CS8_SW4,   CS9_SW4},   //  36, E
    {0, CS7_SW5,   CS8_SW5,   CS9_SW5},   //  37, R
    {0, CS7_SW6,   CS8_SW6,   CS9_SW6},   //  38, T
    {0, CS7_SW7,   CS8_SW7,   CS9_SW7},   //  39, Y
    {0, CS7_SW8,   CS8_SW8,   CS9_SW8},   //  40, U
    {0, CS7_SW9,   CS8_SW9,   CS9_SW9},   //  41, I
    {0, CS7_SW10,  CS8_SW10,  CS9_SW10},  //  42, O
    {0, CS7_SW11,  CS8_SW11,  CS9_SW11},  //  43, P
    {0, CS7_SW12,  CS8_SW12,  CS9_SW12},  //  44, [
    {1, CS1_SW8,   CS2_SW8,   CS3_SW8},   //  45, ]
    {1, CS1_SW9,   CS2_SW9,   CS3_SW9},   //  46, "\\"
    {1, CS4_SW3,   CS5_SW3,   CS6_SW3},   //  47, Delete
    {1, CS4_SW6,   CS5_SW6,   CS6_SW6},   //  48, End
    {1, CS4_SW7,   CS5_SW7,   CS6_SW7},   //  49, Pagedown
  
    {0, CS10_SW1,  CS11_SW1,  CS12_SW1},  //  50, Caps Lock
    {0, CS10_SW2,  CS11_SW2,  CS12_SW2},  //  51, A
    {0, CS10_SW3,  CS11_SW3,  CS12_SW3},  //  52, S
    {0, CS10_SW4,  CS11_SW4,  CS12_SW4},  //  53, D
    {0, CS10_SW5,  CS11_SW5,  CS12_SW5},  //  54, F
    {0, CS10_SW6,  CS11_SW6,  CS12_SW6},  //  55, G
    {0, CS10_SW7,  CS11_SW7,  CS12_SW7},  //  56, H
    {0, CS10_SW8,  CS11_SW8,  CS12_SW8},  //  57, J
    {0, CS10_SW9,  CS11_SW9,  CS12_SW9},  //  58, K
    {0, CS10_SW10, CS11_SW10, CS12_SW10}, //  59, L
    {0, CS10_SW11, CS11_SW11, CS12_SW11}, //  60, ;
    {0, CS10_SW12, CS11_SW12, CS12_SW12}, //  61, '
    {1, CS1_SW11,  CS2_SW11,  CS3_SW11},  //  62, Enter

    {0, CS13_SW1,  CS14_SW1,  CS15_SW1},  //  63, Shift_L
    {0, CS13_SW2,  CS14_SW2,  CS15_SW2},  //  64, Z
    {0, CS13_SW3,  CS14_SW3,  CS15_SW3},  //  65, X
    {0, CS13_SW4,  CS14_SW4,  CS15_SW4},  //  66, C
    {0, CS13_SW5,  CS14_SW5,  CS15_SW5},  //  67, V
    {0, CS13_SW6,  CS14_SW6,  CS15_SW6},  //  68, B
    {0, CS13_SW7,  CS14_SW7,  CS15_SW7},  //  69, N
    {0, CS13_SW8,  CS14_SW8,  CS15_SW8},  //  70, M
    {0, CS13_SW9,  CS14_SW9,  CS15_SW9},  //  71, ,
    {0, CS13_SW10, CS14_SW10, CS15_SW10}, //  72, .
    {0, CS13_SW11, CS14_SW11, CS15_SW11}, //  73, /
    {1, CS4_SW8,   CS5_SW8,   CS6_SW8},   //  74, Shift_R
    {1, CS4_SW9,   CS5_SW9,   CS6_SW9},   //  75, Up

    {0, CS16_SW1,  CS17_SW1,  CS18_SW1},  //  76, Ctrl_L
    {0, CS16_SW2,  CS17_SW2,  CS18_SW2},  //  77, Win_L
    {0, CS16_SW3,  CS17_SW3,  CS18_SW3},  //  78, Alt_L
    {0, CS16_SW6,  CS17_SW6,  CS18_SW6},  //  79, Space
    {0, CS16_SW9,  CS17_SW9,  CS18_SW9},  //  80, Alt_R
    {0, CS16_SW10, CS17_SW10, CS18_SW10}, //  81, FN
    {0, CS16_SW11, CS17_SW11, CS18_SW11}, //  82, App
    {0, CS16_SW12, CS17_SW12, CS18_SW12}, //  83, Ctrl_R
    {1, CS4_SW10,  CS5_SW10,  CS6_SW10},  //  84, Left
    {1, CS4_SW11,  CS5_SW11,  CS6_SW11},  //  85, Down
    {1, CS10_SW5,  CS11_SW5,  CS12_SW5},  //  86, Right
};
#endif

void led_init_ports(void) {
  setPinOutput(C0);
  setPinOutput(C14);
  setPinOutput(C15);
  writePinLow(C0);
  writePinLow(C14);
  writePinLow(C15);
};
