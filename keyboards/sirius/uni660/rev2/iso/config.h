/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

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
#define VENDOR_ID    0x5352 // "SR"
#define PRODUCT_ID   0x0203 // Second Product Third Version
#define DEVICE_VER   0x2004 // 2020.12
#define MANUFACTURER SiRius
#define PRODUCT      Uni660 V2

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 16

#define ONESHOT_TIMEOUT 500

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
//#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
//#define LOCKING_RESYNC_ENABLE

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

/* disable these deprecated features by default */
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

//UART settings for communication with the RF microcontroller
#define SERIAL_UART_BAUD 1000000
#define SERIAL_UART_RXD_PRESENT (UCSR1A & _BV(RXC1))
#define SERIAL_UART_INIT_CUSTOM       \
    /* enable TX and RX */            \
    UCSR1B = _BV(TXEN1) | _BV(RXEN1); \
    /* 8-bit data */                  \
    UCSR1C = _BV(UCSZ11) | _BV(UCSZ10);

#define DYNAMIC_KEYMAP_LAYER_COUNT 4
