// Copyright 2023 Ryan Neff (@JellyTitan)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* - Encoder settings - */
#ifdef ENCODER_MAP_ENABLE
// Key delay for encoders (necessary for some keycodes)
#    define ENCODER_MAP_KEY_DELAY 10
#endif

#define SPLIT_HAPTIC_ENABLE
#define SOLENOID_DEFAULT_DWELL 25 
#define SOLENOID_MAX_DWELL 100
#define SOLENOID_MIN_DWELL 4
#define HAPTIC_OFF_IN_LOW_POWER 1
// Prevents thumper on mods like shift/Ctrl/Alt
#define NO_HAPTIC_MOD
#define SOLENOID_PIN GP21
/* Set tapdance speed */
#define TAPPING_TERM 210

/* Allows for the setting of constant mouse speed levels. */
/* Delay between pressing a movement key and cursor movement */
#define MOUSEKEY_DELAY 10
/* Time between cursor movements in milliseconds */
#define MOUSEKEY_INTERVAL 16
/* Step size */
#define MOUSEKEY_MOVE_DELTA 8
/* Maximum cursor speed at which acceleration stops */
#define MOUSEKEY_MAX_SPEED 2
/* Time until maximum cursor speed is reached */
#define MOUSEKEY_TIME_TO_MAX 40
/* Maximum number of scroll steps per scroll action */
#define MOUSEKEY_WHEEL_MAX_SPEED 42
/* Time until maximum scroll speed is reached */
#define MOUSEKEY_WHEEL_TIME_TO_MAX 15

#define POINTING_DEVICE_ROTATION_90
#define SPLIT_POINTING_ENABLE
#define POINTING_DEVICE_RIGHT
#define POINTING_DEVICE_TASK_THROTTLE_MS 8
/*
    - RGB Stuff -
    All effects can be found in the QMK docs:
    https://docs.qmk.fm/#/feature_rgb_matrix?id=rgb-matrix-effects
*/
#ifdef RGB_MATRIX_ENABLE

#    define RGB_DISABLE_WHEN_USB_SUSPENDED
// Decrease decay of heatmap rgb effect
#    define RGB_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS 50
// If you're setting colors per key, this is required.
#    define SPLIT_LAYER_STATE_ENABLE

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
