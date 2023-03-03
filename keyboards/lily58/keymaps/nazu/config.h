// Copyright 2023 Tom Sennewald (@beelzebubi)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* Select hand configuration */
// #define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#ifdef RGBLIGHT_ENABLE
#   define RGBLIGHT_HUE_STEP 6 // number of steps to cycle through the hue by
#   define RGBLIGHT_SAT_STEP 6 // number of steps to increment the saturation by
#   define RGBLIGHT_VAL_STEP 6 // number of steps to increment the brightness by
#   define RGBLIGHT_SLEEP //  the RGB lighting will be switched off when the host goes to sleep
#   define RGBLIGHT_SPLIT // synchronization functionality for split keyboards
#   define RGBLIGHT_EFFECT_RAINBOW_SWIRL // rainbow swirl animation mode
#endif

#ifdef OLED_ENABLE
// #   define OLED_DISABLE_TIMEOUT
#   define OLED_TIMEOUT 120000
#endif

#ifdef RGB_MATRIX_ENABLE
#   define RGB_MATRIX_LED_COUNT 58  // number of LEDs connected
#   define RGB_MATRIX_KEYPRESSES  // reacts to keypresses
#   define RGB_DISABLE_WHEN_USB_SUSPENDED // turn off effects when suspended
#   define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150  // limits maximum brightness of LEDs to 200 out of 255. If not defined maximum brightness is set to 255
#   define RGB_MATRIX_HUE_STEP 8
#   define RGB_MATRIX_SAT_STEP 8
#   define RGB_MATRIX_VAL_STEP 5
#   define RGB_MATRIX_SPD_STEP 10
#   define RGB_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS 50
#endif

// #ifdef TAP_DANCE_ENABLE
// #   define TAPPING_TERM 200
// #endif

/* Define tri layer numbers */
#define TRI_LAYER_LOWER_LAYER 6
#define TRI_LAYER_UPPER_LAYER 7
#define TRI_LAYER_ADJUST_LAYER 8
