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

#ifdef LED_MATRIX_ENABLE

#define IS31FL3731_I2C_ADDRESS_1 IS31FL3731_I2C_ADDRESS_GND
#define LED_MATRIX_LED_COUNT 105
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
