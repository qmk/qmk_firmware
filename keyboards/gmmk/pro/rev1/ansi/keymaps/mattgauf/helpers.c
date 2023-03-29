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

void rgb_matrix_set_color_flags(uint8_t red, uint8_t green, uint8_t blue, uint8_t flags) {
    for (uint8_t ii = 0; ii < RGB_MATRIX_LED_COUNT; ii++) {
        if (g_led_config.flags[ii] & flags) {
            rgb_matrix_set_color(ii, red, green, blue);
        }
    }
}
