// Copyright 2022 Ryan Neff (@JellyTitan)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define EE_HANDS

/* Turn off RGB light when host is asleep. (Doesn't seem to work for mac)? */
#define RGBLIGHT_SLEEP
#define RGBLIGHT_LAYERS
/* Decrease decay of heatmap rgb effect */
#define RGB_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS 50
/* If you're setting colors per key, this is required. */
#define SPLIT_LAYER_STATE_ENABLE

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

// Tweak how the mouse cursor moves. https://docs.qmk.fm/#/feature_mouse_keys
// Accelerated mode (default).
// MOUSEKEY_DELAY  10  Delady between pressing a movement key and cursor movement
// MOUSEKEY_INTERVAL 20  Time between cursor movements in milliseconds
// MOUSEKEY_MOVE_DELTA 8 Step size
// MOUSEKEY_MAX_SPEED  10  Maximum cursor speed at which acceleration stops
// MOUSEKEY_TIME_TO_MAX  30  Time until maximum cursor speed is reached
// MOUSEKEY_WHEEL_DELAY  10  Delay between pressing a wheel key and wheel movement
// MOUSEKEY_WHEEL_INTERVAL 80  Time between wheel movements
// MOUSEKEY_WHEEL_MAX_SPEED  8 Maximum number of scroll steps per scroll action
// MOUSEKEY_WHEEL_TIME_TO_MAX  40  Time until maximum scroll speed is reached

// Kinetic mode, alternate to the default mode.
// MK_KINETIC_SPEED  undefined Enable kinetic mode
// MOUSEKEY_DELAY  5 Delay between pressing a movement key and cursor movement
// MOUSEKEY_INTERVAL 10  Time between cursor movements in milliseconds
// MOUSEKEY_MOVE_DELTA 5 Step size for accelerating from initial to base speed
// MOUSEKEY_INITIAL_SPEED  100 Initial speed of the cursor in pixel per second
// MOUSEKEY_BASE_SPEED 1000  Maximum cursor speed at which acceleration stops
// MOUSEKEY_DECELERATED_SPEED  400 Decelerated cursor speed
// MOUSEKEY_ACCELERATED_SPEED  3000  Accelerated cursor speed
// MOUSEKEY_WHEEL_INITIAL_MOVEMENTS  16  Initial number of movements of the mouse wheel
// MOUSEKEY_WHEEL_BASE_MOVEMENTS 32  Maximum number of movements at which acceleration stops
// MOUSEKEY_WHEEL_ACCELERATED_MOVEMENTS  48  Accelerated wheel movements
// MOUSEKEY_WHEEL_DECELERATED_MOVEMENTS  8 Decelerated wheel movements
