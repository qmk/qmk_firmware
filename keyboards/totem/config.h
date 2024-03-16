/*
Copyright 2022 GEIST <@geigeigeist>

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

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 8
#define MATRIX_COLS 5


// wiring of each half
#define MATRIX_ROW_PINS { GP26, GP27, GP28, GP29 }
#define MATRIX_COL_PINS { GP6, GP7, GP3, GP4, GP2 }
#define DIODE_DIRECTION COL2ROW


//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION

#define DEBOUNCE 5


/* Serial settings */
#define USE_SERIAL
/* serial.c configuration for split keyboard */
#define SOFT_SERIAL_PIN GP0
//#define SPLIT_LAYER_STATE_ENABLE
//#define SPLIT_USB_DETECT
#define SERIAL_USE_MULTI_TRANSACTION
/* communication between sides */
#define SERIAL_PIO_USE_PIO1


#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U