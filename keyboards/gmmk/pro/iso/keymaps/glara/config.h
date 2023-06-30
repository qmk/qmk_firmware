/* Copyright 2021 Jasper Chan
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

#define DRIVER_1_LED_TOTAL 66
#define DRIVER_2_LED_TOTAL 33
#define DRIVER_LED_TOTAL (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)

#ifdef RGB_MATRIX_ENABLE
#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#    define RGB_MATRIX_KEYPRESSES
#    define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CYCLE_PINWHEEL
#    define RGB_DISABLE_WHEN_USB_SUSPENDED
#    define RGB_DISABLE_TIMEOUT 300000 // 300 seconds / 5 min
#    define RGB_IDLE_TIMEOUT 4500 // 4.5 seconds
// #    define DISABLE_RGB_MATRIX_SOLID_COLOR
// // #    define DISABLE_RGB_MATRIX_ALPHAS_MODS
// #    define DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN
// #    define DISABLE_RGB_MATRIX_BREATHING
// #    define DISABLE_RGB_MATRIX_BAND_SAT
// #    define DISABLE_RGB_MATRIX_BAND_VAL
// #    define DISABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
// #    define DISABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
// #    define DISABLE_RGB_MATRIX_BAND_SPIRAL_SAT
// #    define DISABLE_RGB_MATRIX_BAND_SPIRAL_VAL
// #    define DISABLE_RGB_MATRIX_CYCLE_ALL
// #    define DISABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
// #    define DISABLE_RGB_MATRIX_CYCLE_UP_DOWN
// #    define DISABLE_RGB_MATRIX_CYCLE_OUT_IN
// #    define DISABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
// #    define DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
// #    define DISABLE_RGB_MATRIX_CYCLE_PINWHEEL
// #    define DISABLE_RGB_MATRIX_CYCLE_SPIRAL
// #    define DISABLE_RGB_MATRIX_DUAL_BEACON
// #    define DISABLE_RGB_MATRIX_RAINBOW_BEACON
// #    define DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS
// #    define DISABLE_RGB_MATRIX_RAINDROPS
// #    define DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
// // Requires RGB_MATRIX_FRAMEBUFFER_EFFECTS
// #    define DISABLE_RGB_MATRIX_TYPING_HEATMAP
// #    define DISABLE_RGB_MATRIX_DIGITAL_RAIN
// // RGB_MATRIX_KEYPRESSES OR RGB_MATRIX_KEYRELEASES
// #    define DISABLE_RGB_MATRIX_SOLID_REACTIVE
// #    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
// #    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
// #    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
// #    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
// #    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
// #    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
// #    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
// #    define DISABLE_RGB_MATRIX_SPLASH
// #    define DISABLE_RGB_MATRIX_MULTISPLASH
// #    define DISABLE_RGB_MATRIX_SOLID_SPLASH
// #    define DISABLE_RGB_MATRIX_SOLID_MULTISPLASH
#endif
