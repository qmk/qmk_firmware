/* Copyright 2022 Moritz Plattner
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

/* Limit layer count to fit in storage with VIA enabled */
#define DYNAMIC_KEYMAP_LAYER_COUNT 3

/* key matrix size */
#define MATRIX_ROWS 7
#define MATRIX_COLS 19

#define MATRIX_ROW_PINS { B7, B3, D2, C12, C11, C10, A15 }
#define MATRIX_COL_PINS { A1, A0, C3, C2, F1, F0, C15, C14, C13, C4, C5, B0, B1, B2, B9, A13, A8, C9, C8 }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW
#define DEBOUNCE 5

#define LED_NUM_LOCK_PIN B6
#define LED_CAPS_LOCK_PIN B5
#define LED_SCROLL_LOCK_PIN B4
#define LED_PIN_ON_STATE 0

/* Backlight */
#define BACKLIGHT_PIN A9
#define BACKLIGHT_BREATHING // don't disable even if you don't want breathing - it will not compile without
#define BACKLIGHT_PWM_DRIVER PWMD1
#define BACKLIGHT_PWM_CHANNEL 2
#define BACKLIGHT_PAL_MODE 2
#define BACKLIGHT_LEVELS 5
#define BACKLIGHT_ON_STATE 1
#define BACKLIGHT_PWM_OUTPUT_FREQUENCY 1000

/* I2C for OLED */
#define I2C_DRIVER I2CD2
#define I2C1_SCL_PIN        B10
#define I2C1_SDA_PIN        B11
#define I2C1_SCL_PAL_MODE   1
#define I2C1_SDA_PAL_MODE   1
#define I2C1_TIMINGR_PRESC  0U
#define I2C1_TIMINGR_SCLDEL 3U
#define I2C1_TIMINGR_SDADEL 1U
#define I2C1_TIMINGR_SCLH   3U
#define I2C1_TIMINGR_SCLL   9U
