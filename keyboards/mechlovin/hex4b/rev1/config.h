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
#define DEVICE_VER   0x0001
#define PRODUCT      Hex-4B Rev.1

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
 */

#define MATRIX_ROW_PINS { B7, A2, A1, A3, A4, A5 }
#define MATRIX_COL_PINS { B6, B5, B3, B2, B1, B0, A0, A6, A7, C7, C6, C5, C4, D1, D0 }
#define UNUSED_PINS

#define LED_NUM_LOCK_PIN D6
#define LED_CAPS_LOCK_PIN D7
#define LED_SCROLL_LOCK_PIN D5
//#define LED_COMPOSE_PIN B3
//#define LED_KANA_PIN B4

#define BACKLIGHT_PIN D4
#define BACKLIGHT_LEVELS 5
#define BACKLIGHT_BREATHING

/* Bootmagic Lite key configuration, Backspace */
#define BOOTMAGIC_LITE_ROW 1
#define BOOTMAGIC_LITE_COLUMN 14
