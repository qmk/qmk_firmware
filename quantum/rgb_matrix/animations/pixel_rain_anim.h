/* Copyright (C) 2021 @filterpaper
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

#ifdef ENABLE_RGB_MATRIX_PIXEL_RAIN
RGB_MATRIX_EFFECT(PIXEL_RAIN)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static bool PIXEL_RAIN(effect_params_t* params) {
    static uint32_t wait_timer = 0;

    inline uint32_t interval(void) {
        return 500 / scale16by8(qadd8(rgb_matrix_config.speed, 16), 16);
    }

    void rain_pixel(uint8_t i, effect_params_t * params, bool off) {
        if (!HAS_ANY_FLAGS(g_led_config.flags[i], params->flags)) {
            return;
        }
        if (off) {
            rgb_matrix_set_color(i, 0, 0, 0);
        } else {
            HSV hsv = {random8(), qadd8(random8() >> 1, 127), rgb_matrix_config.hsv.v};
            RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
        wait_timer = g_rgb_timer + interval();
    }

    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    if (g_rgb_timer > wait_timer) {
        rain_pixel(mod8(random8(), DRIVER_LED_TOTAL), params, random8() & 2);
    }
    return rgb_matrix_check_finished_leds(led_max);
}

#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // ENABLE_RGB_MATRIX_PIXEL_RAIN
