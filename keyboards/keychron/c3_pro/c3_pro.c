/* Copyright 2024 @ Keychron (https://www.keychron.com)
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

#include "c3_pro.h"

void keyboard_post_init_kb(void) {
    gpio_set_pin_output_push_pull(LED_MAC_OS_PIN);
    gpio_set_pin_output_push_pull(LED_WIN_OS_PIN);
    gpio_write_pin(LED_MAC_OS_PIN, !LED_OS_PIN_ON_STATE);
    gpio_write_pin(LED_WIN_OS_PIN, !LED_OS_PIN_ON_STATE);
    
    keyboard_post_init_user();
}

void housekeeping_task_kb(void) {
    if (get_highest_layer(default_layer_state) == 0) {
        gpio_write_pin(LED_MAC_OS_PIN, LED_OS_PIN_ON_STATE);
        gpio_write_pin(LED_WIN_OS_PIN, !LED_OS_PIN_ON_STATE);
    }
    if (get_highest_layer(default_layer_state) == 2) {
        gpio_write_pin(LED_MAC_OS_PIN, !LED_OS_PIN_ON_STATE);
        gpio_write_pin(LED_WIN_OS_PIN, LED_OS_PIN_ON_STATE);
    }
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }
    switch (keycode) {
#ifdef RGB_MATRIX_ENABLE
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
#endif
#ifdef LED_MATRIX_ENABLE
        case QK_LED_MATRIX_TOGGLE:
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
#endif
        case KC_OSSW:
            if (record->event.pressed) {
                // Switches default layer between `MAC_BASE` and `WIN_BASE` (0 and 2)
                if (get_highest_layer(default_layer_state) == 2 ) {
                    set_single_persistent_default_layer(0);
                } else {
                    set_single_persistent_default_layer(2);
                }
            }
            return false;
        default:
            return true;
    }
}

void suspend_power_down_kb(void) {
    gpio_write_pin(LED_WIN_OS_PIN, !LED_OS_PIN_ON_STATE);
    gpio_write_pin(LED_MAC_OS_PIN, !LED_OS_PIN_ON_STATE);
    suspend_power_down_user();
}
