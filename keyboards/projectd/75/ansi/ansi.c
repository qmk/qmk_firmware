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

const aw20216s_led_t PROGMEM g_aw20216s_leds[AW20216S_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |     R location
 *   |     |          G location
 *   |     |          |          B location
 *   |     |          |          | */
    //{0, SW4_CS1,   SW4_CS2,   SW4_CS3},   //   0, k00, Esc

    {0, SW1_CS1,   SW1_CS2,   SW1_CS3},   //  Esc
    {0, SW2_CS1,   SW2_CS2,   SW2_CS3},   //  F1
    {0, SW3_CS1,   SW3_CS2,   SW3_CS3},   //  F2
    {0, SW4_CS1,   SW4_CS2,   SW4_CS3},   //  F3
    {0, SW5_CS1,   SW5_CS2,   SW5_CS3},   //  F4
    {0, SW6_CS1,   SW6_CS2,   SW6_CS3},   //  F5
    {0, SW7_CS1,   SW7_CS2,   SW7_CS3},   //  F6
    {0, SW8_CS1,   SW8_CS2,   SW8_CS3},   //  F7
    {0, SW9_CS1,   SW9_CS2,   SW9_CS3},   //  F8
    {0, SW10_CS1,  SW10_CS2,  SW10_CS3},  //  F9
    {0, SW11_CS1,  SW11_CS2,  SW11_CS3},  //  F10
    {0, SW12_CS1,  SW12_CS2,  SW12_CS3},  //  F11
    {1, SW1_CS1,   SW1_CS2,   SW1_CS3},   //  F12
    {1, SW1_CS4,   SW1_CS5,   SW1_CS6},   //  Printscreen
    {1, SW3_CS4,   SW3_CS5,   SW3_CS6},   //  Delete

    {0, SW1_CS4,   SW1_CS5,   SW1_CS6},   //  `
    {0, SW2_CS4,   SW2_CS5,   SW2_CS6},   //  1
    {0, SW3_CS4,   SW3_CS5,   SW3_CS6},   //  2
    {0, SW4_CS4,   SW4_CS5,   SW4_CS6},   //  3
    {0, SW5_CS4,   SW5_CS5,   SW5_CS6},   //  4
    {0, SW6_CS4,   SW6_CS5,   SW6_CS6},   //  5
    {0, SW7_CS4,   SW7_CS5,   SW7_CS6},   //  6
    {0, SW8_CS4,   SW8_CS5,   SW8_CS6},   //  7
    {0, SW9_CS4,   SW9_CS5,   SW9_CS6},   //  8
    {0, SW10_CS4,  SW10_CS5,  SW10_CS6},  //  9
    {0, SW11_CS4,  SW11_CS5,  SW11_CS6},  //  0
    {0, SW12_CS4,  SW12_CS5,  SW12_CS6},  //  -
    {1, SW5_CS1,   SW5_CS2,   SW5_CS3},   //  =
    {1, SW7_CS1,   SW7_CS2,   SW7_CS3},   //  Backspace
    {1, SW5_CS4,   SW5_CS5,   SW5_CS6},   //  Home

    {0, SW1_CS7,   SW1_CS8,   SW1_CS9},   //  Tab
    {0, SW2_CS7,   SW2_CS8,   SW2_CS9},   //  Q
    {0, SW3_CS7,   SW3_CS8,   SW3_CS9},   //  W
    {0, SW4_CS7,   SW4_CS8,   SW4_CS9},   //  E
    {0, SW5_CS7,   SW5_CS8,   SW5_CS9},   //  R
    {0, SW6_CS7,   SW6_CS8,   SW6_CS9},   //  T
    {0, SW7_CS7,   SW7_CS8,   SW7_CS9},   //  Y
    {0, SW8_CS7,   SW8_CS8,   SW8_CS9},   //  U
    {0, SW9_CS7,   SW9_CS8,   SW9_CS9},   //  I
    {0, SW10_CS7,  SW10_CS8,  SW10_CS9},  //  O
    {0, SW11_CS7,  SW11_CS8,  SW11_CS9},  //  P
    {0, SW12_CS7,  SW12_CS8,  SW12_CS9},  //  [
    {1, SW8_CS1,   SW8_CS2,   SW8_CS3},   //  ]
    {1, SW9_CS1,   SW9_CS2,   SW9_CS3},   //  "\\"
    {1, SW4_CS4,   SW4_CS5,   SW4_CS6},   //  PGUP

    {0, SW1_CS10,  SW1_CS11,  SW1_CS12},  //  Caps Lock
    {0, SW2_CS10,  SW2_CS11,  SW2_CS12},  //  A
    {0, SW3_CS10,  SW3_CS11,  SW3_CS12},  //  S
    {0, SW4_CS10,  SW4_CS11,  SW4_CS12},  //  D
    {0, SW5_CS10,  SW5_CS11,  SW5_CS12},  //  F
    {0, SW6_CS10,  SW6_CS11,  SW6_CS12},  //  G
    {0, SW7_CS10,  SW7_CS11,  SW7_CS12},  //  H
    {0, SW8_CS10,  SW8_CS11,  SW8_CS12},  //  J
    {0, SW9_CS10,  SW9_CS11,  SW9_CS12},  //  K
    {0, SW10_CS10, SW10_CS11, SW10_CS12}, //  L
    {0, SW11_CS10, SW11_CS11, SW11_CS12}, //  ;
    {0, SW12_CS10, SW12_CS11, SW12_CS12}, //  '
    {1, SW11_CS1,  SW11_CS2,  SW11_CS3},  //  Enter
    {1, SW7_CS4,   SW7_CS5,   SW7_CS6},   //  PGDN

    {0, SW1_CS13,  SW1_CS14,  SW1_CS15},  //  L Shift
    {0, SW2_CS13,  SW2_CS14,  SW2_CS15},  //  Z
    {0, SW3_CS13,  SW3_CS14,  SW3_CS15},  //  X
    {0, SW4_CS13,  SW4_CS14,  SW4_CS15},  //  C
    {0, SW5_CS13,  SW5_CS14,  SW5_CS15},  //  V
    {0, SW6_CS13,  SW6_CS14,  SW6_CS15},  //  B
    {0, SW7_CS13,  SW7_CS14,  SW7_CS15},  //  N
    {0, SW8_CS13,  SW8_CS14,  SW8_CS15},  //  M
    {0, SW9_CS13,  SW9_CS14,  SW9_CS15},  //  ,
    {0, SW10_CS13, SW10_CS14, SW10_CS15}, //  .
    {0, SW11_CS13, SW11_CS14, SW11_CS15}, //  "/""
    {1, SW8_CS4,   SW8_CS5,   SW8_CS6},   //  R Shift
    {1, SW9_CS4,   SW9_CS5,   SW9_CS6},   //  Up
    {1, SW6_CS4,   SW6_CS5,   SW6_CS6},   //  END

    {0, SW1_CS16,  SW1_CS17,  SW1_CS18},  //  L Ctrl
    {0, SW2_CS16,  SW2_CS17,  SW2_CS18},  //  L Win
    {0, SW3_CS16,  SW3_CS17,  SW3_CS18},  //  L Alt
    {0, SW4_CS16,  SW4_CS17,  SW4_CS18},  //  LED1
    {0, SW5_CS16,  SW5_CS17,  SW5_CS18},  //  LED2
    {0, SW6_CS16,  SW6_CS17,  SW6_CS18},  //  Space
    {0, SW7_CS16,  SW7_CS17,  SW7_CS18},  //  LED3
    {0, SW8_CS16,  SW8_CS17,  SW8_CS18},  //  LED4
    {0, SW9_CS16,  SW9_CS17,  SW9_CS18},  //  R Alt
    {0, SW10_CS16, SW10_CS17, SW10_CS18}, //  FN
    {0, SW12_CS16, SW12_CS17, SW12_CS18}, //  R Ctrl

    {1, SW10_CS4,  SW10_CS5,  SW10_CS6},  //  Left
    {1, SW11_CS4,  SW11_CS5,  SW11_CS6},  //  Down
    {1, SW5_CS10,  SW5_CS11,  SW5_CS12},  //  Right
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
