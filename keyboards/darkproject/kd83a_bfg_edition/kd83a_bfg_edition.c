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

const aw20216s_led_t PROGMEM g_aw20216s_leds[AW20216S_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |     R location
 *   |     |          G location
 *   |     |          |          B location
 *   |     |          |          | */
    //{0, CS1_SW4,   CS2_SW4,   CS3_SW4},   //   0, k00, Esc

    {0, CS1_SW1,   CS2_SW1,   CS3_SW1},   //   1, k13, Esc
    {0, CS1_SW2,   CS2_SW2,   CS3_SW2},   //   2, k26, F1
    {0, CS1_SW3,   CS2_SW3,   CS3_SW3},   //   3, k36, F2
    {0, CS1_SW4,   CS2_SW4,   CS3_SW4},   //   4, k31, F3
    {0, CS1_SW5,   CS2_SW5,   CS3_SW5},   //   5, k33, F4
    {0, CS1_SW6,   CS2_SW6,   CS3_SW6},   //   6, k07, F5
    {0, CS1_SW7,   CS2_SW7,   CS3_SW7},   //   7, k63, F6
    {0, CS1_SW8,   CS2_SW8,   CS3_SW8},   //   8, k71, F7
    {0, CS1_SW9,   CS2_SW9,   CS3_SW9},   //   9, k76, F8
    {0, CS1_SW10,  CS2_SW10,  CS3_SW10},  //  10, ka6, F9
    {0, CS1_SW11,  CS2_SW11,  CS3_SW11},  //  11, ka7, F10
    {0, CS1_SW12,  CS2_SW12,  CS3_SW12},  //  12, ka3, F11
    {1, CS1_SW1,   CS2_SW1,   CS3_SW1},   //  13, ka5, F12
    {1, CS4_SW2,   CS5_SW2,   CS6_SW2},   //  14, k97, Printscreen
    {1, CS4_SW5,   CS5_SW5,   CS6_SW5},   //  15, k02, Del

    {0, CS4_SW1,   CS5_SW1,   CS6_SW1},   //  16, k16, `
    {0, CS4_SW2,   CS5_SW2,   CS6_SW2},   //  17, k17, 1
    {0, CS4_SW3,   CS5_SW3,   CS6_SW3},   //  18, k27, 2
    {0, CS4_SW4,   CS5_SW4,   CS6_SW4},   //  19, k37, 3
    {0, CS4_SW5,   CS5_SW5,   CS6_SW5},   //  20, k47, 4
    {0, CS4_SW6,   CS5_SW6,   CS6_SW6},   //  21, k46, 5
    {0, CS4_SW7,   CS5_SW7,   CS6_SW7},   //  22, k56, 6
    {0, CS4_SW8,   CS5_SW8,   CS6_SW8},   //  23, k57, 7
    {0, CS4_SW9,   CS5_SW9,   CS6_SW9},   //  24, k67, 8
    {0, CS4_SW10,  CS5_SW10,  CS6_SW10},  //  25, k77, 9
    {0, CS4_SW11,  CS5_SW11,  CS6_SW11},  //  26, k87, 0
    {0, CS4_SW12,  CS5_SW12,  CS6_SW12},  //  27, k86, -
    {1, CS1_SW5,   CS2_SW5,   CS3_SW5},   //  28, k66, =
    {1, CS1_SW7,   CS2_SW7,   CS3_SW7},   //  29, ka1, Backspace
    {1, CS1_SW2,   CS2_SW2,   CS3_SW2},   //  30, kc6, Home

    {0, CS7_SW1,   CS8_SW1,   CS9_SW1},   //  31, k11, Tab
    {0, CS7_SW2,   CS8_SW2,   CS9_SW2},   //  32, k10, Q
    {0, CS7_SW3,   CS8_SW3,   CS9_SW3},   //  33, k20, W
    {0, CS7_SW4,   CS8_SW4,   CS9_SW4},   //  34, k30, E
    {0, CS7_SW5,   CS8_SW5,   CS9_SW5},   //  35, k40, R
    {0, CS7_SW6,   CS8_SW6,   CS9_SW6},   //  36, k41, T
    {0, CS7_SW7,   CS8_SW7,   CS9_SW7},   //  37, k51, Y
    {0, CS7_SW8,   CS8_SW8,   CS9_SW8},   //  38, k50, U
    {0, CS7_SW9,   CS8_SW9,   CS9_SW9},   //  39, k60, I
    {0, CS7_SW10,  CS8_SW10,  CS9_SW10},  //  40, k70, O
    {0, CS7_SW11,  CS8_SW11,  CS9_SW11},  //  41, k80, P
    {0, CS7_SW12,  CS8_SW12,  CS9_SW12},  //  42, k81, [
    {1, CS1_SW8,   CS2_SW8,   CS3_SW8},   //  43, k61, ]
    {1, CS1_SW9,   CS2_SW9,   CS3_SW9},   //  44, ka2, "\\"
    {1, CS4_SW3,   CS5_SW3,   CS6_SW3},   //  45, k65, End

    {0, CS10_SW1,  CS11_SW1,  CS12_SW1},  //  46, k21, Caps Lock
    {0, CS10_SW2,  CS11_SW2,  CS12_SW2},  //  47, k12, A
    {0, CS10_SW3,  CS11_SW3,  CS12_SW3},  //  48, k22, S
    {0, CS10_SW4,  CS11_SW4,  CS12_SW4},  //  49, k32, D
    {0, CS10_SW5,  CS11_SW5,  CS12_SW5},  //  50, k42, F
    {0, CS10_SW6,  CS11_SW6,  CS12_SW6},  //  51, k43, G
    {0, CS10_SW7,  CS11_SW7,  CS12_SW7},  //  52, k53, H
    {0, CS10_SW8,  CS11_SW8,  CS12_SW8},  //  53, k52, J
    {0, CS10_SW9,  CS11_SW9,  CS12_SW9},  //  54, k62, K
    {0, CS10_SW10, CS11_SW10, CS12_SW10}, //  55, k72, L
    {0, CS10_SW11, CS11_SW11, CS12_SW11}, //  56, k82, ;
    {0, CS10_SW12, CS11_SW12, CS12_SW12}, //  57, k83, '
    {1, CS1_SW11,  CS2_SW11,  CS3_SW11},  //  58, ka4, Enter
    {1, CS4_SW4,   CS5_SW4,   CS6_SW4},   //  59, k15, PgUp

    {0, CS13_SW1,  CS14_SW1,  CS15_SW1},  //  60, k00, Shift_L
    {0, CS13_SW2,  CS14_SW2,  CS15_SW2},  //  61, k14, Z
    {0, CS13_SW3,  CS14_SW3,  CS15_SW3},  //  62, k24, X
    {0, CS13_SW4,  CS14_SW4,  CS15_SW4},  //  63, k34, C
    {0, CS13_SW5,  CS14_SW5,  CS15_SW5},  //  64, k44, V
    {0, CS13_SW6,  CS14_SW6,  CS15_SW6},  //  65, k45, B
    {0, CS13_SW7,  CS14_SW7,  CS15_SW7},  //  66, k55, N
    {0, CS13_SW8,  CS14_SW8,  CS15_SW8},  //  67, k54, M
    {0, CS13_SW9,  CS14_SW9,  CS15_SW9},  //  68, k64, ,
    {0, CS13_SW10, CS14_SW10, CS15_SW10}, //  69, k74, .
    {0, CS13_SW11, CS14_SW11, CS15_SW11}, //  70, k85, /
    {1, CS4_SW8,   CS5_SW8,   CS6_SW8},   //  71, k91, Shift_R
    {1, CS4_SW9,   CS5_SW9,   CS6_SW9},   //  72, k35, Up
    {1, CS4_SW7,   CS5_SW7,   CS6_SW7},   //  73, k25, PgDn

    {0, CS16_SW1,  CS17_SW1,  CS18_SW1},  //  74, k06, Ctrl_L
    {0, CS16_SW2,  CS17_SW2,  CS18_SW2},  //  75, k90, Win_L
    {0, CS16_SW3,  CS17_SW3,  CS18_SW3},  //  76, k93, Alt_L
    {0, CS16_SW6,  CS17_SW6,  CS18_SW6},  //  77, k94, Space
    {0, CS16_SW9,  CS17_SW9,  CS18_SW9},  //  78, k95, Alt_R
    {0, CS16_SW10, CS17_SW10, CS18_SW10}, //  79, k92, FN
    {0, CS16_SW12, CS17_SW12, CS18_SW12}, //  80, k04, Ctrl_R
    {1, CS4_SW10,  CS5_SW10,  CS6_SW10},  //  81, k03, Left
    {1, CS4_SW11,  CS5_SW11,  CS6_SW11},  //  82, k73, Down
    {1, CS10_SW5,  CS11_SW5,  CS12_SW5},  //  83, k05, Right

    {1, CS10_SW10, CS11_SW10, CS12_SW10}, //  84, kb0, Z1
    {1, CS10_SW11, CS11_SW11, CS12_SW11}, //  85, kb1, Z2
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

void keyboard_pre_init_kb(void) {
    setPinOutput(C0);
    setPinOutput(C15);
    keyboard_pre_init_user();
};
void housekeeping_task_kb(void) {
    writePin(C15, keymap_config.no_gui);
};

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
     if (!process_record_user(keycode, record)) {
        return false;
    }
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

#if defined(ENCODER_ENABLE)
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) {
        return false;
    }
    if (clockwise) {
        tap_code(KC_VOLU);
    } else {
        tap_code(KC_VOLD);
    }
    return false;
};
#endif