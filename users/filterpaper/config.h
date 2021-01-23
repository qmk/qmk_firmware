/* Copyright (C) 2021 @filterpaper
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

// Common settings
#define TAPPING_TERM 250
#define PERMISSIVE_HOLD
#define IGNORE_MOD_TAP_INTERRUPT
#define LEADER_TIMEOUT 500
#define LEADER_PER_KEY_TIMING
#define TAP_CODE_DELAY 10

#ifdef MOUSEKEY_ENABLE
#	define MOUSEKEY_DELAY 0
#	define MOUSEKEY_INTERVAL 16
#	define MOUSEKEY_MAX_SPEED 7
#	define MOUSEKEY_TIME_TO_MAX 25 
#	define MOUSEKEY_WHEEL_DELAY 0
#	define MOUSEKEY_WHEEL_INTERVAL 50
#	define MOUSEKEY_WHEEL_TIME_TO_MAX 100
#endif

#ifdef KEYBOARD_crkbd
#	define EE_HANDS
#	define OLED_TIMEOUT 5000
#	define OLED_FONT_H "users/filterpaper/glcdfont.c"
#endif

#ifdef KEYBOARD_boardsource_the_mark
#	define DRIVER_LED_TOTAL 24
#endif

#ifdef RGB_MATRIX_ENABLE
#	define RGB_MATRIX_KEYPRESSES
#	define RGB_DISABLE_WHEN_USB_SUSPENDED true
#	define RGB_MATRIX_MAXIMUM_BRIGHTNESS 100
// Disable unused effects
#	define DISABLE_RGB_MATRIX_BAND_SAT
#	define DISABLE_RGB_MATRIX_BAND_VAL
#	define DISABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#	define DISABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#	define DISABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#	define DISABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#	define DISABLE_RGB_MATRIX_CYCLE_ALL
#	define DISABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#	define DISABLE_RGB_MATRIX_CYCLE_UP_DOWN
#	define DISABLE_RGB_MATRIX_CYCLE_OUT_IN
#	define DISABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#	define DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#	define DISABLE_RGB_MATRIX_DUAL_BEACON
#	define DISABLE_RGB_MATRIX_CYCLE_PINWHEEL
#	define DISABLE_RGB_MATRIX_CYCLE_SPIRAL
#	define DISABLE_RGB_MATRIX_RAINBOW_BEACON
#	define DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#	define DISABLE_RGB_MATRIX_RAINDROPS
#	define DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
// Layer color and effect definitions
#	define RGB_GRAY		91, 147, 153 // RGB_AZURE substitute
#	define RGB_DEFAULT	RGB_GRAY
#	define RGB_LOWER	RGB_BLUE
#	define RGB_RAISE	RGB_YELLOW
#	define RGB_ADJUST	RGB_TEAL
#	define HSV_DEFAULT	HSV_AZURE
#	define HSV_LOWER	HSV_BLUE
#	define HSV_RAISE	HSV_YELLOW
#	define HSV_ADJUST	HSV_TEAL
#	define MATRIX_NORMAL	RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#	define MATRIX_SPECIAL	RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#endif

