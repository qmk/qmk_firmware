/* Copyright 2022 DZTECH <moyi4681@Live.cn>
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

#define MATRIX_ROWS 6
#define MATRIX_COLS 16
#define MATRIX_ROW_PINS { B0, E6, B1, B4, D1, D2 }
#define MATRIX_COL_PINS { F7, F6, F5, F4, F1, F0, D3, D5, D4, D6, D7, B5, B6, C6, E2, D0 }

#define DIODE_DIRECTION COL2ROW

/* Reduce debounce time */
#ifdef DEBOUNCE
	#undef DEBOUNCE
	#define DEBOUNCE 4
#endif

/* Disable locking support*/
#ifdef LOCKING_SUPPORT_ENABLE
	#undef LOCKING_SUPPORT_ENABLE
#endif

/* Disable locking support*/
#ifdef LOCKING_RESYNC_ENABLE
	#undef LOCKING_RESYNC_ENABLE
#endif

// #define LOCKING_SUPPORT_ENABLE
// #define LOCKING_RESYNC_ENABLE

#define LED_CAPS_LOCK_PIN C7
#define LED_SCROLL_LOCK_PIN B2
#define LED_PIN_ON_STATE 1

/* Disable RGB underglow*/
#ifdef RGB_DI_PIN
	#undef RGB_DI_PIN
#endif

/*
#define RGB_DI_PIN B3
#ifdef RGB_DI_PIN
	#define RGBLIGHT_EFFECT_BREATHING
	#define RGBLIGHT_EFFECT_RAINBOW_MOOD
	#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
	#define RGBLIGHT_EFFECT_SNAKE
	#define RGBLIGHT_EFFECT_KNIGHT
	#define RGBLIGHT_EFFECT_CHRISTMAS
	#define RGBLIGHT_EFFECT_STATIC_GRADIENT
	#define RGBLIGHT_EFFECT_RGB_TEST
	#define RGBLIGHT_EFFECT_ALTERNATING
	#define RGBLIGHT_EFFECT_TWINKLE
	#define RGBLIGHT_DEFAULT_MODE (RGBLIGHT_EFFECT_RAINBOW_MOOD + 6) 
	#define RGBLIGHT_DEFAULT_SPD 15
	#define RGBLED_NUM 20
	#define RGBLIGHT_HUE_STEP 10
	#define RGBLIGHT_SAT_STEP 10
	#define RGBLIGHT_VAL_STEP 10
	#define RGBLIGHT_SLEEP
#endif
*/

#define VIA_EEPROM_LAYOUT_OPTIONS_SIZE 2

/* Increasing performance*/
#define MATRIX_IO_DELAY 20
#define USB_POLLING_INTERVAL_MS 1
#define FORCE_NKRO

/* Disable unused features to save space*/
#define NO_ACTION_LAYER
#define NO_ACTION_ONESHOT

/* Tap-Hold configuration*/
#define TAPPING_TERM 200