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

#ifndef DISABLE_RGB_MATRIX_PIXEL_FLOW
RGB_MATRIX_EFFECT(PIXEL_FLOW)
#   ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static bool PIXEL_FLOW(effect_params_t* params) {
    static RGB led[DRIVER_LED_TOTAL];
    static uint32_t wait_timer = 0;
    uint16_t interval = 1500 / scale16by8(qadd8(rgb_matrix_config.speed, 16), 16);
    if (g_rgb_timer < wait_timer) { return false; }

    void set_rgb(uint8_t i) {
        led[i] = (random8() & 3) ? (RGB){0,0,0} : rgb_matrix_hsv_to_rgb((HSV){random8(), qadd8(random8() >> 1, 127), rgb_matrix_config.hsv.v});
    }
    if (params->init) {
        random16_set_seed((uint16_t)g_rgb_timer);
        for (uint8_t k = 0; k < DRIVER_LED_TOTAL; ++k) { set_rgb(k); }
    }
	RGB_MATRIX_USE_LIMITS(led_min, led_max);
    if (led_max == DRIVER_LED_TOTAL) {
        for (uint8_t j = 0; j < DRIVER_LED_TOTAL-1; ++j) { led[j] = led[j+1]; }
        set_rgb(DRIVER_LED_TOTAL-1);
        wait_timer = g_rgb_timer + interval;
    }
    for (uint8_t i = led_min; i < led_max; ++i) {
        RGB_MATRIX_TEST_LED_FLAGS();
        rgb_matrix_set_color(i, led[i].r, led[i].g, led[i].b);
    }
    return led_max < DRIVER_LED_TOTAL;
}

#   endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif    // DISABLE_RGB_MATRIX_PIXEL_FLOW
