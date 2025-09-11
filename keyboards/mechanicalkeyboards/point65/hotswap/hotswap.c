/* Copyright 2024 Sebastiaan Swinkels @ BeanBoards <sebastiaan.swinkels@googlemail.com>
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

 enum point65_layers {
    _QWERTY,
    _FUNCTION
};

bool rgb_matrix_indicators_kb(void) {
    HSV hsv = {0, 255, 255};

    // Light up ESC RGB LED when _FUNCTION layer is accessed
    if ((get_highest_layer(layer_state|default_layer_state)) == _FUNCTION){
        hsv.h = 43;
        hsv.s = 105;
        hsv.v = 255;

        if (hsv.v > rgb_matrix_get_val() + RGB_INDICATOR_POS_OFFSET) {
            hsv.v = rgb_matrix_get_val() + RGB_INDICATOR_POS_OFFSET;
        }
        RGB rgb = hsv_to_rgb(hsv);

        rgb_matrix_set_color(0, rgb.r, rgb.g, rgb.b);
    }
    // end layer function

    // capslock indicator
    if (host_keyboard_led_state().caps_lock) {
        hsv.h = 43;
        hsv.s = 105;
        hsv.v = 255;

        if (hsv.v > rgb_matrix_get_val() + RGB_INDICATOR_POS_OFFSET) {
                hsv.v = rgb_matrix_get_val() + RGB_INDICATOR_POS_OFFSET;
        }
        RGB rgb = hsv_to_rgb(hsv);

        rgb_matrix_set_color(1, rgb.r, rgb.g, rgb.b);
    }
    // end capslock function

    return false;
}