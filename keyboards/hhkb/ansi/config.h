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
#define VENDOR_ID       0x4848 // HH = happy hacking
#define PRODUCT_ID      0x0001 // ANSI HHKB
#define DEVICE_VER      0x0104
#define MANUFACTURER    q.m.k
#define PRODUCT         HHKB mod

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 8

#define TAPPING_TERM    200

/* number of backlight levels */
#define BACKLIGHT_LEVELS 3

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
//#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
//#define LOCKING_RESYNC_ENABLE

#ifdef HHKB_RN42_ENABLE
// rn42 support -- acquired from the tmk repo. This is almost certainly not
// integrated with qmk in the correct way.

#define SUART_OUT_PORT  PORTD
#define SUART_OUT_BIT   0
#define SUART_IN_PIN    PIND
#define SUART_IN_BIT    1

#define SERIAL_UART_BAUD 115200
#define SERIAL_UART_INIT_CUSTOM                 \
    /* RX interrupt, RX: enable */              \
    UCSR1B |= (1<<RXCIE1) | (1<<RXEN1);         \
    /* TX interrupt, TX: enable */              \
    UCSR1B |= (0<<TXCIE1) | (1<<TXEN1);         \
    /* parity: none(00), even(01), odd(11) */   \
    UCSR1C |= (0<<UPM11) | (0<<UPM10);          \
    /* RTS, CTS(no flow control by hardware) */ \
    UCSR1D |= (0<<RTSEN) | (0<<CTSEN);          \
    /* RTS for flow control by firmware */      \
    DDRD |= (1<<5); PORTD &= ~(1<<5);
#define SERIAL_UART_RTS_LO() do { PORTD &= ~(1<<5); } while (0)
#define SERIAL_UART_RTS_HI() do { PORTD |=  (1<<5); } while (0)

/* power control of key switch board */
#define HHKB_POWER_SAVING

#endif

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
