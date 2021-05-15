/*
Copyright 2021 Sleepdealer

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
#define VENDOR_ID    0x4646 // FF
#define PRODUCT_ID   0x0001
#define DEVICE_VER   0x0001
#define MANUFACTURER FootFingers
#define PRODUCT      puca

#define MATRIX_ROWS 6
#define MATRIX_COLS 5
                    //    0 , 1 , 2 , 3 , 4 , 5
#define MATRIX_ROW_PINS { B4, E6, D7, B5, C6, F6}
#define MATRIX_COL_PINS { F7, B1, B3, B2, B6}

#define DIODE_DIRECTION COL2ROW

#define BACKLIGHT_PIN D4
#define BACKLIGHT_LEVELS 3
#define BACKLIGHT_BREATHING

#define ENCODERS_PAD_A { F4 }
#define ENCODERS_PAD_B { F5 }

#define MY_I2C_ADDRESS (0X3C << 1)

#define VIAL_KEYBOARD_UID {0x8C, 0x1C, 0xE2, 0xA0, 0xB6, 0x21, 0x58, 0x67} // Vial unique ID

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* disable these deprecated features by default */
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
