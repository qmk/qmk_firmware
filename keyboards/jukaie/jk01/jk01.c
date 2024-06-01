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

const aw20216s_led_t PROGMEM g_aw20216s_leds[AW20216S_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |     R location
 *   |     |          G location
 *   |     |          |          B location
 *   |     |          |          | */
    //{0, SW4_CS1,   SW4_CS2,   SW4_CS3},   //   0, k00, Esc

    {0, SW1_CS1,   SW1_CS2,   SW1_CS3},   //   1, k13, Esc
    {0, SW2_CS1,   SW2_CS2,   SW2_CS3},   //   2, k26, F1
    {0, SW3_CS1,   SW3_CS2,   SW3_CS3},   //   3, k36, F2
    {0, SW4_CS1,   SW4_CS2,   SW4_CS3},   //   4, k31, F3
    {0, SW5_CS1,   SW5_CS2,   SW5_CS3},   //   5, k33, F4
    {0, SW6_CS1,   SW6_CS2,   SW6_CS3},   //   6, k07, F5
    {0, SW7_CS1,   SW7_CS2,   SW7_CS3},   //   7, k63, F6
    {0, SW8_CS1,   SW8_CS2,   SW8_CS3},   //   8, k71, F7
    {0, SW9_CS1,   SW9_CS2,   SW9_CS3},   //   9, k76, F8
    {0, SW10_CS1,  SW10_CS2,  SW10_CS3},  //  10, ka6, F9
    {0, SW11_CS1,  SW11_CS2,  SW11_CS3},  //  11, ka7, F10
    {0, SW12_CS1,  SW12_CS2,  SW12_CS3},  //  12, ka3, F11
    {1, SW1_CS1,   SW1_CS2,   SW1_CS3},   //  13, ka5, F12
    {1, SW2_CS4,   SW2_CS5,   SW2_CS6},   //  14, k97, Printscreen
    {1, SW5_CS4,   SW5_CS5,   SW5_CS6},   //  15, k02, Del

    {0, SW1_CS4,   SW1_CS5,   SW1_CS6},   //  16, k16, `
    {0, SW2_CS4,   SW2_CS5,   SW2_CS6},   //  17, k17, 1
    {0, SW3_CS4,   SW3_CS5,   SW3_CS6},   //  18, k27, 2
    {0, SW4_CS4,   SW4_CS5,   SW4_CS6},   //  19, k37, 3
    {0, SW5_CS4,   SW5_CS5,   SW5_CS6},   //  20, k47, 4
    {0, SW6_CS4,   SW6_CS5,   SW6_CS6},   //  21, k46, 5
    {0, SW7_CS4,   SW7_CS5,   SW7_CS6},   //  22, k56, 6
    {0, SW8_CS4,   SW8_CS5,   SW8_CS6},   //  23, k57, 7
    {0, SW9_CS4,   SW9_CS5,   SW9_CS6},   //  24, k67, 8
    {0, SW10_CS4,  SW10_CS5,  SW10_CS6},  //  25, k77, 9
    {0, SW11_CS4,  SW11_CS5,  SW11_CS6},  //  26, k87, 0
    {0, SW12_CS4,  SW12_CS5,  SW12_CS6},  //  27, k86, -
    {1, SW5_CS1,   SW5_CS2,   SW5_CS3},   //  28, k66, =
    {1, SW7_CS1,   SW7_CS2,   SW7_CS3},   //  29, ka1, Backspace
    {1, SW2_CS1,   SW2_CS2,   SW2_CS3},   //  30, kc6, Home

    {0, SW1_CS7,   SW1_CS8,   SW1_CS9},   //  31, k11, Tab
    {0, SW2_CS7,   SW2_CS8,   SW2_CS9},   //  32, k10, Q
    {0, SW3_CS7,   SW3_CS8,   SW3_CS9},   //  33, k20, W
    {0, SW4_CS7,   SW4_CS8,   SW4_CS9},   //  34, k30, E
    {0, SW5_CS7,   SW5_CS8,   SW5_CS9},   //  35, k40, R
    {0, SW6_CS7,   SW6_CS8,   SW6_CS9},   //  36, k41, T
    {0, SW7_CS7,   SW7_CS8,   SW7_CS9},   //  37, k51, Y
    {0, SW8_CS7,   SW8_CS8,   SW8_CS9},   //  38, k50, U
    {0, SW9_CS7,   SW9_CS8,   SW9_CS9},   //  39, k60, I
    {0, SW10_CS7,  SW10_CS8,  SW10_CS9},  //  40, k70, O
    {0, SW11_CS7,  SW11_CS8,  SW11_CS9},  //  41, k80, P
    {0, SW12_CS7,  SW12_CS8,  SW12_CS9},  //  42, k81, [
    {1, SW8_CS1,   SW8_CS2,   SW8_CS3},   //  43, k61, ]
    {1, SW9_CS1,   SW9_CS2,   SW9_CS3},   //  44, ka2, "\\"
    {1, SW3_CS4,   SW3_CS5,   SW3_CS6},   //  45, k65, End

    {0, SW1_CS10,  SW1_CS11,  SW1_CS12},  //  46, k21, Caps Lock
    {0, SW2_CS10,  SW2_CS11,  SW2_CS12},  //  47, k12, A
    {0, SW3_CS10,  SW3_CS11,  SW3_CS12},  //  48, k22, S
    {0, SW4_CS10,  SW4_CS11,  SW4_CS12},  //  49, k32, D
    {0, SW5_CS10,  SW5_CS11,  SW5_CS12},  //  50, k42, F
    {0, SW6_CS10,  SW6_CS11,  SW6_CS12},  //  51, k43, G
    {0, SW7_CS10,  SW7_CS11,  SW7_CS12},  //  52, k53, H
    {0, SW8_CS10,  SW8_CS11,  SW8_CS12},  //  53, k52, J
    {0, SW9_CS10,  SW9_CS11,  SW9_CS12},  //  54, k62, K
    {0, SW10_CS10, SW10_CS11, SW10_CS12}, //  55, k72, L
    {0, SW11_CS10, SW11_CS11, SW11_CS12}, //  56, k82, ;
    {0, SW12_CS10, SW12_CS11, SW12_CS12}, //  57, k83, '
    {1, SW11_CS1,  SW11_CS2,  SW11_CS3},  //  58, ka4, Enter
    {1, SW4_CS4,   SW4_CS5,   SW4_CS6},   //  59, k15, PgUp

    {0, SW1_CS13,  SW1_CS14,  SW1_CS15},  //  60, k00, Shift_L
    {0, SW2_CS13,  SW2_CS14,  SW2_CS15},  //  61, k14, Z
    {0, SW3_CS13,  SW3_CS14,  SW3_CS15},  //  62, k24, X
    {0, SW4_CS13,  SW4_CS14,  SW4_CS15},  //  63, k34, C
    {0, SW5_CS13,  SW5_CS14,  SW5_CS15},  //  64, k44, V
    {0, SW6_CS13,  SW6_CS14,  SW6_CS15},  //  65, k45, B
    {0, SW7_CS13,  SW7_CS14,  SW7_CS15},  //  66, k55, N
    {0, SW8_CS13,  SW8_CS14,  SW8_CS15},  //  67, k54, M
    {0, SW9_CS13,  SW9_CS14,  SW9_CS15},  //  68, k64, ,
    {0, SW10_CS13, SW10_CS14, SW10_CS15}, //  69, k74, .
    {0, SW11_CS13, SW11_CS14, SW11_CS15}, //  70, k85, /
    {1, SW8_CS4,   SW8_CS5,   SW8_CS6},   //  71, k91, Shift_R
    {1, SW9_CS4,   SW9_CS5,   SW9_CS6},   //  72, k35, Up
    {1, SW7_CS4,   SW7_CS5,   SW7_CS6},   //  73, k25, PgDn

    {0, SW1_CS16,  SW1_CS17,  SW1_CS18},  //  74, k06, Ctrl_L
    {0, SW2_CS16,  SW2_CS17,  SW2_CS18},  //  75, k90, Win_L
    {0, SW3_CS16,  SW3_CS17,  SW3_CS18},  //  76, k93, Alt_L
    {0, SW6_CS16,  SW6_CS17,  SW6_CS18},  //  77, k94, Space
    {0, SW9_CS16,  SW9_CS17,  SW9_CS18},  //  78, k95, Alt_R
    {0, SW10_CS16, SW10_CS17, SW10_CS18}, //  79, k92, FN
    {0, SW12_CS16, SW12_CS17, SW12_CS18}, //  80, k04, Ctrl_R
    {1, SW10_CS4,  SW10_CS5,  SW10_CS6},  //  81, k03, Left
    {1, SW11_CS4,  SW11_CS5,  SW11_CS6},  //  82, k73, Down
    {1, SW5_CS10,  SW5_CS11,  SW5_CS12},  //  83, k05, Right

    {1, SW10_CS10, SW10_CS11, SW10_CS12}, //  84, kb0, Z1
    {1, SW11_CS10, SW11_CS11, SW11_CS12}, //  85, kb1, Z2
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

void keyboard_pre_init_kb(void) {
    gpio_set_pin_output(C0);
    gpio_set_pin_output(C15);
    keyboard_pre_init_user();
};
void housekeeping_task_kb(void) {
    gpio_write_pin(C15, keymap_config.no_gui);
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {

        case KC_SIRI:
            if (record->event.pressed) {
                host_consumer_send(0xCF);
            } else {
                host_consumer_send(0);
            }
            return false; /* Skip all further processing of this key */

        default:
            return true; /* Process all other keycodes normally */
    }
};