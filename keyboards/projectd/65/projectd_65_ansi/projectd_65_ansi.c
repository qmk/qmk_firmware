/* Copyright 2023 GSKY <gskyGit@gsky.com.tw>
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
    //{0, SW4_CS1,   SW4_CS2,   SW4_CS3},   //   0, Esc

    {0, SW1_CS1,   SW1_CS2,   SW1_CS3},   //  0, Esc
    {0, SW2_CS4,   SW2_CS5,   SW2_CS6},   //  1, 1
    {0, SW3_CS4,   SW3_CS5,   SW3_CS6},   //  2, 2
    {0, SW4_CS4,   SW4_CS5,   SW4_CS6},   //  3, 3
    {0, SW5_CS4,   SW5_CS5,   SW5_CS6},   //  4, 4
    {0, SW6_CS4,   SW6_CS5,   SW6_CS6},   //  5, 5
    {0, SW7_CS4,   SW7_CS5,   SW7_CS6},   //  6, 6
    {0, SW8_CS4,   SW8_CS5,   SW8_CS6},   //  7, 7
    {0, SW9_CS4,   SW9_CS5,   SW9_CS6},   //  8, 8
    {0, SW10_CS4,  SW10_CS5,  SW10_CS6},  //  9, 9
    {0, SW11_CS4,  SW11_CS5,  SW11_CS6},  //  10, 0
    {0, SW12_CS4,  SW12_CS5,  SW12_CS6},  //  11, -
    {0, SW9_CS1,   SW9_CS2,   SW9_CS3},   //  12, =
    {0, SW10_CS1,  SW10_CS2,  SW10_CS3},  //  13, Backspace
    {0, SW5_CS1,   SW5_CS2,   SW5_CS3},   //  14, Del

    {0, SW1_CS4,   SW1_CS5,   SW1_CS6},   //  15, Tab
    {0, SW2_CS7,   SW2_CS8,   SW2_CS9},   //  16, Q
    {0, SW3_CS7,   SW3_CS8,   SW3_CS9},   //  17, W
    {0, SW4_CS7,   SW4_CS8,   SW4_CS9},   //  18, E
    {0, SW5_CS7,   SW5_CS8,   SW5_CS9},   //  19, R
    {0, SW6_CS7,   SW6_CS8,   SW6_CS9},   //  20, T
    {0, SW7_CS7,   SW7_CS8,   SW7_CS9},   //  21, Y
    {0, SW8_CS7,   SW8_CS8,   SW8_CS9},   //  22, U
    {0, SW9_CS7,   SW9_CS8,   SW9_CS9},   //  23, I
    {0, SW10_CS7,  SW10_CS8,  SW10_CS9},  //  24, O
    {0, SW11_CS7,  SW11_CS8,  SW11_CS9},  //  25, P
    {0, SW12_CS7,  SW12_CS8,  SW12_CS9},  //  26, [
    {0, SW11_CS1,  SW11_CS2,  SW11_CS3},  //  27, ]
    {0, SW12_CS1,  SW12_CS2,  SW12_CS3},  //  28, "\\"
    {0, SW4_CS1,   SW4_CS2,   SW4_CS3},   //  29, PGUP

    {0, SW1_CS7,   SW1_CS8,   SW1_CS9},   //  30, CapsLock
    {0, SW2_CS10,  SW2_CS11,  SW2_CS12},  //  31, A
    {0, SW3_CS10,  SW3_CS11,  SW3_CS12},  //  32, S
    {0, SW4_CS10,  SW4_CS11,  SW4_CS12},  //  33, D
    {0, SW5_CS10,  SW5_CS11,  SW5_CS12},  //  34, F
    {0, SW6_CS10,  SW6_CS11,  SW6_CS12},  //  35, G
    {0, SW7_CS10,  SW7_CS11,  SW7_CS12},  //  36, H
    {0, SW8_CS10,  SW8_CS11,  SW8_CS12},  //  37, J
    {0, SW9_CS10,  SW9_CS11,  SW9_CS12},  //  38, K
    {0, SW10_CS10, SW10_CS11, SW10_CS12}, //  39, L
    {0, SW11_CS10, SW11_CS11, SW11_CS12}, //  40, ;
    {0, SW12_CS10, SW12_CS11, SW12_CS12}, //  41, '
    {0, SW12_CS13, SW12_CS14, SW12_CS15}, //  42, Enter
    {0, SW7_CS1,   SW7_CS2,   SW7_CS3},   //  43, PGDN

    {0, SW1_CS10,  SW1_CS11,  SW1_CS12},  //  44, LShift
    {0, SW2_CS13,  SW2_CS14,  SW2_CS15},  //  45, Z
    {0, SW3_CS13,  SW3_CS14,  SW3_CS15},  //  46, X
    {0, SW4_CS13,  SW4_CS14,  SW4_CS15},  //  47, C
    {0, SW5_CS13,  SW5_CS14,  SW5_CS15},  //  48, V
    {0, SW6_CS13,  SW6_CS14,  SW6_CS15},  //  49, B
    {0, SW7_CS13,  SW7_CS14,  SW7_CS15},  //  50, N
    {0, SW8_CS13,  SW8_CS14,  SW8_CS15},  //  51, M
    {0, SW9_CS13,  SW9_CS14,  SW9_CS15},  //  52, ,
    {0, SW10_CS13, SW10_CS14, SW10_CS15}, //  53, .
    {0, SW11_CS13, SW11_CS14, SW11_CS15}, //  54, /
    {0, SW8_CS16,  SW8_CS17,  SW8_CS18},  //  55, RShift
    {0, SW9_CS16,  SW9_CS17,  SW9_CS18},  //  56, Up
    {0,  SW6_CS1,   SW6_CS2,   SW6_CS3},  //  57, END

    {0, SW1_CS16,  SW1_CS17,  SW1_CS18},  //  58, LCtrl
    {0, SW2_CS16,  SW2_CS17,  SW2_CS18},  //  59, LWin
    {0, SW3_CS16,  SW3_CS17,  SW3_CS18},  //  60, LAlt
    {0,  SW2_CS1,   SW2_CS2,   SW2_CS3},  //  61, LED71
    {0,  SW3_CS1,   SW3_CS2,   SW3_CS3},  //  62, LED72
    {0, SW4_CS16,  SW4_CS17,  SW4_CS18},  //  63, Space
    {0, SW7_CS16,  SW7_CS17,  SW7_CS18},  //  64, LED73
    {0,  SW8_CS1,   SW8_CS2,   SW8_CS3},  //  65, LED74
    {0, SW5_CS16,  SW5_CS17,  SW5_CS18},  //  66, RAlt
    {0, SW6_CS16,  SW6_CS17,  SW6_CS18},  //  67, FN

    {0, SW10_CS16, SW10_CS17, SW10_CS18}, //  68, Left
    {0, SW11_CS16, SW11_CS17, SW11_CS18}, //  69, Down
    {0, SW12_CS16, SW12_CS17, SW12_CS18}, //  70, Right

};

#endif

#ifdef EEPROM_ENABLE

#include "spi_master.h"

void spi_init(void) {
    static bool is_initialised = false;
    if (!is_initialised) {
        is_initialised = true;

        // Try releasing special pins for a short time
        gpio_set_pin_input(SPI_SCK_PIN);
        gpio_set_pin_input(SPI_MOSI_PIN);
        gpio_set_pin_input(SPI_MISO_PIN);

        chThdSleepMilliseconds(10);

        palSetPadMode(PAL_PORT(SPI_SCK_PIN), PAL_PAD(SPI_SCK_PIN), PAL_MODE_ALTERNATE(SPI_SCK_PAL_MODE) | PAL_OUTPUT_TYPE_PUSHPULL | PAL_OUTPUT_SPEED_HIGHEST | PAL_WB32_CURRENT_LEVEL3);
        palSetPadMode(PAL_PORT(SPI_MOSI_PIN), PAL_PAD(SPI_MOSI_PIN), PAL_MODE_ALTERNATE(SPI_MOSI_PAL_MODE) | PAL_OUTPUT_TYPE_PUSHPULL | PAL_OUTPUT_SPEED_HIGHEST);
        palSetPadMode(PAL_PORT(SPI_MISO_PIN), PAL_PAD(SPI_MISO_PIN), PAL_MODE_ALTERNATE(SPI_MISO_PAL_MODE) | PAL_OUTPUT_TYPE_PUSHPULL | PAL_OUTPUT_SPEED_HIGHEST);
    }
}

#endif

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) {
        return false;
}
   if (host_keyboard_led_state().caps_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(30, 255, 255, 255); // assuming caps lock is at led #30
    }
    return false;
}
