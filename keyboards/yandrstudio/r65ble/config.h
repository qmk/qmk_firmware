/* Copyright 2021 JasonRen(biu)
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

/* USB Device descriptor parameter */
#define VENDOR_ID 0xAA96
#define PRODUCT_ID 0xAA03
#define DEVICE_VER 0x0001
#define RAW_USAGE_PAGE 0xFF60
#define MANUFACTURER YandR studio and Magic Mvp
#define PRODUCT r65ble

/* key matrix set */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

#define MATRIX_ROW_PINS { B5, C13, A3, A2, B9 }
#define MATRIX_COL_PINS { C14, B4, A8, B14, B13, B12, B11, B10, B1, B0, A7, A6, A5, A4, B8 }


#define DIODE_DIRECTION COL2ROW
#define DEBOUNCE 5



// enable the nkro when using the VIA.
#define FORCE_NKRO

// fix VIA RGB_light
#define VIA_HAS_BROKEN_KEYCODES




#ifdef RGBLIGHT_ENABLE
#    define RGB_DI_PIN B15
#    define RGBLED_NUM 68
#    define RGBLIGHT_ANIMATIONS
#endif // RGBLIGHT_ENABLE




/* RGN Matrix */
#ifdef RGB_MATRIX_ENABLE

#    define RGB_DI_PIN B15
#    define RGBLED_NUM 68
#    define DRIVER_LED_TOTAL RGBLED_NUM
#define WS2812_SPI SPID2 // default: SPID1
#define WS2812_SPI_MOSI_PAL_MODE 5

#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 180
#    define RGBLIGHT_VAL_STEP 18
#    define RGB_DISABLE_WHEN_USB_SUSPENDED true
#    define RGB_MATRIX_CENTER { 32, 96 }
#    define RGB_MATRIX_KEYPRESSES
#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS

#endif

/* Encoder */
#ifdef ENCODER_ENABLE
#    define ENCODERS_PAD_A { A15 }
#    define ENCODERS_PAD_B { B3 }
#    define ENCODER_RESOLUTION 4
//#    define ENCODER_DIRECTION_FLIP
#endif

/* MOUSEKEY */
#ifdef MOUSEKEY_ENABLE
#    define MOUSEKEY_DELAY 0
#    define MOUSEKEY_INTERVAL 17
#    define MK_3_SPEED
#    define MK_MOMENTARY_ACCEL
#    define MK_C_OFFSET_UNMOD 64
#    define MK_C_INTERVAL_UNMOD 17
#endif



/* Others */
#define TAP_HOLD_CAPS_DELAY 20
#define TAP_CODE_DELAY 10
#ifdef CONSOLE_ENABLE
// #    define DEBUG_MATRIX_SCAN_RATE
#endif

