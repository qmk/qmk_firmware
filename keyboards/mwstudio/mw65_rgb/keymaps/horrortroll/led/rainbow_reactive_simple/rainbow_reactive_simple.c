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

#include "led/rainbow_reactive_simple/rainbow_reactive_simple.h"

static HSV RAINBOW_REACTIVE_SIMPLE_math(HSV hsv, uint8_t i, uint8_t time, uint16_t offset) {
    hsv.h = g_led_config.point[i].x - time;
    hsv.v = scale8(255 - offset, hsv.v);
    return hsv;
}

bool RAINBOW_REACTIVE_SIMPLE(effect_params_t* params) { return effect_rainbow_reactive(params, &RAINBOW_REACTIVE_SIMPLE_math); }
