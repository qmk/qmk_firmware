/* Copyright 2020 Shulin Huang <mumu@x-bows.com>
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

#define VENDOR_ID    0xFEED
#define PRODUCT_ID   0x1226
#define DEVICE_VER   0x0001
#define MANUFACTURER X-BOWS
#define PRODUCT      NATURE

#define MATRIX_ROWS 6
#define MATRIX_COLS 15
#define MATRIX_ROW_PINS { F7, F6, F5, F4, F1, F0 }
#define MATRIX_COL_PINS { B0, B1, B2, B3, B7, D2, D3, D5, D4, D6, D7, B4, B5, B6, C6 }
#define DIODE_DIRECTION COL2ROW
#define DEBOUNCE 3

/* disable these deprecated features by default */
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

#ifdef RGB_MATRIX_ENABLE
#    define RGB_MATRIX_LED_PROCESS_LIMIT 18
#    define RGB_MATRIX_LED_FLUSH_LIMIT 16
#    define RGB_DISABLE_AFTER_TIMEOUT 0          // number of ticks to wait until disabling effects
#    define RGB_DISABLE_WHEN_USB_SUSPENDED       // turn off effects when suspended
#    define RGB_MATRIX_KEYPRESSES
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200
#    define RGB_MATRIX_CENTER \
        { 92, 33 }

#    define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CYCLE_LEFT_RIGHT // Sets the default mode, if none has been set
#    define DISABLE_RGB_MATRIX_ALPHAS_MODS               // Static dual hue, speed is hue for secondary hue
#    define DISABLE_RGB_MATRIX_SOLID_COLOR               // Static single hue, no speed support
#    define DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN          // Static gradient top to bottom, speed controls how much gradient changes
#    define DISABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT       // Static gradient left to right, speed controls how much gradient changes
#    define DISABLE_RGB_MATRIX_BAND_SAT                  // Single hue band fading saturation scrolling left to right
#    define DISABLE_RGB_MATRIX_BAND_VAL                  // Single hue band fading brightness scrolling left to right
#    define DISABLE_RGB_MATRIX_BAND_PINWHEEL_SAT         // Single hue 3 blade spinning pinwheel fades saturation
#    define DISABLE_RGB_MATRIX_BAND_PINWHEEL_VAL         // Single hue 3 blade spinning pinwheel fades brightness
#    define DISABLE_RGB_MATRIX_BAND_SPIRAL_SAT           // Single hue spinning spiral fades saturation
#    define DISABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL         // Full dual gradients scrolling out to in
#    define DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON    // Full gradent Chevron shapped scrolling left to right
#    define DISABLE_RGB_MATRIX_DUAL_BEACON               // Full gradient spinning around center of keyboard
#    define DISABLE_RGB_MATRIX_RAINBOW_BEACON            // Full tighter gradient spinning around center of keyboard
#    define DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS         // Full dual gradients spinning two halfs of keyboard
#    define DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS       // Randomly changes a single key's hue and saturation
#    define DISABLE_RGB_MATRIX_HUE_BREATHING             // Hue shifts up a slight ammount at the same time, then shifts back
#    define DISABLE_RGB_MATRIX_HUE_PENDULUM              // Hue shifts up a slight ammount in a wave to the right, then back to the left
#    define DISABLE_RGB_MATRIX_HUE_WAVE                  // Hue shifts up a slight ammount and then back down in a wave to the right

#    define DISABLE_RGB_MATRIX_DIGITAL_RAIN              // That famous computer simulation
#    define DISABLE_RGB_MATRIX_TYPING_HEATMAP            // How hot is your WPM!

#    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE  // Hue & value pulse near multiple key hits then fades value out
#    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS // Hue & value pulse the same column and row of multiple key hits then fades value out
#    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS      // Hue & value pulse away on the same column and row of a single key hit then fades value out
#    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS // Hue & value pulse away on the same column and row of multiple key hits then fades value out
#    define DISABLE_RGB_MATRIX_MULTISPLASH               // Full gradient & value pulse away from multiple key hits then fades value out
#    define DISABLE_RGB_MATRIX_SOLID_SPLASH              // Hue & value pulse away from a single key hit then fades value out

#    define DRIVER_ADDR_1 0b1110100
#    define DRIVER_ADDR_2 0b1110110
#    define DRIVER_ADDR_3 0b1110101
#    define DRIVER_COUNT 3
#    define DRIVER_1_LED_TOTAL 36
#    define DRIVER_2_LED_TOTAL 36
#    define DRIVER_3_LED_TOTAL 15
#    define DRIVER_LED_TOTAL (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL + DRIVER_3_LED_TOTAL)
#endif
