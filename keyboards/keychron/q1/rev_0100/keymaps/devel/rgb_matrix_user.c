/* Copyright 2021 @ Grayson Carr
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

#include QMK_KEYBOARD_H
#include "rgb_matrix_user.h"

// clang-format off

const uint8_t led_index_alphas[] = {
    LED_Q, LED_W, LED_E, LED_R, LED_T, LED_Y, LED_U, LED_I, LED_O, LED_P,
    LED_A, LED_S, LED_D, LED_F, LED_G, LED_H, LED_J, LED_K, LED_L,
    LED_Z, LED_X, LED_C, LED_V, LED_B, LED_N, LED_M
};

const uint8_t led_index_macos_fn[] = {
	  LEC_ESC, LED_INS,
    LED_Q, LED_W, LED_E, LED_R, LED_T,
    LED_A, LED_S, LED_D, LED_F, LED_G, LED_HOME
};

// clang-format on

void rgb_matrix_indicators_user(void) {
#ifdef CAPS_LOCK_INDICATOR_COLOR
    if (host_keyboard_led_state().caps_lock && (layer_state_is(0) || layer_state_is(2))) {
        rgb_matrix_set_color(LED_CAPS, CAPS_LOCK_INDICATOR_COLOR);
#    ifdef CAPS_LOCK_INDICATOR_LIGHT_TAB
        rgb_matrix_set_color(LED_TAB, CAPS_LOCK_INDICATOR_COLOR);
#    endif
#    ifdef CAPS_LOCK_INDICATOR_LIGHT_ALPHAS
        rgb_matrix_set_color_alphas(CAPS_LOCK_INDICATOR_COLOR);
#    endif
    }
#endif  // CAPS_LOCK_INDICATOR_COLOR
#ifdef MACOS_FN_INDICATOR_COLOR
    if (layer_state_is(1) {
    	  rgb_matrix_set_color_macos_fn(MACOS_FN_INDICATOR_COLOR);
    }
#endif  // MACOS_FN_INDICATOR_COLOR
}

void rgb_matrix_set_color_macos_fn(uint8_t red, uint8_t green, uint8_t blue) {
    uint8_t led_count = sizeof(led_index_macos_fn) / sizeof(led_index_macos_fn[0]);
    rgb_matrix_set_color_leds(led_index_macos_fn, led_count, red, green, blue);
}

void rgb_matrix_set_color_alphas(uint8_t red, uint8_t green, uint8_t blue) {
    uint8_t led_count = sizeof(led_index_alphas) / sizeof(led_index_alphas[0]);
    rgb_matrix_set_color_leds(led_index_alphas, led_count, red, green, blue);
}

void rgb_matrix_set_color_leds(const uint8_t led_index[], uint8_t led_count, uint8_t red, uint8_t green, uint8_t blue) {
    for (uint8_t i = 0; i < led_count; i++) {
        rgb_matrix_set_color(led_index[i], red, green, blue);
    }
}
