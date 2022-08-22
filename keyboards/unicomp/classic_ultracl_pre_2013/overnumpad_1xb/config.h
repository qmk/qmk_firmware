/* Copyright 2020 Purdea Andrei
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

#define SERIAL_NUMBER "purdea.ro:overnumpad_controller"

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 16

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

// All pins in order from left-to-right, as seen on the keyboard:
// C3, C2, C1, C0, A3, A4, A5, A6, A7, C4, C5, B0, B1, B10, B12, B13, B14, B15, C6, C7, C8, C9, A8, A9, A10, 
// On this chip A10, B10 have stronger pull-ups, so it's better to avoid them if possible.

// On this keyboard the right-most pin is not used, so that is A10.
// On this keyboard the right-most 8 pins (excluding the unused pin) are routed on the bottom.

#define MATRIX_COL_PINS { C3, C2, C1, C0, A3, A4, A5, A6, A7, C4, C5, B0, B1, B10, B12, B13 }
#define MATRIX_ROW_PINS { B14, B15, C6, C7, C8, C9, A8, A9 }
//#define UNUSED_PINS

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION ROW2COL

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* define if matrix has ghost (lacks anti-ghosting diodes) */
#define MATRIX_HAS_GHOST

#define STM32_HSECLK 16000000

#define SOLENOID_PIN B5
#define HAPTIC_ENABLE_PIN C13
#define SOLENOID_DEFAULT_DWELL 4
#define SOLENOID_MIN_DWELL 4
#define HAPTIC_OFF_IN_LOW_POWER 1
#define NO_HAPTIC_MOD

#define LED_NUM_LOCK_PIN C12
#define LED_CAPS_LOCK_PIN C11
#define LED_SCROLL_LOCK_PIN C10
#define LED_ON_STATE 1
