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

#include "ansi.h"

#ifdef RGB_MATRIX_ENABLE

const aw_led g_aw_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |     R location
 *   |     |          G location
 *   |     |          |          B location
 *   |     |          |          | */
    //{0, CS1_SW4,   CS2_SW4,   CS3_SW4},   //   0, k00, Esc

    {0, CS1_SW1,   CS2_SW1,   CS3_SW1},   //  Esc
    {0, CS1_SW2,   CS2_SW2,   CS3_SW2},   //  F1
    {0, CS1_SW3,   CS2_SW3,   CS3_SW3},   //  F2
    {0, CS1_SW4,   CS2_SW4,   CS3_SW4},   //  F3
    {0, CS1_SW5,   CS2_SW5,   CS3_SW5},   //  F4
    {0, CS1_SW6,   CS2_SW6,   CS3_SW6},   //  F5
    {0, CS1_SW7,   CS2_SW7,   CS3_SW7},   //  F6
    {0, CS1_SW8,   CS2_SW8,   CS3_SW8},   //  F7
    {0, CS1_SW9,   CS2_SW9,   CS3_SW9},   //  F8
    {0, CS1_SW10,  CS2_SW10,  CS3_SW10},  //  F9
    {0, CS1_SW11,  CS2_SW11,  CS3_SW11},  //  F10
    {0, CS1_SW12,  CS2_SW12,  CS3_SW12},  //  F11
    {1, CS1_SW1,   CS2_SW1,   CS3_SW1},   //  F12
    {1, CS4_SW1,   CS5_SW1,   CS6_SW1},   //  Printscreen
    {1, CS4_SW3,   CS5_SW3,   CS6_SW3},   //  Delete

    {0, CS4_SW1,   CS5_SW1,   CS6_SW1},   //  `
    {0, CS4_SW2,   CS5_SW2,   CS6_SW2},   //  1
    {0, CS4_SW3,   CS5_SW3,   CS6_SW3},   //  2
    {0, CS4_SW4,   CS5_SW4,   CS6_SW4},   //  3
    {0, CS4_SW5,   CS5_SW5,   CS6_SW5},   //  4
    {0, CS4_SW6,   CS5_SW6,   CS6_SW6},   //  5
    {0, CS4_SW7,   CS5_SW7,   CS6_SW7},   //  6
    {0, CS4_SW8,   CS5_SW8,   CS6_SW8},   //  7
    {0, CS4_SW9,   CS5_SW9,   CS6_SW9},   //  8
    {0, CS4_SW10,  CS5_SW10,  CS6_SW10},  //  9
    {0, CS4_SW11,  CS5_SW11,  CS6_SW11},  //  0
    {0, CS4_SW12,  CS5_SW12,  CS6_SW12},  //  -
    {1, CS1_SW5,   CS2_SW5,   CS3_SW5},   //  =
    {1, CS1_SW7,   CS2_SW7,   CS3_SW7},   //  Backspace
    {1, CS4_SW5,   CS5_SW5,   CS6_SW5},   //  Home

    {0, CS7_SW1,   CS8_SW1,   CS9_SW1},   //  Tab
    {0, CS7_SW2,   CS8_SW2,   CS9_SW2},   //  Q
    {0, CS7_SW3,   CS8_SW3,   CS9_SW3},   //  W
    {0, CS7_SW4,   CS8_SW4,   CS9_SW4},   //  E
    {0, CS7_SW5,   CS8_SW5,   CS9_SW5},   //  R
    {0, CS7_SW6,   CS8_SW6,   CS9_SW6},   //  T
    {0, CS7_SW7,   CS8_SW7,   CS9_SW7},   //  Y
    {0, CS7_SW8,   CS8_SW8,   CS9_SW8},   //  U
    {0, CS7_SW9,   CS8_SW9,   CS9_SW9},   //  I
    {0, CS7_SW10,  CS8_SW10,  CS9_SW10},  //  O
    {0, CS7_SW11,  CS8_SW11,  CS9_SW11},  //  P
    {0, CS7_SW12,  CS8_SW12,  CS9_SW12},  //  [
    {1, CS1_SW8,   CS2_SW8,   CS3_SW8},   //  ]
    {1, CS1_SW9,   CS2_SW9,   CS3_SW9},   //  "\\"
    {1, CS4_SW4,   CS5_SW4,   CS6_SW4},   //  PGUP

    {0, CS10_SW1,  CS11_SW1,  CS12_SW1},  //  Caps Lock
    {0, CS10_SW2,  CS11_SW2,  CS12_SW2},  //  A
    {0, CS10_SW3,  CS11_SW3,  CS12_SW3},  //  S
    {0, CS10_SW4,  CS11_SW4,  CS12_SW4},  //  D
    {0, CS10_SW5,  CS11_SW5,  CS12_SW5},  //  F
    {0, CS10_SW6,  CS11_SW6,  CS12_SW6},  //  G
    {0, CS10_SW7,  CS11_SW7,  CS12_SW7},  //  H
    {0, CS10_SW8,  CS11_SW8,  CS12_SW8},  //  J
    {0, CS10_SW9,  CS11_SW9,  CS12_SW9},  //  K
    {0, CS10_SW10, CS11_SW10, CS12_SW10}, //  L
    {0, CS10_SW11, CS11_SW11, CS12_SW11}, //  ;
    {0, CS10_SW12, CS11_SW12, CS12_SW12}, //  '
    {1, CS1_SW11,  CS2_SW11,  CS3_SW11},  //  Enter
    {1, CS4_SW7,   CS5_SW7,   CS6_SW7},   //  PGDN

    {0, CS13_SW1,  CS14_SW1,  CS15_SW1},  //  L Shift
    {0, CS13_SW2,  CS14_SW2,  CS15_SW2},  //  Z
    {0, CS13_SW3,  CS14_SW3,  CS15_SW3},  //  X
    {0, CS13_SW4,  CS14_SW4,  CS15_SW4},  //  C
    {0, CS13_SW5,  CS14_SW5,  CS15_SW5},  //  V
    {0, CS13_SW6,  CS14_SW6,  CS15_SW6},  //  B
    {0, CS13_SW7,  CS14_SW7,  CS15_SW7},  //  N
    {0, CS13_SW8,  CS14_SW8,  CS15_SW8},  //  M
    {0, CS13_SW9,  CS14_SW9,  CS15_SW9},  //  ,
    {0, CS13_SW10, CS14_SW10, CS15_SW10}, //  .
    {0, CS13_SW11, CS14_SW11, CS15_SW11}, //  "/""
    {1, CS4_SW8,   CS5_SW8,   CS6_SW8},   //  R Shift
    {1, CS4_SW9,   CS5_SW9,   CS6_SW9},   //  Up
    {1, CS4_SW6,   CS5_SW6,   CS6_SW6},   //  END

    {0, CS16_SW1,  CS17_SW1,  CS18_SW1},  //  L Ctrl
    {0, CS16_SW2,  CS17_SW2,  CS18_SW2},  //  L Win
    {0, CS16_SW3,  CS17_SW3,  CS18_SW3},  //  L Alt
    {0, CS16_SW4,  CS17_SW4,  CS18_SW4},  //  LED1
    {0, CS16_SW5,  CS17_SW5,  CS18_SW5},  //  LED2
    {0, CS16_SW6,  CS17_SW6,  CS18_SW6},  //  Space
    {0, CS16_SW7,  CS17_SW7,  CS18_SW7},  //  LED3
    {0, CS16_SW8,  CS17_SW8,  CS18_SW8},  //  LED4
    {0, CS16_SW9,  CS17_SW9,  CS18_SW9},  //  R Alt
    {0, CS16_SW10, CS17_SW10, CS18_SW10}, //  FN
    {0, CS16_SW12, CS17_SW12, CS18_SW12}, //  R Ctrl

    {1, CS4_SW10,  CS5_SW10,  CS6_SW10},  //  Left
    {1, CS4_SW11,  CS5_SW11,  CS6_SW11},  //  Down
    {1, CS10_SW5,  CS11_SW5,  CS12_SW5},  //  Right
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

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {

    if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) {
        return false;
    }
    if (host_keyboard_led_state().caps_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(45, 255, 255, 255);
    }

    return false;

}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {

        case RGB_R:
            if (record->event.pressed) {
                rgb_matrix_sethsv(0, 255, 255);
                rgb_matrix_mode(1);
            }
            return false; /* Skip all further processing of this key */

        case RGB_G:
            if (record->event.pressed) {
                rgb_matrix_sethsv(85, 255, 255);
                rgb_matrix_mode(1);
            }
            return false; /* Skip all further processing of this key */

        case RGB_B:
            if (record->event.pressed) {
                rgb_matrix_sethsv(170, 255, 255);
                rgb_matrix_mode(1);
            }
            return false; /* Skip all further processing of this key */

        case RGB_W:
            if (record->event.pressed) {
                rgb_matrix_sethsv(0, 0, 255);
                rgb_matrix_mode(1);
            }
            return false; /* Skip all further processing of this key */

        case SW_cy:
            rgb_matrix_sethsv(0, 255, 255);
            rgb_matrix_mode(13);
            return false; /* Skip all further processing of this key */

        
        default:
            return true; /* Process all other keycodes normally */
    }
};
