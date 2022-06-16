/* Copyright 2021 Jonavin Eng @Jonavin
   Copyright 2022 gourdo1 <jcblake@outlook.com>
   
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

#define TAPPING_TOGGLE 2
// TT set to two taps

/* Handle GRAVESC combo keys */
#define GRAVE_ESC_ALT_OVERRIDE
// Always send Escape if Alt is pressed
#define GRAVE_ESC_CTRL_OVERRIDE
// Always send Escape if Control is pressed

// #define TAPPING_TERM 180
#define TAPPING_TERM 300
#define TAPPING_TERM_PER_KEY

#ifdef RGB_MATRIX_ENABLE
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_SOLID_COLOR
#define RGB_DISABLE_WHEN_USB_SUSPENDED
#endif

// RGB step values
#define RGBLIGHT_HUE_STEP 32 // The number of steps to cycle through the hue by (default 10)
#define RGBLIGHT_SAT_STEP 17 // The number of steps to increment the saturation by (default 17)
#define RGBLIGHT_VAL_STEP 17 // The number of steps to increment the brightness by (default 17)

// add fifth layer for colemak  -- set "COLEMAK_LAYER_ENABLE = yes" in rules.mk to enable
#if defined COLEMAK_LAYER_ENABLE
#define DYNAMIC_KEYMAP_LAYER_COUNT 5
#define _COLEMAK 4
#endif // COLEMAK_LAYER_ENABLE

/*
// Mouse Keys Accelerated Mode Definitions
#define MOUSEKEY_DELAY 3               // Delay between pressing a movement key and cursor movement (default: 10)
#define MOUSEKEY_INTERVAL 13           // Time between cursor movements in milliseconds (default: 20); Try setting to 1000/monitor refresh for smooth movement.
#define MOUSEKEY_MOVE_DELTA 8          // Step size (default: 8)
#define MOUSEKEY_MAX_SPEED 9           // Maximum cursor speed at which acceleration stops (default: 10)
#define MOUSEKEY_TIME_TO_MAX 150       // Time until maximum cursor speed is reached (default: 30)
#define MOUSEKEY_WHEEL_DELAY 0         // Delay between pressing a wheel key and wheel movement (default: 10)
#define MOUSEKEY_WHEEL_INTERVAL 80     // Time between wheel movements (default: 80)
#define MOUSEKEY_WHEEL_MAX_SPEED 8     // Maximum number of scroll steps per scroll action (default: 8)
#define MOUSEKEY_WHEEL_TIME_TO_MAX 40  // Time until maximum scroll speed is reached (default: 40)
*/

// Mouse Keys Kinetic Mode Definitions
#define MK_KINETIC_SPEED                        // Enable Kinetic mode:  Uses a quadratic curve on cursor speed to allow precise movements at the beginning and increases speed thereafter.
#define MOUSEKEY_DELAY 3                        // Delay between pressing a movement key and cursor movement (default: 10)
#define MOUSEKEY_INTERVAL 13                    // Time between cursor movements in milliseconds (default: 20); Try setting to 1000/monitor refresh for smooth movement.
#define MOUSEKEY_MOVE_DELTA 5                   // Step size for accelerating from initial to base speed (default: 8)
#define MOUSEKEY_MOVE_MAX 50                    // use instead of BASE SPEED to limit speed in Kinetic mode
#define MOUSEKEY_INITIAL_SPEED 100              // Initial speed of the cursor in pixels per second (default: 100)
//#define MOUSEKEY_BASE_SPEED 800               // (broken in QMK 0.16.0) Maximum cursor speed at which acceleration stops (default: 1000)
#define MOUSEKEY_DECELERATED_SPEED 400          // Decelerated cursor speed (default: 400)
#define MOUSEKEY_ACCELERATED_SPEED 2000         // Accelerated cursor speed (default: 3000)
#define MOUSEKEY_WHEEL_INITIAL_MOVEMENTS 16     // Initial number of movements of the mouse wheel (default: 16)
#define MOUSEKEY_WHEEL_BASE_MOVEMENTS 32        // Maximum number of movements at which acceleration stops (default: 32)
#define MOUSEKEY_WHEEL_ACCELERATED_MOVEMENTS 48 // Accelerated wheel movements (default: 48)
#define MOUSEKEY_WHEEL_DECELERATED_MOVEMENTS 8  // Decelerated wheel movements (default: 8)
