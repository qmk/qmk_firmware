/* Copyright 2022 GSKY <gskyGit@gsky.com.tw>
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

#include "kd83a_bfg_edition.h"

#ifdef RGB_MATRIX_ENABLE

const aw_led g_aw_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |     R location
 *   |     |          G location
 *   |     |          |          B location
 *   |     |          |          | */
    //{0, CS1_SW4,   CS2_SW4,   CS3_SW4},   //   0, k00, Esc
    
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
    {1, CS4_SW5,   CS5_SW5,   CS6_SW5},   //  14, k56, Del
  
    {0, CS4_SW1,   CS5_SW1,   CS6_SW1},   //  15, k01, `
    {0, CS4_SW2,   CS5_SW2,   CS6_SW2},   //  16, k11, 1
    {0, CS4_SW3,   CS5_SW3,   CS6_SW3},   //  17, k21, 2
    {0, CS4_SW4,   CS5_SW4,   CS6_SW4},   //  18, k31, 3
    {0, CS4_SW5,   CS5_SW5,   CS6_SW5},   //  19, k41, 4
    {0, CS4_SW6,   CS5_SW6,   CS6_SW6},   //  20, k51, 5
    {0, CS4_SW7,   CS5_SW7,   CS6_SW7},   //  21, k61, 6
    {0, CS4_SW8,   CS5_SW8,   CS6_SW8},   //  22, k71, 7
    {0, CS4_SW9,   CS5_SW9,   CS6_SW9},   //  23, k81, 8
    {0, CS4_SW10,  CS5_SW10,  CS6_SW10},  //  24, k91, 9
    {0, CS4_SW11,  CS5_SW11,  CS6_SW11},  //  25, ka1, 0
    {0, CS4_SW12,  CS5_SW12,  CS6_SW12},  //  26, kb1, -
    {1, CS1_SW5,   CS2_SW5,   CS3_SW5},   //  27, kc1, =
    {1, CS1_SW7,   CS2_SW7,   CS3_SW7},   //  28, kd1, Backspace
    {1, CS1_SW2,   CS2_SW2,   CS3_SW2},   //  29, k16, Home

    {0, CS7_SW1,   CS8_SW1,   CS9_SW1},   //  30, k02, Tab
    {0, CS7_SW2,   CS8_SW2,   CS9_SW2},   //  31, k12, Q
    {0, CS7_SW3,   CS8_SW3,   CS9_SW3},   //  32, k22, W
    {0, CS7_SW4,   CS8_SW4,   CS9_SW4},   //  33, k32, E
    {0, CS7_SW5,   CS8_SW5,   CS9_SW5},   //  34, k42, R
    {0, CS7_SW6,   CS8_SW6,   CS9_SW6},   //  35, k52, T
    {0, CS7_SW7,   CS8_SW7,   CS9_SW7},   //  36, k62, Y
    {0, CS7_SW8,   CS8_SW8,   CS9_SW8},   //  37, k72, U
    {0, CS7_SW9,   CS8_SW9,   CS9_SW9},   //  38, k82, I
    {0, CS7_SW10,  CS8_SW10,  CS9_SW10},  //  39, k92, O
    {0, CS7_SW11,  CS8_SW11,  CS9_SW11},  //  40, ka2, P
    {0, CS7_SW12,  CS8_SW12,  CS9_SW12},  //  41, kb2, [
    {1, CS1_SW8,   CS2_SW8,   CS3_SW8},   //  42, kc2, ]
    {1, CS1_SW9,   CS2_SW9,   CS3_SW9},   //  43, kd3, "\\"
    {1, CS4_SW3,   CS5_SW3,   CS6_SW3},   //  44, k06, End
  
    {0, CS10_SW1,  CS11_SW1,  CS12_SW1},  //  45, k03, Caps Lock
    {0, CS10_SW2,  CS11_SW2,  CS12_SW2},  //  46, k13, A
    {0, CS10_SW3,  CS11_SW3,  CS12_SW3},  //  47, k23, S
    {0, CS10_SW4,  CS11_SW4,  CS12_SW4},  //  48, k33, D
    {0, CS10_SW5,  CS11_SW5,  CS12_SW5},  //  49, k43, F
    {0, CS10_SW6,  CS11_SW6,  CS12_SW6},  //  50, k53, G
    {0, CS10_SW7,  CS11_SW7,  CS12_SW7},  //  51, k63, H
    {0, CS10_SW8,  CS11_SW8,  CS12_SW8},  //  52, k73, J
    {0, CS10_SW9,  CS11_SW9,  CS12_SW9},  //  53, k83, K
    {0, CS10_SW10, CS11_SW10, CS12_SW10}, //  54, k93, L
    {0, CS10_SW11, CS11_SW11, CS12_SW11}, //  55, ka3, ;
    {0, CS10_SW12, CS11_SW12, CS12_SW12}, //  56, kb3, '
    {1, CS1_SW11,  CS2_SW11,  CS3_SW11},  //  57, kc3, Enter
    {1, CS4_SW4,   CS5_SW4,   CS6_SW4},   //  58, k26, PgUp
   
    {0, CS13_SW1,  CS14_SW1,  CS15_SW1},  //  59, k04, Shift_L
    {0, CS13_SW2,  CS14_SW2,  CS15_SW2},  //  60, k24, Z
    {0, CS13_SW3,  CS14_SW3,  CS15_SW3},  //  61, k34, X
    {0, CS13_SW4,  CS14_SW4,  CS15_SW4},  //  62, k44, C
    {0, CS13_SW5,  CS14_SW5,  CS15_SW5},  //  63, k54, V
    {0, CS13_SW6,  CS14_SW6,  CS15_SW6},  //  64, k64, B
    {0, CS13_SW7,  CS14_SW7,  CS15_SW7},  //  65, k74, N
    {0, CS13_SW8,  CS14_SW8,  CS15_SW8},  //  66, k84, M
    {0, CS13_SW9,  CS14_SW9,  CS15_SW9},  //  67, k94, ,
    {0, CS13_SW10, CS14_SW10, CS15_SW10}, //  68, ka4, .
    {0, CS13_SW11, CS14_SW11, CS15_SW11}, //  69, kb4, /
    {1, CS4_SW8,   CS5_SW8,   CS6_SW8},   //  70, kd4, Shift_R
    {1, CS4_SW9,   CS5_SW9,   CS6_SW9},   //  71, k17, Up
    {1, CS4_SW7,   CS5_SW7,   CS6_SW7},   //  72, k36, PgDn

    {0, CS16_SW1,  CS17_SW1,  CS18_SW1},  //  73, k05, Ctrl_L
    {0, CS16_SW2,  CS17_SW2,  CS18_SW2},  //  74, k15, Win_L
    {0, CS16_SW3,  CS17_SW3,  CS18_SW3},  //  75, k25, Alt_L
    {0, CS16_SW6,  CS17_SW6,  CS18_SW6},  //  76, k65, Space
    {0, CS16_SW9,  CS17_SW9,  CS18_SW9},  //  77, k95, Alt_R
    {0, CS16_SW10, CS17_SW10, CS18_SW10}, //  78, ka5, FN
    {0, CS16_SW12, CS17_SW12, CS18_SW12}, //  79, kc5, Ctrl_R
    {1, CS4_SW10,  CS5_SW10,  CS6_SW10},  //  80, k07, Left
    {1, CS4_SW11,  CS5_SW11,  CS6_SW11},  //  81, k27, Down
    {1, CS10_SW5,  CS11_SW5,  CS12_SW5},  //  82, k37, Right
   
    {1, CS10_SW10, CS11_SW10, CS12_SW10}, //  83, Z1
    {1, CS10_SW11, CS11_SW11, CS12_SW11}, //  84, Z2  
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
    { 83, __, __, __, __, __, __, __},
    { __, __, __, __, __, __, 29, __},
    { 84, __, __, __, __, __, __, __} 
},
{
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
    { 165,   0}, //  14, k56, Home
   
    {  11,  11}, //  15, k01, `
    {  22,  11}, //  16, k11, 1
    {  33,  11}, //  17, k21, 2
    {  44,  11}, //  18, k31, 3
    {  55,  11}, //  19, k41, 4
    {  66,  11}, //  20, k51, 5
    {  77,  11}, //  21, k61, 6
    {  88,  11}, //  22, k71, 7
    {  99,  11}, //  23, k81, 8
    { 110,  11}, //  24, k91, 9
    { 121,  11}, //  25, ka1, 0
    { 132,  11}, //  26, kb1, -
    { 143,  11}, //  27, kc1, =
    { 154,  11}, //  28, kd1, Backspace
    { 165,  11}, //  29, k16, Ins
  
    {  11,  22}, //  30, k02, Tab
    {  22,  22}, //  31, k12, Q
    {  33,  22}, //  32, k22, W
    {  44,  22}, //  33, k32, E
    {  55,  22}, //  34, k42, R
    {  66,  22}, //  35, k52, T
    {  77,  22}, //  36, k62, Y
    {  88,  22}, //  37, k72, U
    {  99,  22}, //  38, k82, I
    { 110,  22}, //  39, k92, O
    { 121,  22}, //  40, ka2, P
    { 132,  22}, //  41, kb2, [
    { 143,  22}, //  42, kc2, ]
    { 154,  22}, //  43, kd3, "\\"
    { 165,  22}, //  44, k06, Del

    {  11,  33}, //  45, k03, Caps Lock
    {  22,  33}, //  46, k13, A
    {  33,  33}, //  47, k23, S
    {  44,  33}, //  48, k33, D
    {  55,  33}, //  49, k43, F
    {  66,  33}, //  50, k53, G
    {  77,  33}, //  51, k63, H
    {  88,  33}, //  52, k73, J
    {  99,  33}, //  53, k83, K
    { 110,  33}, //  54, k93, L
    { 121,  33}, //  55, ka3, ;
    { 132,  33}, //  56, kb3, '
    { 154,  33}, //  57, kc3, Enter
    { 165,  33}, //  58, k26, PgUp
   
    {  11,  44}, //  59, k04, Shift_L
    {  33,  44}, //  60, k24, Z
    {  44,  44}, //  61, k34, X
    {  55,  44}, //  62, k44, C
    {  66,  44}, //  63, k54, V
    {  77,  44}, //  64, k64, B
    {  88,  44}, //  65, k74, N
    {  99,  44}, //  66, k84, M
    { 110,  44}, //  67, k94, ,
    { 121,  44}, //  68, ka4, .
    { 132,  44}, //  69, kb4, /
    { 143,  44}, //  70, kd4, Shift_R
    { 154,  44}, //  70, k17, Up
    { 165,  44}, //  72, k36, PgDn

    {  11,  55}, //  73, k05, Ctrl_L
    {  22,  55}, //  74, k15, Win_L
    {  33,  55}, //  75, k25, Alt_L
    {  77,  55}, //  76, k65, Space
    { 110,  55}, //  77, k95, Alt_R
    { 121,  55}, //  78, ka5, FN
    { 132,  55}, //  79, kc5, Ctrl_R
    { 143,  55}, //  80, k07, Left
    { 154,  55}, //  81, k27, Down
    { 165,  55}, //  82, k37, Right  
     
    {   0,  18}, // 83, Z1
    {   0,  24}, // 84, Z2  
}, 
{
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    8, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4,
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

