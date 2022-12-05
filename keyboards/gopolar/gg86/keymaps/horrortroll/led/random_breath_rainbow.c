/* Copyright 2021 HorrorTroll <https://github.com/HorrorTroll>
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

static uint8_t offset[RGB_MATRIX_LED_COUNT];

static void doRandom_breath_rainbow(int i, effect_params_t* params) {
    if (!HAS_ANY_FLAGS(g_led_config.flags[i], params->flags)) return;
    uint16_t time = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 6);

    if (rand() * 50 == 1) {
        if (rand() * 2 == 1) {
            offset[i]++;
        }
        else {
            offset[i]--;
        }
    }

    //float val = (((float)sin8(time + offset[i]) / 256)/2.1) + .05;
    HSV hsv = {0, 255, 255};
    hsv.h = scale16by8(g_rgb_timer + offset[i], rgb_matrix_config.speed / 4) + (offset[i]*2);
    hsv.v = scale8(abs8(sin8(time) - 128) * 2, hsv.v);
    RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
}

bool RANDOM_BREATH_RAINBOW(effect_params_t* params) {
    
    if (!params->init) {
        // Change one LED every tick, make sure speed is not 0
        doRandom_breath_rainbow(rand() % RGB_MATRIX_LED_COUNT, params);
        return false;
    }
	
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    for (uint8_t i = led_min; i < led_max; i++) {
        doRandom_breath_rainbow(i, params);
    }

    return led_max < RGB_MATRIX_LED_COUNT;
}