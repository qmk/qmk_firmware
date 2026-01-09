/* Copyright 2025 @ Raw HID Menu Mod
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

// ========================================
// ENCODER GESTURE TIMING CONFIGURATION
// ========================================
// These values can be tuned for responsiveness vs. accuracy
// Increase LONG_PRESS_MS for more deliberate long-press detection
// Decrease DOUBLE_TAP_MS for faster double-tap requirements

// Defined in keymap.c, documented here for reference:
// #define LONG_PRESS_MS 500    // Time to hold for long-press (milliseconds)
// #define DOUBLE_TAP_MS 300    // Max time between taps for double-tap (milliseconds)

// ========================================
// RGB MATRIX CONFIGURATION
// ========================================
// If you need to save flash space, uncomment these to disable specific effects

// #define DISABLE_RGB_MATRIX_ALPHAS_MODS
// #define DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN
// #define DISABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
// #define DISABLE_RGB_MATRIX_BREATHING
// #define DISABLE_RGB_MATRIX_BAND_SAT
// #define DISABLE_RGB_MATRIX_BAND_VAL
// #define DISABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
// #define DISABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
// #define DISABLE_RGB_MATRIX_BAND_SPIRAL_SAT
// #define DISABLE_RGB_MATRIX_BAND_SPIRAL_VAL
// #define DISABLE_RGB_MATRIX_CYCLE_ALL
// #define DISABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
// #define DISABLE_RGB_MATRIX_CYCLE_UP_DOWN
// #define DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
// #define DISABLE_RGB_MATRIX_CYCLE_OUT_IN
// #define DISABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
// #define DISABLE_RGB_MATRIX_CYCLE_PINWHEEL
// #define DISABLE_RGB_MATRIX_CYCLE_SPIRAL
// #define DISABLE_RGB_MATRIX_DUAL_BEACON
// #define DISABLE_RGB_MATRIX_RAINBOW_BEACON
// #define DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS
// #define DISABLE_RGB_MATRIX_RAINDROPS
// #define DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
// #define DISABLE_RGB_MATRIX_HUE_BREATHING
// #define DISABLE_RGB_MATRIX_HUE_PENDULUM
// #define DISABLE_RGB_MATRIX_HUE_WAVE
// #define DISABLE_RGB_MATRIX_PIXEL_RAIN
// #define DISABLE_RGB_MATRIX_PIXEL_FLOW
// #define DISABLE_RGB_MATRIX_PIXEL_FRACTAL

// ========================================
// RAW HID CONFIGURATION
// ========================================
// If VIA conflicts arise, you can try defining a custom usage page
// Uncomment these lines to use a different HID endpoint than VIA
// Note: This may not fully resolve conflicts; disabling VIA is recommended if issues persist

// #define RAW_USAGE_PAGE 0xFF61  // Custom usage page (default is 0xFF60)
// #define RAW_USAGE_ID 0x62      // Custom usage ID (default is 0x61)
