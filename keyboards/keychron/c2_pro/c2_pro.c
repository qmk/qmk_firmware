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
#        define LED_MATRIX_INDICATORS_KB rgb_matrix_indicators_kb
#        define LED_MATRIX_INDICATORS_USER rgb_matrix_indicators_user
#        define LED_MATRIX_SET_COLOR rgb_matrix_set_color
#        define COLOR_WHITE 255, 255, 255
#        define COLOR_BLACK 0, 0, 0
#    endif

#    ifdef LED_MATRIX_ENABLE
#        define LED_MATRIX_INDICATORS_KB led_matrix_indicators_kb
#        define LED_MATRIX_INDICATORS_USER led_matrix_indicators_user
#        define LED_MATRIX_SET_COLOR led_matrix_set_value
#        define COLOR_WHITE 255
#        define COLOR_BLACK 0

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
