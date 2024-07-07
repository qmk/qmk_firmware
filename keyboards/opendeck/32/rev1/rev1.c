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
const is31fl3731_led_t PROGMEM g_is31fl3731_leds[IS31FL3731_LED_COUNT] = {
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

// clang-format off
led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        {  0,  1,  2,  3,  4,  5,  6,  7 },
        {  8,  9, 10, 11, 12, 13, 14, 15 },
        { 16, 17, 18, 19, 20, 21, 22, 23 },
        { 24, 25, 26, 27, 28, 29, 30, 31 }
    }, {
        // LED Index to Physical Position
        { 0,  0 }, { 32,  0 }, { 64,  0 }, { 96,  0 }, { 128,  0 }, { 160,  0 }, { 192,  0 }, { 224,  0 },
        { 0, 21 }, { 32, 21 }, { 64, 21 }, { 96, 21 }, { 128, 21 }, { 160, 21 }, { 192, 21 }, { 224, 21 },
        { 0, 43 }, { 32, 43 }, { 64, 43 }, { 96, 43 }, { 128, 43 }, { 160, 43 }, { 192, 43 }, { 224, 43 },
        { 0, 64 }, { 32, 64 }, { 64, 64 }, { 96, 64 }, { 128, 64 }, { 160, 64 }, { 192, 64 }, { 224, 64 }
    }, {
        // LED Index to Flag
        4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4
    }
};

// clang-format on

void keyboard_pre_init_kb(void) {
    // Light power LED
    gpio_set_pin_output(POWER_LED_PIN);
    gpio_write_pin_low(POWER_LED_PIN);

    // We don't use this feature of the IS31FL3731 but it is electrically connected
    // Make sure not to drive it
    gpio_set_pin_input(IS31FL3731_IRQ_PIN);

    keyboard_pre_init_user();
}

void keyboard_post_init_kb(void) {
    // RGB enabled by default, no way to turn off. No need to expend EEPROM write cycles here.
    rgb_matrix_enable_noeeprom();

    keyboard_post_init_user();
}
#endif

#if defined(KC_WRAPPER_KEY)

static uint8_t g_key_wrapper_tracker = 0;

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) { return false; }
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
