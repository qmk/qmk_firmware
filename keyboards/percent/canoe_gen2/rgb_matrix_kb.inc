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

RGB_MATRIX_EFFECT(indicator_gradient)
RGB_MATRIX_EFFECT(indicator_cycle_all)
RGB_MATRIX_EFFECT(indicator_static)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static bool indicator_static(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    for (uint8_t i = led_min ; i < 74; i++) {
        rgb_matrix_set_color(i, 0x00, 0x00, 0x00);
    }
    for (uint8_t i = 74 ; i < led_max; i++) {
        rgb_matrix_set_color(i, 0xff, 0xff, 0xff);
    }
    return led_max < DRIVER_LED_TOTAL;
}

bool effect_runner_indicator(effect_params_t* params, i_f effect_func) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    uint8_t time = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 16);
    for (uint8_t i = led_min; i < led_max; i++) {
        if (i < 74) {
            rgb_matrix_set_color(i, 0x00, 0x00, 0x00);
        } else {
            RGB_MATRIX_TEST_LED_FLAGS();
            RGB rgb = hsv_to_rgb(effect_func(rgb_matrix_config.hsv, (i - 74), time));
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }
    return led_max < DRIVER_LED_TOTAL;
}

static HSV indicator_gradient_math(HSV hsv, uint8_t i, uint8_t time) {
    hsv.h = g_led_config.point[i].x - time;
    return hsv;
}

bool indicator_gradient(effect_params_t* params) { return effect_runner_indicator(params, &indicator_gradient_math); }

static HSV indicator_cycle_all_math(HSV hsv, uint8_t i, uint8_t time) {
    hsv.h = time;
    return hsv;
}

bool indicator_cycle_all(effect_params_t* params) { return effect_runner_indicator(params, &indicator_cycle_all_math); }

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
