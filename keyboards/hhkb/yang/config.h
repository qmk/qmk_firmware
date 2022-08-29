/*
Copyright 2020 Kan-Ru Chen <kanru@kanru.info>
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
#define VENDOR_ID 0x4848   // HH = happy hacking
#define PRODUCT_ID 0x0001  // ANSI HHKB
#define DEVICE_VER 0x0104
#define MANUFACTURER YANG
#define PRODUCT HHKB BLE Keyboard

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 8

/* matrix power saving */
#define MATRIX_POWER_SAVE_TIMEOUT_MS 10000
#define MATRIX_POWER_SAVE_TIMEOUT_L2_MS 1800000
#define MATRIX_POWER_SAVE_TIMEOUT_L3_MS 7200000

#define LED_CAPS_LOCK_PIN F4

#ifdef BLUETOOTH_ENABLE
#    define OUTPUT_DEFAULT OUTPUT_AUTO

#    undef SERIAL_UART_BAUD
#    undef SERIAL_UART_DATA
#    undef SERIAL_UART_UBRR
#    undef SERIAL_UART_RXD_VECT
#    undef SERIAL_UART_TXD_READY
#    undef SERIAL_UART_INIT

#    define SERIAL_UART_BAUD 76800
#    define SERIAL_UART_DATA UDR1
#    define SERIAL_UART_UBRR (F_CPU / (8UL * SERIAL_UART_BAUD) - 1)
#    define SERIAL_UART_RXD_VECT USART1_RX_vect
#    define SERIAL_UART_TXD_READY (UCSR1A & _BV(UDRE1))
#    define SERIAL_UART_INIT()                        \
        do {                                          \
            cli();                                    \
            /* baud rate */                           \
            UBRR1L = SERIAL_UART_UBRR;                \
            /* baud rate */                           \
            UBRR1H = SERIAL_UART_UBRR >> 8;           \
            /* enable TX */                           \
            UCSR1B |= (0 << TXCIE1) | (1 << TXEN1);   \
            /* enable RX */                           \
            UCSR1B |= (1 << RXCIE1) | (1 << RXEN1);   \
            /* parity: none(00), even(01), odd(11) */ \
            UCSR1C |= (0 << UPM11) | (0 << UPM10);    \
            /* 2x speed (error = 0.2%) */             \
            UCSR1A |= (1 << U2X1);                    \
            sei();                                    \
        } while (0)
#endif

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
//#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
//#define LOCKING_RESYNC_ENABLE

/* If defined, GRAVE_ESC will always act as ESC when CTRL is held.
 * This is useful for the Windows task manager shortcut (ctrl+shift+esc).
 */
//#define GRAVE_ESC_CTRL_OVERRIDE

/*
 * Force NKRO
 *
 * Force NKRO (nKey Rollover) to be enabled by default, regardless of the saved
 * state in the bootmagic EEPROM settings. (Note that NKRO must be enabled in the
 * makefile for this to work.)
 *
 * If forced on, NKRO can be disabled via magic key (default = LShift+RShift+N)
 * until the next keyboard reset.
 *
 * NKRO may prevent your keystrokes from being detected in the BIOS, but it is
 * fully operational during normal computer usage.
 *
 * For a less heavy-handed approach, enable NKRO via magic key (LShift+RShift+N)
 * or via bootmagic (hold SPACE+N while plugging in the keyboard). Once set by
 * bootmagic, NKRO mode will always be enabled until it is toggled again during a
 * power-up.
 *
 */
//#define FORCE_NKRO

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


/* Bootmagic Lite key configuration */
//#define BOOTMAGIC_LITE_ROW 0
//#define BOOTMAGIC_LITE_COLUMN 0

//#define DEBUG_MATRIX_SCAN_RATE

// Disable debounce
#define DEBOUNCE 0
