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


/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define IGNORE_MOD_TAP_INTERRUPT

// The Teensy 3.6 consumes about 80 mA of current at its full speed of 180 MHz:
// https://forum.pjrc.com/threads/47256-What-is-the-power-consumption-of-the-Teensy-3-6
#define USB_MAX_POWER_CONSUMPTION 100

#define EEPROM_SIZE 4096
