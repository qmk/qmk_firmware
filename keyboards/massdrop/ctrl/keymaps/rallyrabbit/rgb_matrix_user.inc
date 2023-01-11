/*
   Copyright 2023 @rallyrabbit <https://github.com/rallyrabbit>
   All code except for "Flower Blooming" animation
   SPDX-License-Identifier: GPL-2.0-or-later

   Flower Blooming Animation
   Copyright 2022 HorrorTroll <https://github.com/HorrorTroll>
   SPDX-License-Identifier: GPL-2.0-or-later
*/

/* !!! DO NOT ADD #pragma once !!! */

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
#include "flower_blooming.h"

static HSV FLOWER_BLOOMING_math(HSV hsv, uint8_t i, uint8_t time) {
    if (g_led_config.point[i].y > k_rgb_matrix_center.y)
        hsv.h = g_led_config.point[i].x * 3 - g_led_config.point[i].y * 3 + time;
    else
        hsv.h = g_led_config.point[i].x * 3 - g_led_config.point[i].y * 3 - time;
    return hsv;
}

bool FLOWER_BLOOMING(effect_params_t* params) { return effect_runner_bloom(params, &FLOWER_BLOOMING_math); }

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
