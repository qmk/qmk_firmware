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

#ifndef DISABLE_RGB_MATRIX_PIXELATION
RGB_MATRIX_EFFECT(PIXELATION)
#   ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static bool PIXELATION(effect_params_t* params) {
    void set_rgb(int i, effect_params_t* params, bool on) {
        if (!HAS_ANY_FLAGS(g_led_config.flags[i], params->flags)) { return; }
        if (on) {
            HSV hsv = {random8(), add8(random8() >> 1, 127), rgb_matrix_config.hsv.v};
            RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        } else {
            rgb_matrix_set_color(i, RGB_OFF);
        }
    }
    
    if (params->init) { random16_set_seed(0xe089); }

    uint16_t tick = scale16by8(g_rgb_timer, add8(rgb_matrix_config.speed >> 5, 1));
    if (mod8(tick, 5) == 0) { set_rgb(mod8(random8(), DRIVER_LED_TOTAL), params, random8() & 1); }
    return false;
}

#   endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif    // DISABLE_RGB_MATRIX_PIXELATION
