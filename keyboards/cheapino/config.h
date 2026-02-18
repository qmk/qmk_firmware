/*
Copyright 2023 Thomas Haukland (@tompi)

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

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
// #define NO_DEBUG

/* disable print */
// #define NO_PRINT

/* disable action features */
// #define NO_ACTION_LAYER
// #define NO_ACTION_TAPPING
// #define NO_ACTION_ONESHOT

#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
#define WS2812_PIO_USE_PIO1 // Force the usage of PIO1 peripheral, by default the WS2812 implementation uses the PIO0 peripheral
// #define WS2812_TRST_US 80
#define WS2812_BYTE_ORDER WS2812_BYTE_ORDER_RGB

// Pick good defaults for enabling homerow modifiers
#define TAPPING_TERM 230

#define WS2812_DI_PIN GP16   // The pin connected to the data pin of the LEDs
#define RGBLIGHT_LED_COUNT 1 // The number of LEDs connected

#define MAX_DEFERRED_EXECUTORS 32

// #define DEBUG_MATRIX_SCAN_RATE

#define RGBLIGHT_DEFAULT_HUE 128 // Sets the default hue value, if none has been set
#define RGBLIGHT_DEFAULT_SAT 128 // Sets the default saturation value, if none has been set
#define RGBLIGHT_DEFAULT_VAL \
    32 // Sets the default brightness value, if none has been set
       //
