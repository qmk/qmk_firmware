/*
Copyright 2020 Team Mechlovin

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


/* USB Device descriptor parameter */
#define VENDOR_ID    0x4D4C
#define PRODUCT_ID   0xD750 
#define DEVICE_VER   0x0002
#define PRODUCT      Olly Octagon

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 16

#define MATRIX_ROW_PINS { B0, B12, A6, A5, A4, A3 }
#define MATRIX_COL_PINS { B11, B10, B2, B1, B0, A7, A6, A5, A3, C13, B7, B6, B5, B4, B3 }
#define UNUSED_PINS

#define LED_NUM_LOCK_PIN C15
#define LED_CAPS_LOCK_PIN B9
#define LED_SCROLL_LOCK_PIN A15
//#define LED_COMPOSE_PIN B3
//#define LED_KANA_PIN B4

#define BACKLIGHT_PIN B8
#define BACKLIGHT_LEVELS 5
#define BACKLIGHT_PWM_DRIVER PWMD4
#define BACKLIGHT_BREATHING

/* Bootmagic Lite key configuration, Backspace */
#define BOOTMAGIC_LITE_ROW 1
#define BOOTMAGIC_LITE_COLUMN 14

#define LED_PIN_ON_STATE 0

/* Bootmagic Lite key configuration, Backspace */
#define BOOTMAGIC_LITE_ROW 1
#define BOOTMAGIC_LITE_COLUMN 14
