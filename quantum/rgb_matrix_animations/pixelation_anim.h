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
    uint8_t prng8(void) {
        #define rot8(x,k) (((x) << (k))|((x) >> (8 - (k))))
        static uint8_t a = 73, b = 29;
        uint8_t t = sub8(a, rot8(b, 1));
        a = b ^ rot8(t, 4);
        return b = add8(t, a);
    }

    void set_rgb(int i, effect_params_t* params, bool on) {
        if (!HAS_ANY_FLAGS(g_led_config.flags[i], params->flags)) { return; }
        on ? rgb_matrix_set_color(i, prng8(), prng8(), prng8()) : rgb_matrix_set_color(i, RGB_OFF);
    }

    uint16_t tick = scale16by8(g_rgb_timer, qadd8((rgb_matrix_config.speed >> 5), 1));
    if (mod8(tick, 10) == 0) { set_rgb(mod8(prng8(), DRIVER_LED_TOTAL), params, 1); }
    if (mod8(tick,  5) == 0) { set_rgb(mod8(prng8(), DRIVER_LED_TOTAL), params, 0); }
    return false;
}

#   endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif    // DISABLE_RGB_MATRIX_PIXELATION
