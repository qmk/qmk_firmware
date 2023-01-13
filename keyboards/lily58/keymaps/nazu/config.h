// Copyright 2023 Tom Sennewald (@beelzebubi)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* Select hand configuration */
#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#ifdef RGBLIGHT_ENABLE
#   define RGBLIGHT_HUE_STEP 6 // number of steps to cycle through the hue by
#   define RGBLIGHT_SAT_STEP 6 // number of steps to increment the saturation by
#   define RGBLIGHT_VAL_STEP 6 // number of steps to increment the brightness by
#   define RGBLIGHT_SLEEP //  the RGB lighting will be switched off when the host goes to sleep
#   define RGBLIGHT_SPLIT // synchronization functionality for split keyboards
#   undef RGBLIGHT_EFFECT_ALTERNATING // alternating animation mode
#   undef RGBLIGHT_EFFECT_BREATHING // breathing animation mode
#   undef RGBLIGHT_EFFECT_CHRISTMAS // christmas animation mode
#   undef RGBLIGHT_EFFECT_KNIGHT // knight animation mode
#   undef RGBLIGHT_EFFECT_RAINBOW_MOOD // rainbow mood animation mode
#   define RGBLIGHT_EFFECT_RAINBOW_SWIRL // rainbow swirl animation mode
#   undef RGBLIGHT_EFFECT_RGB_TEST // RGB test animation mode
#   undef RGBLIGHT_EFFECT_SNAKE // snake animation mode
#   undef RGBLIGHT_EFFECT_STATIC_GRADIENT // static gradient mode
#   undef RGBLIGHT_EFFECT_TWINKLE // twinkle animation mode
#endif

#ifdef OLED_ENABLE
// #   define OLED_DISABLE_TIMEOUT
#   define OLED_TIMEOUT 120000
#endif

#ifdef RGB_MATRIX_ENABLE
#   define DRIVER_LED_TOTAL 58  // number of LEDs connected
#   define RGB_MATRIX_KEYPRESSES  // reacts to keypresses
// #   define RGB_MATRIX_KEYRELEASES // reacts to keyreleases (instead of keypresses)
// #   define RGB_DISABLE_AFTER_TIMEOUT 0 // number of ticks to wait until disabling effects
#   define RGB_DISABLE_WHEN_USB_SUSPENDED // turn off effects when suspended
// #   define RGB_MATRIX_LED_PROCESS_LIMIT (DRIVER_LED_TOTAL + 4) / 5 // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
// #   define RGB_MATRIX_LED_FLUSH_LIMIT 16 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
#   define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150  // limits maximum brightness of LEDs to 200 out of 255. If not defined maximum brightness is set to 255
#   define RGB_MATRIX_HUE_STEP 8
#   define RGB_MATRIX_SAT_STEP 8
#   define RGB_MATRIX_VAL_STEP 5
#   define RGB_MATRIX_SPD_STEP 10
// disabling effects
#   define DISABLE_RGB_MATRIX_ALPHA_MODS
#   define DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#   define DISABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#   define DISABLE_RGB_MATRIX_BREATHING
#   define DISABLE_RGB_MATRIX_BAND_SAT
#   define DISABLE_RGB_MATRIX_BAND_VAL
#   define DISABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#   define DISABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#   define DISABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#   define DISABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#   define DISABLE_RGB_MATRIX_CYCLE_ALL
#   define DISABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#   define DISABLE_RGB_MATRIX_CYCLE_UP_DOWN
#   define DISABLE_RGB_MATRIX_CYLCE_OUT_IN
#   define DISABLE_RGB_MATRIX_CYLCE_OUT_IN_DUAL
#   define DISABLE_RGB_MATRIX_CYLCE_PINWHEEL
#   define DISABLE_RGB_MATRIX_CYLCE_SPIRAL
#   define DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#   define DISABLE_RGB_MATRIX_DUAL_BEACON
#   define DISABLE_RGB_MATRIX_RAINBOW_BEACON
#   define DISABLE_RGB_MATRIX_RAINBOW_PINWHEEL
#   define DISABLE_RGB_MATRIX_RAINDROPS
#   define DISABLE_RGB_MATRIX_JELLYBEANS_RAINDROPS
#   define DISABLE_RGB_MATRIX_HUE_BREATHING
#   define DISABLE_RGB_MATRIX_HUE_PENDULUM
#   define DISABLE_RGB_MATRIX_HUE_WAVE
// #   define DISABLE_RGB_MATRIX_TYPING_HEATMAP
#   define DISABLE_RGB_MATRIX_DIGITAL_RAIN
#   define DISABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#   define DISABLE_RGB_MATRIX_SOLID_REACTIVE
#   define DISABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#   define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#   define DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#   define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#   define DISABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#   define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#   define DISABLE_RGB_MATRIX_SPLASH
#   define DISABLE_RGB_MATRIX_MULTISPLASH
#   define DISABLE_RGB_MATRIX_SOLID_SPLASH
#   define DISABLE_RGB_MATRIX_SOLID_MULTISPLASH
#   define RGB_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS 50
#endif

#ifdef TAP_DANCE_ENABLE
#   define TAPPING_TERM 200
#endif

// If you are using an Elite C rev3 on the slave side, uncomment the lines below:
// #define SPLIT_USB_DETECT
// #define NO_USB_STARTUP_CHECK

// Tests for reducing firmware size
// #define NO_ACTION_MACRO
// #define NO_ACTION_FUNCTION
