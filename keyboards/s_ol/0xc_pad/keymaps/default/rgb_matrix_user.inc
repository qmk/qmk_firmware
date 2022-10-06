/* Copyright 2022 s-ol
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
RGB_MATRIX_EFFECT(RGB_TESTING)
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static HSV RGB_TESTING_math(HSV hsv, uint8_t i, uint8_t time) {
    hsv.v = 255;
    hsv.s = 255;

    uint8_t t = (time + i * 6) % 256;
    switch (t / (256 / 4)) {
        case 0:
            hsv.h = 0;
            break;
        case 1:
            hsv.h = 85;
            break;
        case 2:
            hsv.h = 170;
            break;
        default:
            hsv.s = 0;
    }
    return hsv;
}

static bool RGB_TESTING(effect_params_t* params) { return effect_runner_i(params, &RGB_TESTING_math); }
#endif
