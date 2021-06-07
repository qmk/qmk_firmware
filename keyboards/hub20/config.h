/*
Copyright 2020 joshajohnson 
Copyright 2021 peepeetee

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

/* USB Device descriptor parameter */
#define VENDOR_ID       0x6A6A  // JJ
#define PRODUCT_ID      0x4414  // H20
#define DEVICE_VER      0x0001
#define MANUFACTURER    Josh Johnson
#define PRODUCT         Hub20

/* key matrix */
#define MATRIX_ROWS 6
#define MATRIX_COLS 4

#define MATRIX_ROW_PINS { A13, B14, A10, A0, A2, A1 }
#define MATRIX_COL_PINS { A6, A7, B7, B6 }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* Rotary Encoder Things */
// #define ENCODER_DIRECTION_FLIP
#define ENCODERS_PAD_A { B12, A8 }
#define ENCODERS_PAD_B { B13, A9 }

#define RGB_DI_PIN B15
#define RGBLED_NUM 27

#define DRIVER_LED_TOTAL 27
#ifdef RGB_DI_PIN
    #define RGBLED_NUM 27
#endif

#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES

// This list in in the correct mode order. Next mode is the following line, previous mode is previous line. Loops around.
// #define DISABLE_RGB_MATRIX_SOLID_COLOR                   // Static single hue, no speed support
#define DISABLE_RGB_MATRIX_ALPHAS_MODS                   // Static dual hue, speed is hue for secondary hue
//#define DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN              // Static gradient top to bottom, speed controls how much gradient changes
//#define DISABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT           // Static gradient top to bottom, speed controls how much gradient changes
//#define DISABLE_RGB_MATRIX_BREATHING                     // Single hue brightness cycling animation
#define DISABLE_RGB_MATRIX_BAND_SAT                      // Single hue band fading saturation scrolling left to right
#define DISABLE_RGB_MATRIX_BAND_VAL                      // Single hue band fading brightness scrolling left to right
#define DISABLE_RGB_MATRIX_BAND_PINWHEEL_SAT             // Single hue 3 blade spinning pinwheel fades saturation
#define DISABLE_RGB_MATRIX_BAND_PINWHEEL_VAL             // Single hue 3 blade spinning pinwheel fades brightness
#define DISABLE_RGB_MATRIX_BAND_SPIRAL_SAT               // Single hue spinning spiral fades saturation
#define DISABLE_RGB_MATRIX_BAND_SPIRAL_VAL               // Single hue spinning spiral fades brightness
#define DISABLE_RGB_MATRIX_CYCLE_ALL                     // Full keyboard solid hue cycling through full gradient
//#define DISABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT              // Full gradient scrolling left to right
//#define DISABLE_RGB_MATRIX_CYCLE_UP_DOWN                 // Full gradient scrolling top to bottom
#define DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON        // Full gradent Chevron shapped scrolling left to right
#define DISABLE_RGB_MATRIX_CYCLE_OUT_IN                  // Full gradient scrolling out to in
#define DISABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL             // Full dual gradients scrolling out to in
#define DISABLE_RGB_MATRIX_CYCLE_PINWHEEL                // Full gradient spinning pinwheel around center of keyboard
#define DISABLE_RGB_MATRIX_CYCLE_SPIRAL                  // Full gradient spinning spiral around center of keyboard
#define DISABLE_RGB_MATRIX_DUAL_BEACON                   // Full gradient spinning around center of keyboard
#define DISABLE_RGB_MATRIX_RAINBOW_BEACON                // Full tighter gradient spinning around center of keyboard
#define DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS             // Full dual gradients spinning two halfs of keyboard
//#define DISABLE_RGB_MATRIX_RAINDROPS                     // Randomly changes a single key's hue
//#define DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS           // Randomly changes a single key's hue and saturation
// =================================================== Requires RGB_MATRIX_FRAMEBUFFER_EFFECTS =============================================================
// #define DISABLE_RGB_MATRIX_TYPING_HEATMAP                // How hot is your WPM!
//#define DISABLE_RGB_MATRIX_DIGITAL_RAIN                  // That famous computer simulation
// =================================================== RGB_MATRIX_KEYPRESSES OR RGB_MATRIX_KEYRELEASES =====================================================
//#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE         // Pulses keys hit to hue & value then fades value out
//#define DISABLE_RGB_MATRIX_SOLID_REACTIVE                // Static single hue, pulses keys hit to shifted hue then fades to current hue
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE           // Hue & value pulse near a single key hit then fades value out
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE      // Hue & value pulse near multiple key hits then fades value out
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS          // Hue & value pulse the same column and row of a single key hit then fades value out
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS     // Hue & value pulse the same column and row of multiple key hits then fades value out
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS          // Hue & value pulse away on the same column and row of a single key hit then fades value out
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS     // Hue & value pulse away on the same column and row of multiple key hits then fades value out
#define DISABLE_RGB_MATRIX_SPLASH                        // Full gradient & value pulse away from a single key hit then fades value out
#define DISABLE_RGB_MATRIX_MULTISPLASH                   // Full gradient & value pulse away from multiple key hits then fades value out
#define DISABLE_RGB_MATRIX_SOLID_SPLASH                  // Hue & value pulse away from a single key hit then fades value out
#define DISABLE_RGB_MATRIX_SOLID_MULTISPLASH             // Hue & value pulse away from multiple key hits then fades value out

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Tap delay for tap vs hold */
#define TAPPING_TERM 200

/* Slow down key press speed to ensure computer picks it up */
#define TAP_CODE_DELAY 10

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* disable these deprecated features by default */
#ifndef LINK_TIME_OPTIMIZATION_ENABLE
  #define NO_ACTION_MACRO
  #define NO_ACTION_FUNCTION
#endif
