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

#define MATRIX_ROW_PINS { A4, B12, B13, B14, B15, A1 }
#define MATRIX_COL_PINS { B11, B10, B2, B1, B0, A7, A6, A5, A3, C13, B7, B6, B5, B4, B3 }

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