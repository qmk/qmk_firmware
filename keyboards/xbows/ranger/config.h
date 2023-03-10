/* Copyright 2021 Shulin Huang <mumu@x-bows.com>
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

#ifdef RGB_MATRIX_ENABLE
#    define RGB_MATRIX_LED_PROCESS_LIMIT 18
#    define RGB_MATRIX_LED_FLUSH_LIMIT 16
#    define RGB_DISABLE_WHEN_USB_SUSPENDED       // turn off effects when suspended
#    define RGB_MATRIX_KEYPRESSES
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200
#    define RGB_MATRIX_CENTER { 103, 32 }

// RGB Matrix Animation modes. Explicitly enabled
// For full list of effects, see:
// https://docs.qmk.fm/#/feature_rgb_matrix?id=rgb-matrix-effects
#    define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_CYCLE_LEFT_RIGHT // Sets the default mode, if none has been set
#    define ENABLE_RGB_MATRIX_BREATHING           // Single hue brightness cycling animation
#    define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL     // Single hue spinning spiral fades brightness
#    define ENABLE_RGB_MATRIX_CYCLE_ALL           // Full keyboard solid hue cycling through full gradient
#    define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT    // Full gradient scrolling left to right
#    define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN       // Full gradient scrolling top to bottom
#    define ENABLE_RGB_MATRIX_CYCLE_OUT_IN        // Full gradient scrolling out to in
#    define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL      // Full gradient spinning pinwheel around center of keyboard
#    define ENABLE_RGB_MATRIX_CYCLE_SPIRAL        // Full gradient spinning spiral around center of keyboard
#    define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS   // Full dual gradients spinning two halfs of keyboard
#    define ENABLE_RGB_MATRIX_RAINDROPS           // Randomly changes a single key's hue

// enabled only of RGB_MATRIX_KEYPRESSES or RGB_MATRIX_KEYRELEASES is defined
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE   // Pulses keys hit to hue & value then fades value out
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE          // Static single hue, pulses keys hit to shifted hue then fades to current hue
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE     // Hue & value pulse near a single key hit then fades value out
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS    // Hue & value pulse the same column and row of a single key hit then fades value out
#    define ENABLE_RGB_MATRIX_SPLASH                  // Full gradient & value pulse away from a single key hit then fades value out
#    define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH       // Hue & value pulse away from multiple key hits then fades value out

#    define DRIVER_ADDR_1 0b1110100
#    define DRIVER_ADDR_2 0b1110101
#    define DRIVER_ADDR_3 0b1110110
#    define DRIVER_COUNT 3
#    define DRIVER_1_LED_TOTAL 36
#    define DRIVER_2_LED_TOTAL 36
#    define DRIVER_3_LED_TOTAL 15
#    define RGB_MATRIX_LED_COUNT (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL + DRIVER_3_LED_TOTAL)

#endif
