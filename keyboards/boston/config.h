/* Copyright 2020 Pylon
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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

/* key matrix size */
#define MATRIX_ROWS 7
#define MATRIX_COLS 19

#define MATRIX_COL_PINS \
    { B10, B11, B12, B13, B14, B15, A8, A9, A10, A15, B3, B4, B7, B8, B9, C14, C15, F0, A3 }
#define MATRIX_ROW_PINS \
    { B5, B6, A7, B0, B1, B2, A4 }
#define DIODE_DIRECTION COL2ROW

#define BACKLIGHT_PIN A6
#define BACKLIGHT_PWM_DRIVER PWMD3
#define BACKLIGHT_PWM_CHANNEL 1
#define BACKLIGHT_PAL_MODE 1
#define BACKLIGHT_LEVELS 6
#define BACKLIGHT_BREATHING
#define BREATHING_PERIOD 6

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* Define RGBLED */
#define RGB_DI_PIN A5
#define RGBLED_NUM 1
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_LAYERS

//The 3D-printed version of Boston uses APA106 LEDs, which are reversed 
#define WS2812_BYTE_ORDER WS2812_BYTE_ORDER_RGB

/* Define encoder */
#define ENCODERS_PAD_A \
    { C13 }
#define ENCODERS_PAD_B \
    { F1 }
#define ENCODER_RESOLUTION 2
#define TAP_CODE_DELAY 15

/* Lock LEDs */
#define LED_NUM_LOCK_PIN A0
#define LED_CAPS_LOCK_PIN A1
#define LED_SCROLL_LOCK_PIN A2

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
