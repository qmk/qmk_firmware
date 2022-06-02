/* Copyright 2021 Tybera
 * Copyright 2021 thewerther
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x6964 /* "id" */
#define PRODUCT_ID      0x0067
#define DEVICE_VER      0x0002
#define MANUFACTURER    IDOBAO
#define PRODUCT         ID67

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
 */
#define MATRIX_ROW_PINS { B0, B1, B2, B3, F7 }
#define MATRIX_COL_PINS { C7, F6, F5, F4, F1, B7, D5, D1, D2, D3, D4, D0, D6, D7, B4 }

#define DIODE_DIRECTION COL2ROW
#define RGB_DI_PIN F0

// RGB Matrix config
#if defined(RGB_MATRIX_ENABLE)
    #ifndef ID67_DISABLE_UNDERGLOW
        #define DRIVER_LED_TOTAL 77
    #else
        #define DRIVER_LED_TOTAL 67
    #endif

    #define RGB_DISABLE_WHEN_USB_SUSPENDED  // turn off effects when suspended
    #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150    // limits maximum brightness of LEDs to x out of 255. If not defined maximum brightness is set to 255

    #define RGB_MATRIX_KEYPRESSES

    #define ENABLE_RGB_MATRIX_ALPHAS_MODS          // Static dual hue, speed is hue for secondary hue
    #define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN     // Static gradient top to bottom, speed controls how much gradient changes
    #define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT  // Static gradient left to right, speed controls how much gradient changes
    #define ENABLE_RGB_MATRIX_BREATHING            // Single hue brightness cycling animation
    #define ENABLE_RGB_MATRIX_BAND_SAT             // Single hue band fading saturation scrolling left to right
    #define ENABLE_RGB_MATRIX_BAND_VAL             // Single hue band fading brightness scrolling left to right
    #define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT    // Single hue 3 blade spinning pinwheel fades saturation
    #define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL    // Single hue 3 blade spinning pinwheel fades brightness
    #define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT      // Single hue spinning spiral fades saturation
    #define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL      // Single hue spinning spiral fades brightness
    #define ENABLE_RGB_MATRIX_CYCLE_ALL            // Full keyboard solid hue cycling through full gradient
    #define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT     // Full gradient scrolling left to right
    #define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN        // Full gradient scrolling top to bottom
    #define ENABLE_RGB_MATRIX_CYCLE_OUT_IN         // Full gradient scrolling out to in
    #define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL    // Full dual gradients scrolling out to in
    #define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON  // Full gradient Chevron shaped scrolling left to right
    #define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL       // Full gradient spinning pinwheel around center of keyboard
    #define ENABLE_RGB_MATRIX_CYCLE_SPIRAL         // Full gradient spinning spiral around center of keyboard
    #define ENABLE_RGB_MATRIX_DUAL_BEACON          // Full gradient spinning around center of keyboard
    #define ENABLE_RGB_MATRIX_RAINBOW_BEACON       // Full tighter gradient spinning around center of keyboard
    #define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS    // Full dual gradients spinning two halfs of keyboard
    #define ENABLE_RGB_MATRIX_RAINDROPS            // Randomly changes a single key's hue
    #define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS  // Randomly changes a single key's hue and saturation
    #define ENABLE_RGB_MATRIX_HUE_BREATHING        // Hue shifts up a slight amount at the same time, then shifts back
    #define ENABLE_RGB_MATRIX_HUE_PENDULUM         // Hue shifts up a slight amount in a wave to the right, then back to the left
    #define ENABLE_RGB_MATRIX_HUE_WAVE             // Hue shifts up a slight amount and then back down in a wave to the right

    // don't need `#if`, animation modes themselves check defines
    // #if defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS)
    // #define ENABLE_RGB_MATRIX_TYPING_HEATMAP
    // #define ENABLE_RGB_MATRIX_DIGITAL_RAIN
    // #endif // #if defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS)

    // don't need `#if`, animation modes themselves check defines
    // #if defined(RGB_MATRIX_KEYPRESSES) || defined(RGB_MATRIX_KEYRELEASES)
    #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE// Pulses keys hit to hue & value then fades value out
    #define ENABLE_RGB_MATRIX_SOLID_REACTIVE       // Static single hue, pulses keys hit to shifted hue then fades to current hue
    #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE       // Hue & value pulse near a single key hit then fades value out
    #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE  // Hue & value pulse near multiple key hits then fades value out
    #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS      // Hue & value pulse the same column and row of a single key hit then fades value out
    #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS // Hue & value pulse the same column and row of multiple key hits then fades value out
    #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS      // Hue & value pulse away on the same column and row of a single key hit then fades value out
    #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS // Hue & value pulse away on the same column and row of multiple key hits then fades value out
    #define ENABLE_RGB_MATRIX_SPLASH               // Full gradient & value pulse away from a single key hit then fades value out
    #define ENABLE_RGB_MATRIX_MULTISPLASH          // Full gradient & value pulse away from multiple key hits then fades value out
    #define ENABLE_RGB_MATRIX_SOLID_SPLASH         // Hue & value pulse away from a single key hit then fades value out
    #define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH    // Hue & value pulse away from multiple key hits then fades value out
    // #endif // #if defined(RGB_MATRIX_KEYPRESSES) || defined(RGB_MATRIX_KEYRELEASES)
#endif // #if defined(RGB_MATRIX_ENABLE)
