/* Copyright 2023 HorrorTroll <https://github.com/HorrorTroll>
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

#ifdef ENABLE_RGB_MATRIX_FLOWER_BLOOMING
RGB_MATRIX_EFFECT(FLOWER_BLOOMING)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

typedef HSV (*flower_blooming_f)(HSV hsv, uint8_t i, uint8_t time);

bool effect_runner_bloom(effect_params_t* params, flower_blooming_f effect_func) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    uint8_t time = scale16by8(g_rgb_timer, qadd8(rgb_matrix_config.speed / 10, 1));
    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        if (g_led_config.point[i].y > k_rgb_matrix_center.y) {
            RGB bgr = rgb_matrix_hsv_to_rgb(effect_func(rgb_matrix_config.hsv, i, time));
            rgb_matrix_set_color(i, bgr.b, bgr.g, bgr.r);
        } else {
            RGB rgb = rgb_matrix_hsv_to_rgb(effect_func(rgb_matrix_config.hsv, i, time));
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }
    return rgb_matrix_check_finished_leds(led_max);
}

static HSV FLOWER_BLOOMING_math(HSV hsv, uint8_t i, uint8_t time) {
    if (g_led_config.point[i].y > k_rgb_matrix_center.y)
        hsv.h = g_led_config.point[i].x * 3 - g_led_config.point[i].y * 3 + time;
    else
        hsv.h = g_led_config.point[i].x * 3 - g_led_config.point[i].y * 3 - time;
    return hsv;
}

bool FLOWER_BLOOMING(effect_params_t* params) {
    return effect_runner_bloom(params, &FLOWER_BLOOMING_math);
}

#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // ENABLE_RGB_MATRIX_FLOWER_BLOOMING
