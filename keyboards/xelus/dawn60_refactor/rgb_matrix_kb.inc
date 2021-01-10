/*
Copyright 2020 Evy Dekkers

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

RGB_MATRIX_EFFECT(rgb_test)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

//colour
// 0 = red, 1 = green, 2 = blue, 3 = white
static bool rgb_test(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    uint8_t factor = 10;
    switch ((g_rgb_timer & (0b11 << factor)) >> factor) {
        case 0: {
            rgb_matrix_set_color_all(20, 0, 0);
            break;
        }
        case 1: {
            rgb_matrix_set_color_all(0, 20, 0);
            break;
        }
        case 2: {
            rgb_matrix_set_color_all(0, 0, 20);
            break;
        }
        case 3: {
            rgb_matrix_set_color_all(20, 20, 20);
            break;
        }
    }
    return led_max < DRIVER_LED_TOTAL;
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
