/*
Copyright 2021 Charue Design

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
#define VENDOR_ID    0x4344 // CD for CharueDesign
#define PRODUCT_ID   0x4348 // CH for Charon
#define DEVICE_VER   0x0001 // Revision prototype
#define MANUFACTURER Charue Design
#define PRODUCT      Charon

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

/* Keyboard Matrix Assignments */
#define MATRIX_ROW_PINS { B0, B1, B2, B3, C7 }
#define MATRIX_COL_PINS { D3, D5, B4, D7, D6, D4, F7, F6, F5, F4, F1, F0, B5, B6, C6 }
#define UNUSED_PINS { B7, D0, D1, D2 }
#define DIODE_DIRECTION COL2ROW

/* LED config */
#define LED_CAPS_LOCK_PIN E6

/* Set 0 if debouncing is not needed */
#define DEBOUNCE 5
