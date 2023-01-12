/*
   Copyright 2023 @rallyrabbit <https://github.com/rallyrabbit>
   SPDX-License-Identifier: GPL-2.0-or-later
*/

/* !!! DO NOT ADD #pragma once !!! */

/* Step 1. */
/* Declare custom effects using the RGB_MATRIX_EFFECT macro */
/* (note the lack of semicolon after the macro!) */

RGB_MATRIX_EFFECT(RAINBOW_DIAGONAL)
RGB_MATRIX_EFFECT(BAND_SAT_DEEP_RIVER)
RGB_MATRIX_EFFECT(BAND_SAT_DEEP_RIVER_REVERSE)
RGB_MATRIX_EFFECT(DEEP_RIVER_CYLON)

/* Step 2. */
/* Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block */
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

/*
 * DEEP RIVER CYCLON - Green and Blue mimicing BSG Cylon Robot Eye
 */

/* Support function for CYLON Animation */
static uint8_t time_to_led(uint8_t time, uint8_t ledBehind, uint8_t ledCount) {
    uint16_t ledTime = ledCount * time;
    uint16_t step = ((2 * ledCount + (ledTime / 128)) - ledBehind) % (2 * ledCount);
    uint8_t led;

    if (step < ledCount) {
        led = step;
    } else {
        led = ledCount - 1 - (step - ledCount);
    }

    return led;
}

static HSV DEEP_RIVER_CYLON_math(HSV hsv, uint8_t i, uint8_t time) {
    /* Row 1 (Escape/Functions to Pause) */
    /* Row 2 (Number row to page up) */
    /* Row 3 (First row of letters to Page Down */
    uint8_t ledFirst[3] = {   0,  16,  33 };
    uint8_t ledCount[3] = {  16,  17,  17 };
    uint8_t hsv_h[3]    = { 170,  85, 170 };

    /* Row 1/3: Base Color as Deep River Green */
    /* Row 2: Base Color as Deep River Green */
    /* The Blue and Green Color Targeting Share some of the HSV Hue and Value settings */
    hsv.s = 255;
    hsv.v = 255;

    bool effectLedFound = false;

    /* Traverse the possible LED Matches by desired positions in rows */
    for (uint8_t row=0; row < 3; row++) {
        if (i >= ledFirst[row] && i < ledFirst[row] + ledCount[row]) {
            uint8_t j = i - ledFirst[row];

            if (j == time_to_led(time, 0, ledCount[row])) {
                hsv.h = hsv_h[row];
                hsv.v = hsv.v;
                effectLedFound = true;
                break;
            } else if (j == time_to_led(time, 1, ledCount[row])) {
                hsv.h = hsv_h[row];
                hsv.v = hsv.v / 2;
                effectLedFound = true;
                break;
            } else if (j == time_to_led(time, 2, ledCount[row])) {
                hsv.h = hsv_h[row];
                hsv.v = hsv.v / 4;
                effectLedFound = true;
                break;
            } else if (j == time_to_led(time, 3, ledCount[row])) {
                hsv.h = hsv_h[row];
                hsv.v = hsv.v / 8;
                effectLedFound = true;
                break;
            } else {
                /* Position not on, turn off (Black) */
                hsv.v = 0;
                effectLedFound = true;
                break;
            }
        }
    }

    /* No Match Found */
    if (effectLedFound == false) {
        /* Off (Black) */
        hsv.v = 0;
    }

    return hsv;
}

bool DEEP_RIVER_CYLON(effect_params_t* params) {
    return effect_runner_i(params, &DEEP_RIVER_CYLON_math);
}

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
