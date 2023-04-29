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

#include "horrortroll.h"

#include "rgb_matrix.h"

// For CUSTOM_GRADIENT
HSV gradient_0          = {205, 250, 255};
HSV gradient_100        = {140, 215, 125};
bool reflected_gradient = false;
uint8_t gp_i            = 0;

typedef struct {
    HSV gradient_0;
    HSV gradient_1;
    bool reflected;
} CUSTOM_PRESETS;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint8_t color_adj_step = 5;

    CUSTOM_PRESETS gradient_presets[] = {
    {{41 , 255, 255}, {233, 245, 255}, false },
    {{45 , 245, 155}, {160, 255,  80}, false },
    {{173, 245,  40}, {41 , 255, 205}, true  },
    {{32 , 255, 165}, {217, 185,  70}, false },
    {{240, 255, 145}, {115, 255, 245}, true  },
    {{118, 255, 255}, {242, 255, 255}, false },
    {{212,  0 ,   0}, {223, 235, 165}, true  },
    {{205, 250, 255}, {140, 215, 125}, false },
    };

    uint8_t gp_length = sizeof(gradient_presets)/sizeof(gradient_presets[0]);

    switch (keycode) {
        case G1_HUI:
            if (record->event.pressed) {
                gradient_0.h += color_adj_step;
                dprintf("Gradient 0 HSV: %d, %d, %d\n", gradient_0.h, gradient_0.s, gradient_0.v);
            }
            return false;
        case G1_HUD:
            if (record->event.pressed) {
                gradient_0.h -= color_adj_step;
                dprintf("Gradient 0 HSV: %d, %d, %d\n", gradient_0.h, gradient_0.s, gradient_0.v);
            }
            return false;
        case G1_SAI:
            if (record->event.pressed) {
                gradient_0.s = (gradient_0.s + color_adj_step * 2 <= 255) ? gradient_0.s + color_adj_step * 2 : 255;
                dprintf("Gradient 0 HSV: %d, %d, %d\n", gradient_0.h, gradient_0.s, gradient_0.v);
            }
            return false;
        case G1_SAD:
            if (record->event.pressed) {
                gradient_0.s = (gradient_0.s - color_adj_step * 2 >= 0) ? gradient_0.s - color_adj_step * 2 : 0;
                dprintf("Gradient 0 HSV: %d, %d, %d\n", gradient_0.h, gradient_0.s, gradient_0.v);
            }
            return false;
        case G1_VAI:
            if (record->event.pressed) {
                gradient_0.v = (gradient_0.v + color_adj_step * 2 <= 255) ? gradient_0.v + color_adj_step * 2 : 255;
                dprintf("Gradient 0 HSV: %d, %d, %d\n", gradient_0.h, gradient_0.s, gradient_0.v);
            }
            return false;
        case G1_VAD:
            if (record->event.pressed) {
                gradient_0.v = (gradient_0.v - color_adj_step * 2 >= 0) ? gradient_0.v - color_adj_step * 2 : 0;
                dprintf("Gradient 0 HSV: %d, %d, %d\n", gradient_0.h, gradient_0.s, gradient_0.v);
            }
            return false;
        case G2_HUI:
            if (record->event.pressed) {
                gradient_100.h += color_adj_step;
                dprintf("Gradient 100 HSV: %d, %d, %d\n", gradient_100.h, gradient_100.s, gradient_100.v);
            }
            return false;
        case G2_HUD:
            if (record->event.pressed) {
                gradient_100.h -= color_adj_step;
                dprintf("Gradient 100 HSV: %d, %d, %d\n", gradient_100.h, gradient_100.s, gradient_100.v);
            }
            return false;
        case G2_SAI:
            if (record->event.pressed) {
                gradient_100.s = (gradient_100.s + color_adj_step * 2 <= 255) ? gradient_100.s + color_adj_step * 2 : 255;
                dprintf("Gradient 100 HSV: %d, %d, %d\n", gradient_100.h, gradient_100.s, gradient_100.v);
            }
            return false;
        case G2_SAD:
            if (record->event.pressed) {
                gradient_100.s = (gradient_100.s - color_adj_step * 2 >= 0) ? gradient_100.s - color_adj_step * 2 : 0;
                dprintf("Gradient 100 HSV: %d, %d, %d\n", gradient_100.h, gradient_100.s, gradient_100.v);
            }
            return false;
        case G2_VAI:
            if (record->event.pressed) {
                gradient_100.v = (gradient_100.v + color_adj_step * 2 <= 255) ? gradient_100.v + color_adj_step * 2 : 255;
                dprintf("Gradient 100 HSV: %d, %d, %d\n", gradient_100.h, gradient_100.s, gradient_100.v);
            }
            return false;
        case G2_VAD:
            if (record->event.pressed) {
                gradient_100.v = (gradient_100.v - color_adj_step * 2 >= 0) ? gradient_100.v - color_adj_step * 2 : 0;
                dprintf("Gradient 100 HSV: %d, %d, %d\n", gradient_100.h, gradient_100.s, gradient_100.v);
            }
            return false;
        case G_PRE:
            if (record->event.pressed) {
                gp_i = (gp_i + gp_length ) % gp_length;

                gradient_0 = gradient_presets[gp_i].gradient_0;
                gradient_100 = gradient_presets[gp_i].gradient_1;
                reflected_gradient = gradient_presets[gp_i].reflected;

                gp_i += 1;
            }
            return false;
        case REF_G:
            if (record->event.pressed) {
                reflected_gradient = !reflected_gradient;
            }
            return false;
        case G_FLIP:
            if (record->event.pressed) {
                HSV temp_color = gradient_0;
                gradient_0 = gradient_100;
                gradient_100 = temp_color;
            }
            return false;
        case RGB_C_E:
            if (record->event.pressed) {
                switch (rgb_matrix_get_mode()) {
                    case RGB_MATRIX_CUSTOM_CUSTOM_GRADIENT:
                        rgb_matrix_mode(RGB_MATRIX_CUSTOM_COOL_DIAGONAL);
                        return false;
                    case RGB_MATRIX_CUSTOM_COOL_DIAGONAL:
                        rgb_matrix_mode(RGB_MATRIX_CUSTOM_FLOWER_BLOOMING);
                        return false;
                    case RGB_MATRIX_CUSTOM_FLOWER_BLOOMING:
                        rgb_matrix_mode(RGB_MATRIX_CUSTOM_RANDOM_BREATH_RAINBOW);
                        return false;
                    default:
                        rgb_matrix_mode(RGB_MATRIX_CUSTOM_CUSTOM_GRADIENT);
                        return false;
                }
            }
            return false;
	}
    return true;
}
