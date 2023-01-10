/*
QMK Firmware Massdrop CTRL M-AS Keymap
Copyright (C) 2020 matthewrobo

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// !!! DO NOT ADD #pragma once !!! //

/* Step 1. */
/* Declare custom effects using the RGB_MATRIX_EFFECT macro */
/* (note the lack of semicolon after the macro!) */

RGB_MATRIX_EFFECT(FLOWER_BLOOMING)
RGB_MATRIX_EFFECT(RAINBOW_DIAGONAL)
RGB_MATRIX_EFFECT(BAND_SAT_DEEP_RIVER)
RGB_MATRIX_EFFECT(BAND_SAT_DEEP_RIVER_REVERSE)

/* Step 2. */
/* Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block */
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

/*
 * Blooming Flower was taken from HorrorTroll
 */
#include "flower_blooming/flower_blooming.c"

/*
 * RAINBOW_DIAGONOL is a variation on COOL_DIAGONAL also from HorrorTroll 
 */
static HSV RAINBOW_DIAGONAL_math(HSV hsv, uint8_t i, uint8_t time) {
    hsv.h = (g_led_config.point[i].x / 4) - g_led_config.point[i].y - time;
    return hsv;
}

bool RAINBOW_DIAGONAL(effect_params_t* params) {
    return effect_runner_i(params, &RAINBOW_DIAGONAL_math);
}

/*
 * RGB Matrix BAND SAT/VAL
 * Static Green rotation on Blue
 */
static HSV BAND_SAT_deepriver_math(HSV hsv, uint8_t i, uint8_t time) {
    int16_t v = hsv.v - abs(scale8(g_led_config.point[i].x, 228) + 28 - time) * 8;

    /* When value is 0, then override from black to desired backgroun color */
    if (v <= 0) {
        /* When algorithm would normally set up black (v == 0), let's go back to HSV_BLUE */
        hsv.s = 255;
        hsv.v = 255;
        hsv.h = 170;
    } else {
        /* Gradient of Green (HSV_GREEN) when it isn't blue (HSV_BLUE) */
        hsv.s = 255;
        hsv.v = scale8(v < 0 ? 0 : v, hsv.v);
        hsv.h = 85;
    }

    return hsv;
}

bool BAND_SAT_DEEP_RIVER(effect_params_t *params) {
    return effect_runner_i(params, &BAND_SAT_deepriver_math);
}

/*
 * RGB Matrix BAND SAT/VAL
 * Static Blue rotation on Green
 */
static HSV BAND_SAT_deepriver_reverse_math(HSV hsv, uint8_t i, uint8_t time) {
    int16_t v = hsv.v - abs(scale8(g_led_config.point[i].x, 228) + 28 - time) * 8;

    /* When value is 0, then override from black to desired backgroun color */
    if (v <= 0) {
        /* When algorithm would normally set up black (v == 0), let's go back to HSV_GREEN */
        hsv.s = 255;
        hsv.v = 255;
        hsv.h = 85;
    } else {
        /* Gradient of Blue (HSV_BLUE) when it isn't green (HSV_GREEN) */
        hsv.s = 255;
        hsv.v = scale8(v < 0 ? 0 : v, hsv.v);
        hsv.h = 170;
    }

    return hsv;
}

bool BAND_SAT_DEEP_RIVER_REVERSE(effect_params_t *params) {
    return effect_runner_i(params, &BAND_SAT_deepriver_reverse_math);
}

#endif
