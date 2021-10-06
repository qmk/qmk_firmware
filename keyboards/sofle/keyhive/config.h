/* Copyright
 *   2021 solartempest
 *   2021 QMK
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

// USB Device descriptor parameter

#define VENDOR_ID    0xFC32
#define PRODUCT_ID   0x1287
#define DEVICE_VER   0x0002
#define MANUFACTURER Keyhive
#define PRODUCT      Sofle  // VIA version for this PCB is incorrect for the bottom row

// Key matrix size
// Rows are doubled-up. Added extra column for rotary encoder VIA mapping.
#define MATRIX_ROWS  10
#define MATRIX_COLS  6

// wiring of each half
#define MATRIX_ROW_PINS \
    { C6, D7, E6, B4, B5 }
#define MATRIX_COL_PINS \
    { B6, B2, B3, B1, F7, F6 }
#define MATRIX_ROW_PINS_RIGHT \
    { C6, D7, E6, B4, B5 }
#define MATRIX_COL_PINS_RIGHT \
    { F6, F7, B1, B3, B2, B6 }

#define DIODE_DIRECTION COL2ROW

#define DEBOUNCE        5

// Encoder support
#define ENCODERS_PAD_A \
    { F5 }
#define ENCODERS_PAD_B \
    { F4 }
#define ENCODERS_PAD_A_RIGHT \
    { F4 }
#define ENCODERS_PAD_B_RIGHT \
    { F5 }
#define ENCODER_RESOLUTIONS \
    { 4, 2 }  // Left encoder seems to have double-output issue but right does not.

#define TAP_CODE_DELAY  10

// Communication between sides
#define SOFT_SERIAL_PIN D2

// OLED settings
#define OLED_TIMEOUT    80000
#define OLED_BRIGHTNESS 90

#define SPLIT_WPM_ENABLE
#define SPLIT_OLED_ENABLE
#define SPLIT_TRANSPORT_MIRROR

// Add RGB underglow
#define RGB_DI_PIN D3
#define RGBLED_NUM 74
#define RGBLED_SPLIT \
    { 37, 37 }

#define RGBLIGHT_LIMIT_VAL 160  // Power draw may exceed 0.6A at max brightness with white colour.
#define RGBLIGHT_LAYERS
#define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF
#define RGBLIGHT_SLEEP

#define DRIVER_LED_TOTAL RGBLED_NUM
#define RGB_MATRIX_SPLIT RGBLED_SPLIT

#define RGB_MATRIX_KEYPRESSES           // reacts to keypresses
#define RGB_DISABLE_WHEN_USB_SUSPENDED  // turn off effects when suspended
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES  // reacts to keypresses
// #   define RGB_MATRIX_KEYRELEASES // reacts to keyreleases (instead of keypresses)
// #   define RGB_DISABLE_AFTER_TIMEOUT 0 // number of ticks to wait until disabling effects
#define RGB_DISABLE_WHEN_USB_SUSPENDED  // turn off effects when suspended
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
// #   define RGB_MATRIX_LED_PROCESS_LIMIT (DRIVER_LED_TOTAL + 4) / 5 // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
// #   define RGB_MATRIX_LED_FLUSH_LIMIT 16 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150  // limits maximum brightness of LEDs to 150 out of 255. Higher may cause the controller to crash.

#define RGB_MATRIX_STARTUP_MODE       RGB_MATRIX_GRADIENT_LEFT_RIGHT

#define RGB_MATRIX_HUE_STEP           8
#define RGB_MATRIX_SAT_STEP           8
#define RGB_MATRIX_VAL_STEP           8
#define RGB_MATRIX_SPD_STEP           10
