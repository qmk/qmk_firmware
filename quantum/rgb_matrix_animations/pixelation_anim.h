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
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    // Bob Jenkin's fast PRNG, smaller than rand()
    #define rot8(x,k) (((x) << (k))|((x) >> (8 - (k))))
    uint8_t prng(void) {
        static uint_fast8_t a = 0x71, b = 0x1f, c = 0x2f, d = 0x3f;

        uint_fast8_t e = a - rot8(b, 1);
        a = b ^ rot8(c, 4);
        b = c + d;
        c = d + e;
        return d = e + a;
    }

    void set_pixel_rgb(int i, effect_params_t* params, bool on) {
        if (!HAS_ANY_FLAGS(g_led_config.flags[i], params->flags)) { return; }
        (on) ? rgb_matrix_set_color(i, prng(), prng(), prng()) : rgb_matrix_set_color(i, RGB_OFF);
    }

    if (!params->init) {
        if (scale16by8(g_rgb_timer, qadd8(rgb_matrix_config.speed, 16)) % 20 == 0) {
            set_pixel_rgb(prng() % DRIVER_LED_TOTAL, params, 1);
        }
        if (scale16by8(g_rgb_timer, qadd8(rgb_matrix_config.speed, 16)) % 10 == 0) {
            set_pixel_rgb(prng() % DRIVER_LED_TOTAL, params, 0);
        }
        return false;
    }
    return led_max < DRIVER_LED_TOTAL;
}

#   endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif    // DISABLE_RGB_MATRIX_PIXELATION
