/*
Base Copyright 2017 Luiz Ribeiro <luizribeiro@gmail.com>
Modified 2017 Andrew Novak <ndrw.nvk@gmail.com>
Modified 2018 Harshit Goel <Harshitgoel96@yahoo.com>
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

#include "config_common.h"

#pragma once

/* matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 15
#define MATRIX_ROW_PINS { B0, B1, B2, B3, B4, B5, B6, B7 }
#define MATRIX_COL_PINS { A0, A1, A2, A3, A4, A5, A6, A7, C7, C6, C5, C4, C3, C2, D7 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define LED_NUM_LOCK_PIN D0
#define LED_CAPS_LOCK_PIN D1
#define LED_PIN_ON_STATE 0

#define BACKLIGHT_PIN D4
#define BACKLIGHT_LEVELS 12
#define BACKLIGHT_BREATHING

#define TAPPING_TOGGLE 3

#define USB_MAX_POWER_CONSUMPTION 100

/* RGB underglow */
// The RGB_DI_PIN value seems to be shared between all PS2AVRGB boards.
// The same pin is used on the JJ40, at least.
#define RGBLED_NUM 18
#define RGB_DI_PIN E2 // NOTE: for PS2AVRGB boards, underglow commands are sent via I2C to 0xB0.
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
/*#define RGBLIGHT_VAL_STEP 20*/
