/* Copyright 2021 Jay Greco
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

/* Used to set host for remote KB if VUSB detect doesn't work. */
// #define KEYBOARD_HOST // Force host mode
// #define KEYBOARD_REMOTE // Force remote mode

// Workaround for freezing after MacOS sleep
#define NO_USB_STARTUP_CHECK

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 16
#define MATRIX_MUX_COLS 4

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 10

/*
 * Keyboard Matrix Assignments
 * The nibble uses a demultiplexer for the cols.
 * to free up more IOs for awesomeness!
 * See matrix.c for more details.
*/
#define MATRIX_ROW_PINS { B1, B3, B2, B6, D4 }
#define MATRIX_COL_MUX_PINS { F4, F5, F6, F7 }
#define MATRIX_COL_PINS { }

/* Optional SMT LED pins */
#define RGB_DI_PIN E6
#define RGBLED_NUM 10
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
#define RGBLIGHT_SLEEP

/* Optional encoder pins */
#define ENCODERS_PAD_A { B5 }
#define ENCODERS_PAD_B { B4 }
