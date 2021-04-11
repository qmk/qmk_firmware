/* Copyright 2021 Work Louder
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

#include "loop.h"

#ifdef ENCODER_ENABLE
__attribute__((weak)) void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLD);
        } else {
            tap_code(KC_VOLU);
        }
    } else if (index == 2) {
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    } else {
        if (clockwise) {
            tap_code(KC_UP);
        } else {
            tap_code(KC_DOWN);
        }
    }
}
#endif

#if defined(RGBLIGHT_ENABLE) && defined(RGB_MATRIX_EANBLE)
#    undef RGB_DI_PIN
#    define RGBLIGHT_DI_PIN
#    include "ws2812.c"

void rgblight_call_driver(LED_TYPE *start_led, uint8_t num_leds) {
    ws2812_setleds(start_led, num_leds);
}
#endif

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = {
    {
        {   NO_LED, NO_LED, NO_LED, 8, 7, 6, 5, 4, 3, 2, 1, 0 }
    }, {
        { 36,  32 }, { 55,  32 }, { 74,  32 }, { 93,  32 }, {  112,  32 }, {  131,  32 }, {  150,  32 }, {  169,  32 }, {  188,  32 }
    }, {
        4, 4, 4, 4, 4, 4, 4, 4, 4
    }
};

void suspend_power_down_kb(void) {
    rgb_matrix_set_suspend_state(true);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    rgb_matrix_set_suspend_state(false);
    suspend_wakeup_init_user();
}
#endif
