/*
Copyright 2022 Automata

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

/* USB Device descriptor parameter */
#define usb.vid                 0xFEED
#define usb.pid                 0x2012
#define usb.device_version      0x0001
#define manufacturer            Automata
#define keyboard_name           Alisaie

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 14

// ROWS: Top to bottom, COLS: Left to right

#define MATRIX_ROW_PINS { E6, F6, D5, D4, B1 }
#define MATRIX_COL_PINS { B6, F0, F1, F4, F5, B5, B7, D3, D2, D1, D0, B3, B2, B0 }

#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE 
