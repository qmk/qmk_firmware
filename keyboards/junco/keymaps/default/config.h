// Copyright 2022 Dane Skalski (@Daneski13)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* - Encoder settings - */
#ifdef ENCODER_ENABLE
#    define ENCODER_RESOLUTION 4
#endif
#ifdef ENCODER_MAP_ENABLE
// Key delay for encoders (necessary for some keycodes)
#    define ENCODER_MAP_KEY_DELAY 10
#endif

/*
    - RGB Stuff -
    All effects can be found in the QMK docs:
    https://docs.qmk.fm/#/feature_rgb_matrix?id=rgb-matrix-effects
*/
#ifdef RGB_MATRIX_ENABLE

// Default effect when EEPROM cleared
#    define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_RAINBOW_MOVING_CHEVRON

// Turns off RGB effects when there is no longer a USB connection
#    define RGB_DISABLE_WHEN_USB_SUSPENDED

// Key press reactive animations
#    define SPLIT_TRANSPORT_MIRROR // Necessary setting for key press animations
#    define RGB_MATRIX_KEYPRESSES  // Enables key press effects
#    define ENABLE_RGB_MATRIX_MULTISPLASH

// Normal effects
#    define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#    define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#    define ENABLE_RGB_MATRIX_PIXEL_RAIN

#endif
