/*
Copyright 2020 Tvrd Rad Keyboards

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
#define VENDOR_ID    0x5452  // "TR"
#define PRODUCT_ID   0x0001  // TRK1
#define DEVICE_VER   0x0001  // v1.0
#define MANUFACTURER Tvrd Rad Keyboards
#define PRODUCT      Tvrd Rad Keyboards TRK1

/* Key matrix */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15
#define MATRIX_ROW_PINS { F5, F4, F1, F0, B7 }
#define MATRIX_COL_PINS { B3, B2, D2, D3, C6, C7, D5, F6, F7, B6, B5, B4, D7, D6, D4 }
#define ENCODERS_PAD_A { B1 }
#define ENCODERS_PAD_B { B0 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5
#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE

/* Keyboard reports */
#define FORCE_NKRO
#define USB_POLLING_INTERVAL_MS 1

/* Tapping */
#define PERMISSIVE_HOLD
#define TAPPING_TERM   200
#define TAPPING_TOGGLE 2

/* Firmware size reductions */
#undef  LOCKING_SUPPORT_ENABLE
#define NO_ACTION_FUNCTION
#define NO_ACTION_MACRO
#define NO_ACTION_ONESHOT
