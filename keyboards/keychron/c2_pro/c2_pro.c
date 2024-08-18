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

#ifdef DIP_SWITCH_ENABLE

bool dip_switch_update_kb(uint8_t index, bool active) {
    if (!dip_switch_update_user(index, active)) {
        return false;
    }
    if (index == 0) {
        default_layer_set(1UL << (active ? 2 : 0));
    }
    return true;
}

#endif // DIP_SWITCH_ENABLE

#    ifdef RGB_MATRIX_ENABLE
#        define LED_SET_FLAGS rgb_matrix_set_flags
#        define LED_GET_FLAGS rgb_matrix_get_flags
#        define LED_SET_ALL_OFF rgb_matrix_set_color_all(COLOR_BLACK)
#        define LED_IS_ENABLED rgb_matrix_is_enabled
#        define LED_ENABLE rgb_matrix_enable
#        define LED_MATRIX_INDICATORS_KB rgb_matrix_indicators_kb
#        define LED_MATRIX_INDICATORS_USER rgb_matrix_indicators_user
#        define LED_MATRIX_SET_COLOR rgb_matrix_set_color
#        define LED_MATRIX_UPDATE_PWN_BUFFERS rgb_matrix_update_pwm_buffers
#        define LED_MATRIX_INDICATORS_NONE_KB rgb_matrix_indicators_none_kb
#        define LED_MATRIX_IS_ENABLED rgb_matrix_is_enabled
#        define COLOR_WHITE 255, 255, 255
#        define COLOR_BLACK 0, 0, 0
#    endif

#    ifdef LED_MATRIX_ENABLE
#        define LED_SET_FLAGS led_matrix_set_flags
#        define LED_GET_FLAGS led_matrix_get_flags
#        define LED_SET_ALL_OFF led_matrix_set_value_all(COLOR_BLACK)
#        define LED_IS_ENABLED led_matrix_is_enabled
#        define LED_ENABLE led_matrix_enable
#        define LED_MATRIX_INDICATORS_KB led_matrix_indicators_kb
#        define LED_MATRIX_INDICATORS_USER led_matrix_indicators_user
#        define LED_MATRIX_SET_COLOR led_matrix_set_value
#        define LED_MATRIX_UPDATE_PWN_BUFFERS led_matrix_update_pwm_buffers
#        define LED_MATRIX_INDICATORS_NONE_KB led_matrix_indicators_none_kb
#        define LED_MATRIX_IS_ENABLED led_matrix_is_enabled
#        define COLOR_WHITE 255
#        define COLOR_BLACK 0

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }
    switch (keycode) {
        case RGB_TOG:
            if (record->event.pressed) {
                switch (LED_GET_FLAGS()) {
                    case LED_FLAG_ALL: {
                        LED_SET_FLAGS(LED_FLAG_NONE);
                        LED_SET_ALL_OFF;
                    } break;
                    default: {
                        LED_SET_FLAGS(LED_FLAG_ALL);
                    } break;
                }
            }
            if (!LED_IS_ENABLED()) {
                LED_SET_FLAGS(LED_FLAG_ALL);
                LED_ENABLE();
            }
            return false;
    }
    return true;
}

bool LED_MATRIX_INDICATORS_KB(void) {
    if (!LED_MATRIX_INDICATORS_USER()) {
        return false;
    }
    if (host_keyboard_led_state().caps_lock) {
        LED_MATRIX_SET_COLOR(CAPS_LED_INDEX, COLOR_WHITE);
    } else {
        LED_MATRIX_SET_COLOR(CAPS_LED_INDEX, COLOR_BLACK);
    }
    if (host_keyboard_led_state().num_lock) {
        LED_MATRIX_SET_COLOR(NUM_LED_INDEX, COLOR_WHITE);
    } else {
        LED_MATRIX_SET_COLOR(NUM_LED_INDEX, COLOR_BLACK);
    }
    if (default_layer_state == (1 << 0)) {
        LED_MATRIX_SET_COLOR(MAC_LED_INDEX, COLOR_WHITE);
    } else {
        LED_MATRIX_SET_COLOR(MAC_LED_INDEX, COLOR_BLACK);
    }
    if (default_layer_state == (1 << 2)) {
        LED_MATRIX_SET_COLOR(WIN_LED_INDEX, COLOR_WHITE);
    } else {
        LED_MATRIX_SET_COLOR(WIN_LED_INDEX, COLOR_BLACK);
    }
    return true;
}

#endif
