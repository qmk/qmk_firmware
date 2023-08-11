// Copyright 2023 Peter.Falken (@PeterFalken)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Custom RGB_MATRIX settings
#ifdef RGB_MATRIX_ENABLE
    // Remove predefined values
    #undef RGB_DISABLE_TIMEOUT
    #undef RGB_MATRIX_MAXIMUM_BRIGHTNESS
    #undef RGB_MATRIX_DEFAULT_MODE
    #undef RGB_MATRIX_DEFAULT_HUE
    #undef RGB_MATRIX_DEFAULT_SAT
    #undef RGB_MATRIX_DEFAULT_VAL

    // Redefine values
    // Number of milliseconds to wait until RGB automatically turns off
    #define RGB_MATRIX_TIMEOUT 5000
    // Limits maximum brightness of LEDs to 120 out of 255
    #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 120
    // Sets the default startup mode
    #define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_CUSTOM_active_keys
    // Sets the default hue, saturation & brightness values
    #define RGB_MATRIX_DEFAULT_HUE 0
    #define RGB_MATRIX_DEFAULT_SAT 0
    #define RGB_MATRIX_DEFAULT_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS/3
#endif  // RGB_MATRIX_ENABLE

// Custom definition
// Disable RGB_MATRIX_ANIMATIONS to free up space
#ifdef DISABLE_RGB_MATRIX_ANIMATIONS
    #undef ENABLE_RGB_MATRIX_CYCLE_ALL
    #undef ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
    #undef ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
    #undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN
    #undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
    #undef ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
    #undef ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
    #undef ENABLE_RGB_MATRIX_CYCLE_SPIRAL
    #undef ENABLE_RGB_MATRIX_RAINDROPS
    #undef ENABLE_RGB_MATRIX_SPLASH
    #undef ENABLE_RGB_MATRIX_MULTISPLASH
#endif  // DISABLE_RGB_MATRIX_ANIMATIONS
