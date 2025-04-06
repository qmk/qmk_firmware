/* Copyright (C) 2023 jonylee@hfd
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
// clang-format off
#ifdef RGB_MATRIX_ENABLE
const snled27351_led_t PROGMEM g_snled27351_leds[SNLED27351_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
    /*row0*/
    {1, CB1_CA1,   CB2_CA1,   CB3_CA1},
    {1, CB1_CA2,   CB2_CA2,   CB3_CA2},
    {1, CB1_CA3,   CB2_CA3,   CB3_CA3},
    {1, CB1_CA4,   CB2_CA4,   CB3_CA4},
    {1, CB1_CA5,   CB2_CA5,   CB3_CA5},
    {1, CB1_CA6,   CB2_CA6,   CB3_CA6},
    {1, CB1_CA7,   CB2_CA7,   CB3_CA7},
    {1, CB1_CA8,   CB2_CA8,   CB3_CA8},
    {1, CB1_CA9,   CB2_CA9,   CB3_CA9},
    {1, CB1_CA10,  CB2_CA10,  CB3_CA10},
    {1, CB1_CA11,  CB2_CA11,  CB3_CA11},
    {1, CB1_CA12,  CB2_CA12,  CB3_CA12},
    {1, CB1_CA13,  CB2_CA13,  CB3_CA13},
    {1, CB1_CA14,  CB2_CA14,  CB3_CA14},
    {1, CB1_CA15,  CB2_CA15,  CB3_CA15},
    {1, CB1_CA16,  CB2_CA16,  CB3_CA16},

    /*row1*/
    {0, CB1_CA1,   CB2_CA1,   CB3_CA1},
    {0, CB1_CA2,   CB2_CA2,   CB3_CA2},
    {0, CB1_CA3,   CB2_CA3,   CB3_CA3},
    {0, CB1_CA4,   CB2_CA4,   CB3_CA4},
    {0, CB1_CA5,   CB2_CA5,   CB3_CA5},
    {0, CB1_CA6,   CB2_CA6,   CB3_CA6},
    {0, CB1_CA7,   CB2_CA7,   CB3_CA7},
    {0, CB1_CA8,   CB2_CA8,   CB3_CA8},
    {0, CB1_CA9,   CB2_CA9,   CB3_CA9},
    {0, CB1_CA10,  CB2_CA10,  CB3_CA10},
    {0, CB1_CA11,  CB2_CA11,  CB3_CA11},
    {0, CB1_CA12,  CB2_CA12,  CB3_CA12},
    {0, CB1_CA13,  CB2_CA13,  CB3_CA13},
    {0, CB1_CA14,  CB2_CA14,  CB3_CA14},
    {1, CB4_CA1,    CB5_CA1,   CB6_CA1},
    {1, CB4_CA2,    CB5_CA2,   CB6_CA2},
    {1, CB4_CA3,    CB5_CA3,   CB6_CA3},

    /*row2*/
    {0, CB4_CA1,   CB5_CA1,   CB6_CA1},
    {0, CB4_CA2,   CB5_CA2,   CB6_CA2},
    {0, CB4_CA3,   CB5_CA3,   CB6_CA3},
    {0, CB4_CA4,   CB5_CA4,   CB6_CA4},
    {0, CB4_CA5,   CB5_CA5,   CB6_CA5},
    {0, CB4_CA6,   CB5_CA6,   CB6_CA6},
    {0, CB4_CA7,   CB5_CA7,   CB6_CA7},
    {0, CB4_CA8,   CB5_CA8,   CB6_CA8},
    {0, CB4_CA9,   CB5_CA9,   CB6_CA9},
    {0, CB4_CA10,  CB5_CA10,  CB6_CA10},
    {0, CB4_CA11,  CB5_CA11,  CB6_CA11},
    {0, CB4_CA12,  CB5_CA12,  CB6_CA12},
    {0, CB4_CA13,  CB5_CA13,  CB6_CA13},
    {0, CB4_CA14,  CB5_CA14,  CB6_CA14},
    {1, CB7_CA1,   CB8_CA1,   CB9_CA1},
    {1, CB7_CA2,   CB8_CA2,   CB9_CA2},
    {1, CB7_CA3,   CB8_CA3,   CB9_CA3},

    /*row3*/
    {0, CB7_CA1,   CB8_CA1,   CB9_CA1},
    {0, CB7_CA2,   CB8_CA2,   CB9_CA2},
    {0, CB7_CA3,   CB8_CA3,   CB9_CA3},
    {0, CB7_CA4,   CB8_CA4,   CB9_CA4},
    {0, CB7_CA5,   CB8_CA5,   CB9_CA5},
    {0, CB7_CA6,   CB8_CA6,   CB9_CA6},
    {0, CB7_CA7,   CB8_CA7,   CB9_CA7},
    {0, CB7_CA8,   CB8_CA8,   CB9_CA8},
    {0, CB7_CA9,   CB8_CA9,   CB9_CA9},
    {0, CB7_CA10,  CB8_CA10,  CB9_CA10},
    {0, CB7_CA11,  CB8_CA11,  CB9_CA11},
    {0, CB7_CA12,  CB8_CA12,  CB9_CA12},
    {0, CB7_CA13,  CB8_CA13,  CB9_CA13},

    /*row4*/
    {0, CB10_CA1,   CB11_CA1,   CB12_CA1},
    {0, CB10_CA2,   CB11_CA2,   CB12_CA2},
    {0, CB10_CA3,   CB11_CA3,   CB12_CA3},
    {0, CB10_CA4,   CB11_CA4,   CB12_CA4},
    {0, CB10_CA5,   CB11_CA5,   CB12_CA5},
    {0, CB10_CA6,   CB11_CA6,   CB12_CA6},
    {0, CB10_CA7,   CB11_CA7,   CB12_CA7},
    {0, CB10_CA8,   CB11_CA8,   CB12_CA8},
    {0, CB10_CA9,   CB11_CA9,   CB12_CA9},
    {0, CB10_CA10,  CB11_CA10,  CB12_CA10},
    {0, CB10_CA11,  CB11_CA11,  CB12_CA11},
    {0, CB10_CA12,  CB11_CA12,  CB12_CA12},
    {1,  CB10_CA4,   CB11_CA4,  CB12_CA4},

    /*row5*/
    {0, CB10_CA13,  CB11_CA13,  CB12_CA13},
    {0, CB10_CA14,  CB11_CA14,  CB12_CA14},
    {0, CB10_CA15,  CB11_CA15,  CB12_CA15},
    {0, CB10_CA16,  CB11_CA16,  CB12_CA16},
    {0, CB7_CA14,  CB8_CA14,  CB9_CA14},
    {0, CB7_CA15,  CB8_CA15,  CB9_CA15},
    {0, CB7_CA16,  CB8_CA16,  CB9_CA16},
    {0, CB4_CA15,  CB5_CA15,  CB6_CA15},
    {1,  CB10_CA1,   CB11_CA1,  CB12_CA1},
    {1,  CB10_CA2,   CB11_CA2,  CB12_CA2},
    {1,  CB10_CA3,   CB11_CA3,  CB12_CA3},
};
#endif // RGB_MATRIX_ENABLE

// clang-format on
enum __layers {
    WIN_B,
    WIN_W,
    WIN_FN,
    MAC_B,
    MAC_W,
    MAC_FN,
};

void matrix_init_kb(void) {
    gpio_set_pin_output(LED_MAC_OS_PIN); // LDE2 MAC\WIN
    gpio_write_pin_low(LED_MAC_OS_PIN);
    gpio_set_pin_output(LED_WIN_LOCK_PIN); // LED3 Win Lock
    gpio_write_pin_low(LED_WIN_LOCK_PIN);

    matrix_init_user();
}

void housekeeping_task_kb(void){
    gpio_write_pin(LED_MAC_OS_PIN, (get_highest_layer(default_layer_state) == 3));
    gpio_write_pin(LED_WIN_LOCK_PIN, keymap_config.no_gui);
}

bool process_record_kb(uint16_t keycode, keyrecord_t* record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }
    switch (keycode) {
        case DF(WIN_B):
            if (record->event.pressed) {
                set_single_persistent_default_layer(WIN_B);
            }
            return false;
        case DF(MAC_B):
            if (record->event.pressed) {
                set_single_persistent_default_layer(MAC_B);
                keymap_config.no_gui = 0;
                eeconfig_update_keymap(keymap_config.raw);
            }
            return false;
        case GU_TOGG:
            if (record->event.pressed) {
                gpio_write_pin(LED_WIN_LOCK_PIN, !keymap_config.no_gui);
            }
            return true;
        case QK_RGB_MATRIX_TOGGLE:
            if (record->event.pressed) {
                switch (rgb_matrix_get_flags()) {
                    case LED_FLAG_ALL: {
                        rgb_matrix_set_flags(LED_FLAG_NONE);
                        rgb_matrix_set_color_all(0, 0, 0);
                    } break;
                    default: {
                        rgb_matrix_set_flags(LED_FLAG_ALL);
                    } break;
                }
            }
            if (!rgb_matrix_is_enabled()) {
                rgb_matrix_set_flags(LED_FLAG_ALL);
                rgb_matrix_enable();
            }
            return false;
        default:
            return true;
    }
}
