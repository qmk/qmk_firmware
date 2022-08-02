/* Copyright 2021 Oliver Granlund
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

#define MATRIX_ROWS 10
#define MATRIX_COLS 8
#define MATRIX_ROW_PINS { E6, F0, F5, F6, C7, C6, B4, D7, D6, D4 }
#define MATRIX_COL_PINS { F4, F1, F7, B2, D1, D2, B3, B1 }

#define DIODE_DIRECTION COL2ROW
#define ENCODERS_PAD_A { B7 }
#define ENCODERS_PAD_B { B0 }
#define ENCODER_RESOLUTION 4
#define UNUSED_PINS

#define LED_CAPS_LOCK_PIN B6
#define BACKLIGHT_ON_STATE  0

#define BACKLIGHT_PIN B5
#define BACKLIGHT_LEVELS 5

#define GRAVE_ESC_CTRL_OVERRIDE

/* RGB Light Configuration */

#define RGB_DI_PIN D5
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 11
#define RGBLIGHT_LED_MAP { 4, 3, 2, 1, 0, 10, 9, 8, 7, 6, 5 }
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_LIMIT_VAL 200

/* Handle volume control issue with rotary encoder */

#define TAP_CODE_DELAY 10
