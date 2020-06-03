/* Copyright 2020 QMK
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

/* USB Device descriptor parameter */
#undef VENDOR_ID
#define VENDOR_ID 0x1209
#undef PRODUCT_ID
#define PRODUCT_ID 0x345C
#undef DEVICE_VER
#define DEVICE_VER 0x0001
#undef MANUFACTURER
#define MANUFACTURER "https://github.com/stapelberg"
#undef PRODUCT
#define PRODUCT "kinT (kint36)"

/* key matrix size */
#define MATRIX_ROWS 15
#define MATRIX_COLS 7

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
#define MATRIX_ROW_PINS { D3, C3, C4, C6, D2, B0, D7, A12, A13, B17, B16, D0, B1, C2, D6 }
#define MATRIX_COL_PINS { B3, D1, C0, D5, C1, B2, D4 }

#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

#define IGNORE_MOD_TAP_INTERRUPT

// Reduce input latency by lowering the USB polling interval
// from its 10ms default to the 1ms minimum that USB 1.x (Full Speed) allows:
#define USB_POLLING_INTERVAL_MS 1

#define LED_PIN_ON_STATE 0
#define LED_NUM_LOCK_PIN A14
#define LED_CAPS_LOCK_PIN C7
#define LED_SCROLL_LOCK_PIN A5
#define LED_COMPOSE_PIN E26
