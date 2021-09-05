/* Copyright 2021 Matt Gauf
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

#include "rgb_matrix.h"

void rgb_matrix_set_color_underglow(uint8_t red, uint8_t green, uint8_t blue) {
    for (uint8_t ii = 0; ii < DRIVER_LED_TOTAL; ii++) {
        if (g_led_config.flags[ii] & LED_FLAG_UNDERGLOW) {
            rgb_matrix_set_color(ii, red, green, blue);
        }
    }
}

void rgb_matrix_set_color_keylight(uint8_t red, uint8_t green, uint8_t blue) {
    for (uint8_t ii = 0; ii < DRIVER_LED_TOTAL; ii++) {
        if (g_led_config.flags[ii] & (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER)) {
            rgb_matrix_set_color(ii, red, green, blue);
        }
    }
}

void rgb_matrix_set_color_modifier(uint8_t red, uint8_t green, uint8_t blue) {
    for (uint8_t ii = 0; ii < DRIVER_LED_TOTAL; ii++) {
        if (g_led_config.flags[ii] & LED_FLAG_MODIFIER) {
            rgb_matrix_set_color(ii, red, green, blue);
        }
    }
}
