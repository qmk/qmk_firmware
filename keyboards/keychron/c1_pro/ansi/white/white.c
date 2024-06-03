/* Copyright 2023 @ Keychron (https://www.keychron.com)
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
#ifdef LED_MATRIX_ENABLE
const snled27351_led_t PROGMEM g_snled27351_leds[SNLED27351_LED_COUNT] = {
/* Refer to SNLED27351 manual for these locations
 *   driver
 *   |  LED address
 *   |  |   */
    {0, CB1_CA16}, // esc
    {0, CB1_CA15}, // f1
    {0, CB1_CA14}, // f2
    {0, CB1_CA13}, // f3
    {0, CB1_CA12}, // f4
    {0, CB1_CA11}, // f5
    {0, CB1_CA10}, // f6
    {0, CB1_CA9},  // f7
    {0, CB1_CA8},  // f8
    {0, CB1_CA7},  // f9
    {0, CB1_CA6},  // f10
    {0, CB1_CA5},  // f11
    {0, CB1_CA4},  // f12
    {0, CB1_CA2},  // print
    {0, CB1_CA1},  // siri
    {0, CB7_CA1},  // light

    {0, CB2_CA16}, // ~
    {0, CB2_CA15}, // 1!
    {0, CB2_CA14}, // 2@
    {0, CB2_CA13}, // 3#
    {0, CB2_CA12}, // 4$
    {0, CB2_CA11}, // 5%
    {0, CB2_CA10}, // 6^
    {0, CB2_CA9},  // 7&
    {0, CB2_CA8},  // 8*
    {0, CB2_CA7},  // 9(
    {0, CB2_CA6},  // 0)
    {0, CB2_CA5},  // -_
    {0, CB2_CA4},  // =+
    {0, CB2_CA3},  // back space
    {0, CB2_CA2},  // INS
    {0, CB2_CA1},  // HOME
    {0, CB8_CA1},  // PGUP

    {0, CB3_CA16}, // tab
    {0, CB3_CA15}, // q
    {0, CB3_CA14}, // w
    {0, CB3_CA13}, // e
    {0, CB3_CA12}, // r
    {0, CB3_CA11}, // t
    {0, CB3_CA10}, // y
    {0, CB3_CA9},  // u
    {0, CB3_CA8},  // i
    {0, CB3_CA7},  // o
    {0, CB3_CA6},  // p
    {0, CB3_CA5},  // [{
    {0, CB3_CA4},  // ]}
    {0, CB3_CA3},  // \|
    {0, CB3_CA2},  // DEL
    {0, CB3_CA1},  // END
    {0, CB7_CA6},  // PGDN

    {0, CB4_CA16}, // caps lock
    {0, CB4_CA15}, // a
    {0, CB4_CA14}, // s
    {0, CB4_CA13}, // d
    {0, CB4_CA12}, // f
    {0, CB4_CA11}, // g
    {0, CB4_CA10}, // h
    {0, CB4_CA9},  // j
    {0, CB4_CA8},  // k
    {0, CB4_CA7},  // l
    {0, CB4_CA6},  // ;:
    {0, CB4_CA5},  // '"
    {0, CB4_CA3},  // enter

    {0, CB8_CA7},  // CPAS
    {0, CB8_CA8},  // MAC
    {0, CB8_CA9},  // WIN

    {0, CB5_CA16}, // left shift
    {0, CB5_CA14}, // z
    {0, CB5_CA13}, // x
    {0, CB5_CA12}, // c
    {0, CB5_CA11}, // v
    {0, CB5_CA10}, // b
    {0, CB5_CA9},  // b
    {0, CB5_CA8},  // n
    {0, CB5_CA7},  // m
    {0, CB5_CA6},  // ,<
    {0, CB5_CA5},  // .>
    {0, CB5_CA3},  // right shift
    {0, CB5_CA1},  // up

    {0, CB6_CA16}, // left ctrl
    {0, CB6_CA15}, // left command
    {0, CB6_CA14}, // left option
    {0, CB6_CA10}, // space
    {0, CB6_CA6},  // right command
    {0, CB6_CA5},  // right option
    {0, CB6_CA4},  // right ctrl
    {0, CB6_CA3},  // Fn
    {0, CB6_CA2},  // left
    {0, CB6_CA1},  // down
    {0, CB7_CA13}, // right
};

// clang-format on

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }
    switch (keycode) {
        case LM_TOGG:
            if (record->event.pressed) {
                switch (led_matrix_get_flags()) {
                    case LED_FLAG_ALL: {
                        led_matrix_set_flags(LED_FLAG_NONE);
                        led_matrix_set_value_all(0);
                    } break;
                    default: {
                        led_matrix_set_flags(LED_FLAG_ALL);
                    } break;
                }
            }
            if (!led_matrix_is_enabled()) {
                led_matrix_set_flags(LED_FLAG_ALL);
                led_matrix_enable();
            }
            return false;
    }
    return true;
}

bool led_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (!led_matrix_indicators_advanced_user(led_min, led_max)) {
        return false;
    }
    if ((host_keyboard_led_state().caps_lock) && (default_layer_state == (1 << 0))) {
        led_matrix_set_value(CAPS_LOCK_LED_INDEX, 255);
        led_matrix_set_value(MAC_LOCK_LED_INDEX, 255);
        led_matrix_set_value(WIN_LOCK_LED_INDEX, 0);
    } else if ((!host_keyboard_led_state().caps_lock) && (default_layer_state == (1 << 0))) {
        led_matrix_set_value(CAPS_LOCK_LED_INDEX, 0);
        led_matrix_set_value(MAC_LOCK_LED_INDEX, 255);
        led_matrix_set_value(WIN_LOCK_LED_INDEX, 0);
    } else if ((host_keyboard_led_state().caps_lock) && (default_layer_state == (1 << 2))) {
        led_matrix_set_value(CAPS_LOCK_LED_INDEX, 255);
        led_matrix_set_value(MAC_LOCK_LED_INDEX, 0);
        led_matrix_set_value(WIN_LOCK_LED_INDEX, 255);
    } else if ((!host_keyboard_led_state().caps_lock) && (default_layer_state == (1 << 2))) {
        led_matrix_set_value(CAPS_LOCK_LED_INDEX, 0);
        led_matrix_set_value(MAC_LOCK_LED_INDEX, 0);
        led_matrix_set_value(WIN_LOCK_LED_INDEX, 255);
    }
    return true;
}

#endif
