/* Copyright 2021 Matt Gauf
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

// clang-format off
#pragma once

/* Defaults */
#define RAW_USAGE_PAGE  0x200
#define RAW_USAGE_ID    0x40

/* Board Features */
#define DYNAMIC_MACRO_SIZE 512

/* RGB Matrix Features */
#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_COLOR
#define RGB_DISABLE_WHEN_USB_SUSPENDED true

/* RGB Matrix Framebuffer Config */
// #define RGB_MATRIX_FRAMEBUFFER_EFFECTS
// #define RGB_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS 25

/* RGB Matrix Disabled Effects */
#define DISABLE_RGB_MATRIX_ALPHAS_MODS                      // Static dual hue, speed is hue for secondary hue
#define DISABLE_RGB_MATRIX_BAND_PINWHEEL_SAT                // Single hue 3 blade spinning pinwheel fades saturation
#define DISABLE_RGB_MATRIX_BAND_PINWHEEL_VAL                // Single hue 3 blade spinning pinwheel fades brightness
#define DISABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL                // Full dual gradients scrolling out to in
#define DISABLE_RGB_MATRIX_CYCLE_PINWHEEL                   // Full gradient spinning pinwheel around center of keyboard
#define DISABLE_RGB_MATRIX_DUAL_BEACON                      // Full gradient spinning around center of keyboard
#define DISABLE_RGB_MATRIX_RAINBOW_BEACON                   // Full tighter gradient spinning around center of keyboard
#define DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS                // Full dual gradients spinning two halfs of keyboard
#define DISABLE_RGB_MATRIX_RAINDROPS                        // Randomly changes a single key's hue
#define DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS              // Randomly changes a single key's hue and saturation
#define DISABLE_RGB_MATRIX_HUE_PENDULUM                     // Hue shifts up a slight ammount in a wave to the right, then back to the left
#define DISABLE_RGB_MATRIX_HUE_WAVE                         // Hue shifts up a slight ammount and then back down in a wave to the right

#if defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS)
    #define DISABLE_RGB_MATRIX_DIGITAL_RAIN                 // That famous computer simulation
#endif

#if defined(RGB_MATRIX_KEYPRESSES) || defined(RGB_MATRIX_KEYRELEASES)
    #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE          // Hue & value pulse near a single key hit then fades value out
    #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS         // Hue & value pulse the same column and row of a single key hit then fades value out
    #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS         // Hue & value pulse away on the same column and row of a single key hit then fades value out
    #define DISABLE_RGB_MATRIX_SPLASH                       // Full gradient & value pulse away from a single key hit then fades value out
    #define DISABLE_RGB_MATRIX_SOLID_SPLASH                 // Hue & value pulse away from a single key hit then fades value out
#endif

#define DISABLE_RGB_MATRIX_EFFECT_MAX
// clang-format on
