/* Copyright 2020 ademey "MsMustard"
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
#define VENDOR_ID       0x4d4d // MM
#define PRODUCT_ID      0x545a // TZ
#define DEVICE_VER      0x0002
#define MANUFACTURER    MsMustard
#define PRODUCT         Terrazzo

/* key matrix size */

// SWAP FOR PRO MICRO
// #define MATRIX_ROWS 8
#define MATRIX_ROWS 9
#define MATRIX_COLS 6

/* key matrix pins */

// SWAP FOR PRO MICRO
// #define MATRIX_ROW_PINS { D2, D7, E6, B4, B5, B6, B2, B3 }
#define MATRIX_ROW_PINS { D2, D7, E6, B4, B5, B6, B2, B3, F0 }
#define MATRIX_COL_PINS { D3, F4, F5, F6, F7, B1 }

#define UNUSED_PINS
#define DIODE_DIRECTION COL2ROW

/* ROTARY ENCODERS */

/* 4 encoder positions are supported. With multiple
encoder support when using the extra pins of
Elite-C controller.

Use the following configuration guides for your
encoder layout. */

/* PRO MICRO CONFIGURATIONS */

/* If using a Pro Micro, only 1 encoder may be used,
and only in the top or bottom position.
Top and bottom encoders share the same net,
so there is only one configuration. */

/* TOP or BOTTOM */
// #define ENCODERS_PAD_A { C6 }
// #define ENCODERS_PAD_B { D4 }

/* ELITE-C ONLY CONFIGURATIONS */

/* TOP 3
   Default configuration */
#define ENCODERS_PAD_A { C6 , B7, C7 }
#define ENCODERS_PAD_B { D4 , D5, F1 }

/* BOTTOM 3 */
// #define ENCODERS_PAD_A { B7, C7, C6 }
// #define ENCODERS_PAD_B { D5, F1, D4 }

/* BOTTOM 2 */
// #define ENCODERS_PAD_A { C7, C6 }
// #define ENCODERS_PAD_B { F1, D4 }


#define ENCODER_RESOLUTION 2
#define BACKLIGHT_LEVELS 5

#ifdef LED_MATRIX_ENABLE

#define LED_DRIVER_ADDR_1 0x74
#define LED_DRIVER_COUNT 1
#define DRIVER_LED_TOTAL 105
#define LED_MATRIX_ROWS 15
#define LED_MATRIX_COLS 7
#define LED_MATRIX_MAXIMUM_BRIGHTNESS 20
#define LED_DISABLE_WHEN_USB_SUSPENDED

// LED Matrix Animation modes. Explicitly enabled
// For full list of effects, see:
// https://docs.qmk.fm/#/feature_led_matrix?id=led-matrix-effects
// #    define ENABLE_LED_MATRIX_ALPHAS_MODS
// #    define ENABLE_LED_MATRIX_BREATHING
// #    define ENABLE_LED_MATRIX_BAND
// #    define ENABLE_LED_MATRIX_BAND_PINWHEEL
// #    define ENABLE_LED_MATRIX_BAND_SPIRAL
// #    define ENABLE_LED_MATRIX_CYCLE_LEFT_RIGHT
// #    define ENABLE_LED_MATRIX_CYCLE_UP_DOWN
// #    define ENABLE_LED_MATRIX_CYCLE_OUT_IN
// #    define ENABLE_LED_MATRIX_DUAL_BEACON
// #    if defined(LED_MATRIX_KEYREACTIVE_ENABLED)
// #        define ENABLE_LED_MATRIX_SOLID_REACTIVE_SIMPLE
// #        define ENABLE_LED_MATRIX_SOLID_REACTIVE_WIDE
// #        define ENABLE_LED_MATRIX_SOLID_REACTIVE_MULTIWIDE
// #        define ENABLE_LED_MATRIX_SOLID_REACTIVE_CROSS
// #        define ENABLE_LED_MATRIX_SOLID_REACTIVE_MULTICROSS
// #        define ENABLE_LED_MATRIX_SOLID_REACTIVE_NEXUS
// #        define ENABLE_LED_MATRIX_SOLID_REACTIVE_MULTINEXUS
// #        define ENABLE_LED_MATRIX_SPLASH
// #        define ENABLE_LED_MATRIX_MULTISPLASH
// #    endif
// #    define ENABLE_LED_MATRIX_WAVE_LEFT_RIGHT
// #    define ENABLE_LED_MATRIX_WAVE_UP_DOWN
#endif

/* Terrazzo animations */

// #define DISABLE_TERRAZZO_EFFECT_STRIPES
// #define DISABLE_TERRAZZO_EFFECT_DINO
// #define DISABLE_TERRAZZO_EFFECT_OUTRUN
#define DISABLE_TERRAZZO_EFFECT_PAC_DUDE
#define DISABLE_TERRAZZO_EFFECT_HEART
// #define DISABLE_TERRAZZO_EFFECT_WPM_CHART
#define DISABLE_TERRAZZO_EFFECT_DOT
