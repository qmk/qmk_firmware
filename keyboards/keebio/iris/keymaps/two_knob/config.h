/*
Copyright 2017 Danny Nguyen <danny@keeb.io>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

// #define USE_I2C
#define EE_HANDS

// Turn off RGB light when host is asleep. (Doesn't seem to work for mac)?
#define RGBLIGHT_SLEEP
#define RGBLIGHT_LAYERS
// Decrease decay of heatmap rgb effect
#define RGB_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS 50
// If you're setting colors per key, this is required.
#define SPLIT_LAYER_STATE_ENABLE

// If you type too fast, it confuses the Mod key combos. This resolves it:
#define IGNORE_MOD_TAP_INTERRUPT

// Set tapdance speed:
#define TAPPING_TERM 175

// Allows for the setting of constant mouse speed levels.
#define MOUSEKEY_DELAY 10 // Delay between pressing a movement key and cursor movement
#define MOUSEKEY_INTERVAL 16 // Time between cursor movements in milliseconds
#define MOUSEKEY_MOVE_DELTA 8 // Step size
#define MOUSEKEY_MAX_SPEED 2 // Maximum cursor speed at which acceleration stops
#define MOUSEKEY_TIME_TO_MAX 40 // Time until maximum cursor speed is reached
#define MOUSEKEY_WHEEL_MAX_SPEED 42 // Maximum number of scroll steps per scroll action
#define MOUSEKEY_WHEEL_TIME_TO_MAX 15 // Time until maximum scroll speed is reached

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

// Used for debugging. Switching these off saves space.
#ifndef NO_DEBUG
#define NO_DEBUG
#endif // !NO_DEBUG
#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
#define NO_PRINT
#endif // !NO_PRINT