/* Copyright 2020-2022 Lorenzo Leonini
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#define MATRIX_COL_PINS { C6, B6, B5, B4, D7, D6, F0, F1, F4, F5, F6, F7 }
#define MATRIX_ROW_PINS { C7, D5, D3, D2 }

#define QMK_LED E6

#define RGB_DI_PIN B7

#define DRIVER_LED_TOTAL 42
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 170
#define RGB_MATRIX_CENTER { 112, 32 }
#define RGB_DISABLE_WHEN_USB_SUSPENDED
#define RGB_MATRIX_LED_PROCESS_LIMIT 21
#define RGB_MATRIX_LED_FLUSH_LIMIT 16
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CYCLE_LEFT_RIGHT
#define RGB_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS 20
#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_SAT_STEP 24
#define RGB_MATRIX_HUE_STEP 8
#define RGB_MATRIX_VAL_STEP 16
#define RGB_MATRIX_SPD_STEP 16

#define ENABLE_RGB_MATRIX_BREATHING
#define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#define ENABLE_RGBLIGHT_MODE_STATIC_LIGHT
#define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#define ENABLE_RGB_MATRIX_PIXEL_FRACTAL
#define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#define ENABLE_RGB_MATRIX_PIXEL_RAIN
#define ENABLE_RGB_MATRIX_DIGITAL_RAIN
#define ENABLE_RGB_MATRIX_BAND_VAL
#define ENABLE_RGB_MATRIX_SPLASH
