// Copyright 2021 Christian Eiden, cykedev
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#pragma once

#undef SOFT_SERIAL_PIN
#undef DIODE_DIRECTION
#undef MATRIX_ROW_PINS
#undef MATRIX_COL_PINS
#undef BOOTMAGIC_LITE_ROW
#undef BOOTMAGIC_LITE_COLUMN
#undef BOOTMAGIC_LITE_ROW_RIGHT
#undef BOOTMAGIC_LITE_COLUMN_RIGHT


#define SOFT_SERIAL_PIN D2
#define EE_HANDS
// #define SPLIT_USB_DETECT

// wiring of each half
// ../../../../docs/proton_c_conversion.md
#define MATRIX_ROW_PINS { B6, B2, B3, B1, F7, F6, F5 }
#define MATRIX_COL_PINS { B5, B4, E6, D7, C6, D4 }

#define DIODE_DIRECTION ROW2COL

#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0

#define BOOTMAGIC_LITE_ROW_RIGHT 0
#define BOOTMAGIC_LITE_COLUMN_RIGHT 5

// Configure the global tapping term (default: 200ms)
#define TAPPING_TERM 200

#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define QUICK_TAP_TERM 0

#define FORCE_NKRO
