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

// Inspired from 4x12 fractal created by @schwarzgrau

#ifndef DISABLE_RGB_MATRIX_PIXEL_FRACTAL
RGB_MATRIX_EFFECT(PIXEL_FRACTAL)
#   ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static bool PIXEL_FRACTAL(effect_params_t* params) {
    #define FRACTAL_WIDTH 15
    #define FRACTAL_HEIGHT 5
    #define FRACTAL_MIDDLE 7
    #define FRACTAL_RATIO 16  // Ratio assumes 224 x 64 matrix

    typedef struct PACKED { RGB rgb; bool tag; } fractal_led_t;
    static fractal_led_t led[FRACTAL_WIDTH][FRACTAL_HEIGHT];
    static uint32_t wait_timer = 0;
    if (wait_timer > g_rgb_timer) { return false; }

    inline uint32_t interval(void) { return 3000 / scale16by8(qadd8(rgb_matrix_config.speed, 16), 16); }

    #define FRACTAL_PIXEL() (random8() & 3) ? (RGB){0,0,0} : rgb_matrix_hsv_to_rgb((HSV){random8(), qadd8(random8() >> 1, 127), rgb_matrix_config.hsv.v})
    #define GET_FRACTAL_POINT(k) (point_t){scale8(g_led_config.point[k].x, FRACTAL_RATIO), scale8(g_led_config.point[k].y, FRACTAL_RATIO)}

    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    if (params->init) { random16_set_seed((uint16_t)g_rgb_timer); }
    // Main LED lighting loop
    for (uint8_t i = led_min; i < led_max; ++i) {
        RGB_MATRIX_TEST_LED_FLAGS();
        point_t map = GET_FRACTAL_POINT(i);
        led[map.x][map.y].tag = true; // Tag used arrays after scaling by FRACTAL_RATIO
        rgb_matrix_set_color(i, led[map.x][map.y].rgb.r, led[map.x][map.y].rgb.g, led[map.x][map.y].rgb.b);
    }
    // Shifts columns outwards
    if (led_max == DRIVER_LED_TOTAL) {
        for (uint8_t h = 0; h < FRACTAL_HEIGHT; ++h) {
            for (uint8_t l = 0; l < FRACTAL_MIDDLE; ++l) {               // Move left columns
                led[l][h].rgb = (led[l+1][h].tag) ? led[l+1][h].rgb : led[l+2][h].rgb;
            }
            for (uint8_t r = FRACTAL_WIDTH-1; r > FRACTAL_MIDDLE; --r) { // Move right columns
                led[r][h].rgb = (led[r-1][h].tag) ? led[r-1][h].rgb : led[r-2][h].rgb;
            }
            led[FRACTAL_MIDDLE][h].tag = true;             // Tag middle column
            led[FRACTAL_MIDDLE][h].rgb = FRACTAL_PIXEL();  // Randomize middle column
        }
        wait_timer = g_rgb_timer + interval();
    }
    return led_max < DRIVER_LED_TOTAL;
}

#   endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif    // DISABLE_RGB_MATRIX_PIXEL_FRACTAL
