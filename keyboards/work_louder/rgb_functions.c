/* Copyright 2021 Drashna Jael're
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

#include "rgb_functions.h"

#ifdef RGBLIGHT_ENABLE
#undef WS2812_DI_PIN
#define WS2812_DI_PIN RGBLIGHT_DI_PIN

#define ws2812_setleds ws2812_rgb_setleds

#include "ws2812_bitbang.c"

void rgblight_call_driver(LED_TYPE *start_led, uint8_t num_leds) {
    ws2812_setleds(start_led, num_leds);
}
#endif

#ifdef RGB_MATRIX_ENABLE
bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) { return false; }

    if (record->event.pressed) {
        switch(keycode) {
        case RGB_MATRIX_TOGGLE: // toggle rgb matrix
            rgb_matrix_toggle();
            return false;
        case RGB_MATRIX_MODE_INC:
            rgb_matrix_step();
            return false;
        case RGB_MATRIX_MODE_DEC:
            rgb_matrix_step_reverse();
            return false;
        case RGB_MATRIX_HUE_INC:
            rgb_matrix_increase_hue();
            return false;
        case RGB_MATRIX_HUE_DEC:
            rgb_matrix_decrease_hue();
            return false;
        case RGB_MATRIX_SAT_INC:
            rgb_matrix_increase_sat();
            return false;
        case RGB_MATRIX_SAT_DEC:
            rgb_matrix_decrease_sat();
            return false;
        case RGB_MATRIX_VAL_INC:
            rgb_matrix_increase_val();
            return false;
        case RGB_MATRIX_VAL_DEC:
            rgb_matrix_decrease_val();
            return false;
        default:
            break;
        }
    }
    return true;
}
#endif
