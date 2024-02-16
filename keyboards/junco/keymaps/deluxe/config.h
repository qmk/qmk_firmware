// Copyright 2022 Dane Skalski (@Daneski13)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* Indicator LEDs */
// LED index for caps lock key on the extension layer
#define CAPS_LOCK_LED_INDEX 25
// LED index for num lock key on the symbol layer
#define NUM_LOCK_LED_INDEX 62
// LED index for key that sticks the adjust layer
#define ADJST_LED_INDEX 19

// Number of Layers that can be used by VIA.
// Change this if you want more layers
#define DYNAMIC_KEYMAP_LAYER_COUNT 6

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

// Allows the indicator LEDs to work
#    define SPLIT_LED_STATE_ENABLE
#    define SPLIT_LAYER_STATE_ENABLE

// Default effect when EEPROM cleared
#    define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_RAINBOW_MOVING_CHEVRON

// Turns off RGB effects when there is no longer a USB connection
#    define RGB_MATRIX_SLEEP

// Throttling of RGB to increase keyboard responsiveness, set to 1.5x the default limits
#    define RGB_MATRIX_LED_PROCESS_LIMIT (RGB_MATRIX_LED_COUNT + 4) / 6 // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
#    define RGB_MATRIX_LED_FLUSH_LIMIT 24                               // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms), the default, is equivalent to limiting to 60fps

// Key press reactive animations
#    define SPLIT_TRANSPORT_MIRROR // Necessary setting for key press animations
#    define RGB_MATRIX_KEYPRESSES  // Enables key press effects
#    define ENABLE_RGB_MATRIX_MULTISPLASH

// Normal effects
#    define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#    define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#    define ENABLE_RGB_MATRIX_PIXEL_RAIN

#endif
