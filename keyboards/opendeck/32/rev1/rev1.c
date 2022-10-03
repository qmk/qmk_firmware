/* Copyright 2020 cmdremily
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

#include "rev1.h"

#ifdef RGB_MATRIX_ENABLE
const is31_led PROGMEM g_is31_leds[DRIVER_LED_TOTAL] = {
    /* Refer to IS31 manual for these locations
     *   driver
     *   |  R location
     *   |  |      G location
     *   |  |      |      B location
     *   |  |      |      | */
    // clang-format off
    {0, C4_1, C5_1, C6_1},
    {0, C4_2, C5_2, C6_2},
    {0, C4_3, C5_3, C6_3},
    {0, C1_4, C2_4, C3_4},
    {0, C4_9, C5_9, C6_9},
    {0, C4_10, C5_10, C6_10},
    {0, C4_11, C5_11, C6_11},
    {0, C1_12, C2_12, C3_12},

    {0, C7_1, C8_1, C9_1},
    {0, C7_2, C8_2, C9_2},
    {0, C7_3, C8_3, C9_3},
    {0, C7_4, C8_4, C9_4},
    {0, C7_9, C8_9, C9_9},
    {0, C7_10, C8_10, C9_10},
    {0, C7_11, C8_11, C9_11},
    {0, C7_12, C8_12, C9_12},

    {0, C1_5, C2_5, C3_5},
    {0, C1_6, C2_6, C3_6},
    {0, C1_7, C2_7, C3_7},
    {0, C1_8, C2_8, C3_8},
    {0, C1_13, C2_13, C3_13},
    {0, C1_14, C2_14, C3_14},
    {0, C1_15, C2_15, C3_15},
    {0, C1_16, C2_16, C3_16},

    {0, C7_5, C8_5, C9_5},
    {0, C7_6, C8_6, C9_6},
    {0, C4_7, C5_7, C6_7},
    {0, C4_8, C5_8, C6_8},
    {0, C7_13, C8_13, C9_13},
    {0, C7_14, C8_14, C9_14},
    {0, C4_15, C5_15, C6_15},
    {0, C4_16, C5_16, C6_16},
    // clang-format on
};

#define P(x,y) {(x*224 / (MATRIX_COLS - 1)), (y*64 / (MATRIX_ROWS - 1))}
// clang-format off
led_config_t g_led_config = {
    // Key Matrix to LED Index
    {
        {0,  1,  2,  3,  4,  5,  6,  7},
        {8,  9,  10, 11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20, 21, 22, 23},
        {24, 25, 26, 27, 28, 29, 30, 31}
    }, {
        // LED Index to Physical Position
        P(0, 0), P(1, 0), P(2, 0), P(3, 0), P(4, 0), P(5, 0), P(6, 0), P(7, 0),
        P(0, 1), P(1, 1), P(2, 1), P(3, 1), P(4, 1), P(5, 1), P(6, 1), P(7, 1),
        P(0, 2), P(1, 2), P(2, 2), P(3, 2), P(4, 2), P(5, 2), P(6, 2), P(7, 2),
        P(0, 3), P(1, 3), P(2, 3), P(3, 3), P(4, 3), P(5, 3), P(6, 3), P(7, 3),
    }, {
        // LED Index to Flag
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
    }
};
#undef P

// clang-format on

// Set custom key colors here, in order to change the RGB effect, either reserve some keys
// in the keymap to adjust the pattern (see QMK docs, incompatible with wrapper keys) or
// change the default pattern in config.h.
/*
void rgb_matrix_indicators_kb(void) {
    //rgb_matrix_set_color(0, 255, 255, 255);
    //rgb_matrix_set_color_all(0x86,0xff,0xff);
}
*/

void keyboard_pre_init_kb(void) {
    // Light power LED
    setPinOutput(POWER_LED_PIN);
    writePinLow(POWER_LED_PIN);

    // Enable RGB driver IC
    setPinOutput(RGB_DISABLE_N_PIN);
    writePinHigh(RGB_DISABLE_N_PIN);

    // We don't use this feature of the IS31FL3731 but it is electrically connected
    // Make sure not to drive it
    setPinInput(RGB_IRQ_N_PIN);
}

void keyboard_post_init_user() {
    // RGB enabled by default, no way to turn off. No need to expend EEPROM write cycles here.
    rgb_matrix_enable_noeeprom();
}
#endif

#if defined(KC_WRAPPER_KEY)

static uint8_t g_key_wrapper_tracker = 0;

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record) { return false; }
    if (record->event.pressed && keycode != KC_WRAPPER_KEY) {
        register_code(KC_WRAPPER_KEY);
        register_code(keycode);
        g_key_wrapper_tracker++;
        return false;
    }
    return true;
}

void post_process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed && keycode != KC_WRAPPER_KEY) {
        --g_key_wrapper_tracker;
        if (g_key_wrapper_tracker <= 0) {
            unregister_code(KC_WRAPPER_KEY);
            g_key_wrapper_tracker = 0;
        }
    }
    post_process_record_user(keycode, record);
}
#endif
