/* Copyright 2022 HorrorTroll <https://github.com/HorrorTroll>
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

#include "led/flower_blooming/flower_blooming.h"

static hsv_t FLOWER_BLOOMING_math(hsv_t hsv, uint8_t i, uint8_t time) {
    if (g_led_config.point[i].y > k_rgb_matrix_center.y)
        hsv.h = g_led_config.point[i].x * 3 - g_led_config.point[i].y * 3 + time;
    else
        hsv.h = g_led_config.point[i].x * 3 - g_led_config.point[i].y * 3 - time;
    return hsv;
}

bool FLOWER_BLOOMING(effect_params_t* params) { return effect_runner_bloom(params, &FLOWER_BLOOMING_math); }
