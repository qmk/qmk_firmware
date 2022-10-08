/*
Copyright 2020 Gondolindrim

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

#include "config_common.h"

#define MATRIX_ROWS 5
#define MATRIX_COLS 15

#define MATRIX_COL_PINS { A10, A9, A8, B14, B12, B11, B10, B2, B1, A7, A5, B9, B8, B7, B6 }
#define MATRIX_ROW_PINS { B3, A15, B0, B4, B5 }

#define DIODE_DIRECTION COL2ROW

#define BACKLIGHT_PIN A6
#define BACKLIGHT_PWM_DRIVER PWMD3
#define BACKLIGHT_PWM_CHANNEL 1
#define BACKLIGHT_PAL_MODE 1
#define BACKLIGHT_BREATHING
#define BACKLIGHT_LEVELS 20
#define BACKLIGHT_DEFAULT_LEVEL	10
#define BREATHING_PERIOD 3

#define RGB_DI_PIN B15
#define RGBLED_NUM 16
#define RGBLIGHT_LIMIT_VAL 200
#define RGBLIGHT_SLEEP
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

#define RGBLIGHT_DEFAULT_MODE (RGBLIGHT_MODE_RAINBOW_SWIRL + 5)

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* define if matrix has ghost (lacks anti-ghosting diodes) */
//#define MATRIX_HAS_GHOST

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

// Elongate has six indicator LEDs. These def's are the indicator pin defs. The LEDs are distributed in two clusters: one next to the numpad and another between spacebars; LEDs are numbered top-to-bottom.

#define LED1_PIN A2
#define LED2_PIN A1
#define LED3_PIN A0
#define LED4_PIN A4
#define LED5_PIN A3
#define LED6_PIN F1
