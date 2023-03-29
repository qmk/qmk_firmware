/* Copyright 2021 Jonavin Eng @Jonavin
   Copyright 2022 gourdo1 <gourdo1@outlook.com>
   
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

// Force n-key rollover
#define FORCE_NKRO

// Set TT to two taps
#define TAPPING_TOGGLE 2

#ifdef COMMAND_ENABLE
#define IS_COMMAND() (get_mods() == MOD_MASK_CTRL) //debug commands accessed by holding down both CTRLs: https://github.com/qmk/qmk_firmware/blob/master/docs/feature_command.md
#endif

// Caps Word configuration
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
#define CAPS_WORD_IDLE_TIMEOUT 10000      // Automatically turn off after x milliseconds of idle. 0 to never timeout.

// Handle GRAVESC combo keys
#define GRAVE_ESC_ALT_OVERRIDE
// Always send Escape if Alt is pressed
#define GRAVE_ESC_CTRL_OVERRIDE
// Always send Escape if Control is pressed

// #define TAPPING_TERM 180
#define TAPPING_TERM 300
#define TAPPING_TERM_PER_KEY

#ifdef RGB_MATRIX_ENABLE
    #define RGB_DISABLE_WHEN_USB_SUSPENDED
    #define RGB_MATRIX_KEYPRESSES            // Enables REACTIVE & SPLASH modes
    #define RGB_MATRIX_FRAMEBUFFER_EFFECTS   // Enables Heatmap, Rain

    // RGB step values
    #define RGBLIGHT_HUE_STEP 32             // The number of steps to cycle through the hue by (default 10)
    #define RGBLIGHT_SAT_STEP 17             // The number of steps to increment the saturation by (default 17)
    #define RGBLIGHT_VAL_STEP 17             // The number of steps to increment the brightness by (default 17)

    // Startup values, when none have been set
    #define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_REACTIVE // Sets the default effect mode, if none has been set (was RGB_MATRIX_SOLID_COLOR)
    #define RGB_MATRIX_DEFAULT_HUE 24                         // Sets the default hue value, if none has been set
    #define RGB_MATRIX_DEFAULT_SAT 255                        // Sets the default saturation value, if none has been set
    #define RGB_MATRIX_DEFAULT_VAL 127                        // Sets the default brightness value, if none has been set
    #define RGB_MATRIX_DEFAULT_SPD 127                        // Sets the default animation speed, if none has been set

    // Uncomment any #undef line below to turn OFF any default enabled RGB background effect (enabled in keyboards/gmmk/pro/config.h).
    #undef ENABLE_RGB_MATRIX_ALPHAS_MODS                      // Solid color (seems redundant; seems same as RGB_MATRIX_SOLID_COLOR?)
    //#undef ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN               // Static, horizontal rainbow
    //#undef ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT            // Static, vertical Rainbow
    //#undef ENABLE_RGB_MATRIX_BREATHING                      // Breathing animation using selected HSV color
    #undef ENABLE_RGB_MATRIX_BAND_SAT                         // Single hue band fading saturation scrolling left to right (with white)
    //#undef ENABLE_RGB_MATRIX_BAND_VAL                       // Single hue band fading brightness scrolling left to right (with black)
    #undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT                // Single hue 3 blade spinning pinwheel fades sat (with white)
    //#undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL              // Single hue 3 blade spinning pinwheel fades brightness (with black)
    #undef ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT                  // Single hue spinning spiral fades brightness (with white)
    //#undef ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL                // Single hue spinning spiral fades brightness (with black)
    //#undef ENABLE_RGB_MATRIX_CYCLE_ALL                      // Full keyboard cycling through rainbow
    //#undef ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT               // Full gradient moving left to right
    //#undef ENABLE_RGB_MATRIX_CYCLE_UP_DOWN                  // Full gradient scrolling top to bottom
    #undef ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON           // Full gradient chevron scrolling left to right (too similar to cycle left right)
    //#undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN                   // Rainbow circles coming to center.
    #undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL                // Two Rainbow circles coming to 1/3 and 2/3 points. (seems mostly redundant with above)
    #undef ENABLE_RGB_MATRIX_CYCLE_PINWHEEL                   // Built-in cycling pinwheel (seems redundant with below)
    //#undef ENABLE_RGB_MATRIX_CYCLE_SPIRAL                   // Full gradient spinning spiral around center of keyboard
    #undef ENABLE_RGB_MATRIX_RAINBOW_BEACON                   // Spinning rainbow (more distracting transitions)
    //#undef ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS              // Spinning rainbow (smoother)
    #undef ENABLE_RGB_MATRIX_DUAL_BEACON                      // Two rainbows spinning around keyboard (distracting, busy)
    #undef ENABLE_RGB_MATRIX_RAINDROPS                        // Sustained raindrops of blue, green, yellow (confusing to use with RGB layers)
    //#undef ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS            // Sustained raindrops of blue, purple, pink, green (confusing to use with RGB layers, but slightly better than above)
    #undef ENABLE_RGB_MATRIX_HUE_BREATHING                    // Hue shifts up a slight amount at the same time, then shifts back (very subtle)
    #undef ENABLE_RGB_MATRIX_HUE_PENDULUM                     // Hue shifts up a slight amount in a wave to the right, then back to the left (very subtle)
    #undef ENABLE_RGB_MATRIX_HUE_WAVE                         // Hue shifts up a slight amount and then back down in a wave to the right (very subtle)
    //#undef ENABLE_RGB_MATRIX_PIXEL_RAIN                     // Non-sustained raindrops of pastel colors
    #undef ENABLE_RGB_MATRIX_PIXEL_FLOW                       // More active version of pixel rain with quick cycling (unusable, very distracting)
    #undef ENABLE_RGB_MATRIX_PIXEL_FRACTAL                    // Same as Pixel Flow but with current HSV only (somewhat distracting)
        //Only enabled if RGB_MATRIX_FRAMEBUFFER_EFFECTS is defined
    //#undef ENABLE_RGB_MATRIX_TYPING_HEATMAP                 // Fading heatmap that follows keystrokes (has buggy side LEDs that glow red)
    //#undef ENABLE_RGB_MATRIX_DIGITAL_RAIN                   // The Matrix (has buggy side LEDs that glow red)
        //Only enabled if RGB_MATRIX_KEYPRESSES or RGB_MATRIX_KEYRELEASES is defined
    //#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE          // Key hits shown in current hue - all other keys black
    //#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE                 // Keyboard lights up in chosen hue, key hits shown in complementary hue (try this as default?)
    #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE              // Hue & value pulse around a single key hit then fades value out (Single key)
    //#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE       // same as above but more intense (Multi-key)
    #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS             // Column and Row single current color fade (Single key)
    //#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS      // Column and Row single color fade. (Multi-key)
    #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS             // Hue & value pulse away on the same column and row of key hit then fades (Single key)
    //#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS      // Hue & value pulse away on the same column and row of multi-key hit then fades
    //#undef ENABLE_RGB_MATRIX_SPLASH                         // Full rainbow pulses from key hit. All else black.
    #undef ENABLE_RGB_MATRIX_MULTISPLASH                      // Full rainbow pulses from multi-keys. All else black. (distracting on multiple keystroke hits)
    #undef ENABLE_RGB_MATRIX_SOLID_SPLASH                     // Single color pulses from key hit. All else black. (distracting on multiple key hits)
    //#undef ENABLE_RGB_MATRIX_SOLID_MULTISPLASH              // Single color pulses from muli-keys. All else black.
#endif //RGB_MATRIX_ENABLE

// Add a layer for colemak  -- set "COLEMAK_LAYER_ENABLE = yes" in rules.mk to enable
#if defined COLEMAK_LAYER_ENABLE
    #ifdef GAME_ENABLE
        #define DYNAMIC_KEYMAP_LAYER_COUNT 6
        #define _COLEMAK 5
    #else
        #define DYNAMIC_KEYMAP_LAYER_COUNT 5
        #define _COLEMAK 4
    #endif //GAME_ENABLE
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
