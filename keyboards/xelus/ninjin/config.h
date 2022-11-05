/* Copyright 2021 Harrison Chan (Xelus)
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

/* USB Device descriptor parameter */
#define VENDOR_ID       0x5845  // XE
#define PRODUCT_ID      0x4E4A  // NJ
#define DEVICE_VER      0x0001
#define MANUFACTURER    Xelus
#define PRODUCT         Ninjin

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 17

#define MATRIX_COL_PINS { A9, A8, B15, B14, B13, B12, B11, B10, B2, B1, B0, A7, A6, A5, A4, B6, B5 }
#define MATRIX_ROW_PINS { B4, B3, A15, A3, B9, B8 }
#define DIODE_DIRECTION COL2ROW

/* RGB Underglow */
#define RGB_DI_PIN A10
#define RGBLED_NUM 26
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_LIMIT_VAL 200

// PWM RGB Underglow Defines
#define WS2812_PWM_DRIVER PWMD1
#define WS2812_PWM_CHANNEL 3
#define WS2812_PWM_PAL_MODE 2
#define WS2812_DMA_STREAM STM32_DMA1_STREAM5
#define WS2812_DMA_CHANNEL 3
#define WS2812_EXTERNAL_PULLUP

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define LED_CAPS_LOCK_PIN A2
#define LED_SCROLL_LOCK_PIN A13
#define LED_PIN_ON_STATE 1