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

#ifndef DISABLE_RGB_MATRIX_PIXEL_RAIN
RGB_MATRIX_EFFECT(PIXEL_RAIN)
#   ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static bool PIXEL_RAIN(effect_params_t* params) {
    static uint32_t timer = 0;
    uint16_t speed = 500 / scale16by8(qadd8(rgb_matrix_config.speed, 16), 16);
    if (timer > g_rgb_timer) { return false; }

    bool set_rgb(uint8_t i, effect_params_t* params, bool off) {
        if (!HAS_ANY_FLAGS(g_led_config.flags[i], params->flags)) { return false; }
        if (off) {
            rgb_matrix_set_color(i, RGB_OFF);
        } else {
            HSV hsv = {random8(), qadd8(random8() >> 1, 127), rgb_matrix_config.hsv.v};
            RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
        timer = g_rgb_timer + speed;
        return false;
    }

    if (params->init) { random16_set_seed((uint16_t)g_rgb_timer); }
    return set_rgb(mod8(random8(), DRIVER_LED_TOTAL), params, random8() & 3);
}

#   endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif    // DISABLE_RGB_MATRIX_PIXEL_RAIN
