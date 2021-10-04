/*
Copyright 2021 Moritz Plattner
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
#define VENDOR_ID       0x4C58      //"LX"
#define PRODUCT_ID      0x0003
#define DEVICE_VER      0x0001
#define MANUFACTURER    Lx3
#define PRODUCT         ORCA

/* Set 1 kHz polling rate and force USB NKRO */
#define USB_POLLING_INTERVAL_MS 1
#define FORCE_NKRO

/* key matrix size */
#define MATRIX_ROWS 10
#define MATRIX_COLS 7

#define MATRIX_ROW_PINS { C6, B6, C7, B5, F6, D6, F1, D5, D2, B0 }
#define MATRIX_COL_PINS { B4, D7, F0, D1, F7, F4, F5 }
#define UNUSED_PINS { B6, C6, C7 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Indicator LEDs */
#define LED_CAPS_LOCK_PIN D4
#define LED_PIN_ON_STATE 0