/*
Copyright 2021 Suavity Designs <henry@suavity.cc>

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
#define VENDOR_ID       0x5344 // 5344 short for "SD" (Suavity Designs)
#define PRODUCT_ID      0x4548 // 4548 short for "EH" (EHan)
#define DEVICE_VER      0x0001
#define MANUFACTURER    Suavity Designs
#define PRODUCT         ehan

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 17

#define MATRIX_COL_PINS { A10, A9, A8, B15, B14, B13, B12, C14, B7, B6, B5,  B4,  B3,  A15, C13, B9, B8 }
// Matrix Column Pins:     C0  C1  C2   C3   C4   C5   C6   C7  C8  C9  C10  C11  C12  C13  C14  C15  C16
#define MATRIX_ROW_PINS { A7, B0, A3, A4, A5, A6 }
// Matrix Row Pins:       R0  R1  R2  R3  R4  R5
#define DIODE_DIRECTION COL2ROW
// Current flow out of the diodes are from rows to columns

#define LED_CAPS_LOCK_PIN B11 // LED for Step Caps
#define LED_SCROLL_LOCK_PIN F1 // LED Indicator for Scroll Lock
#define LED_PIN_ON_STATE 1

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

