/* Copyright 2021 JasonRen(biu)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once
#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID 0xAA96
#define PRODUCT_ID 0xAA02
#define DEVICE_VER 0x0001
#define MANUFACTURER    Jason Ren and Student WTF
#define PRODUCT         SB65P

/* key matrix size */
#define MATRIX_ROWS 10
#define MATRIX_COLS 9

/* key matrix pins */
#define MATRIX_ROW_PINS { B0, B1, B2, B3, B4, B5, B6, B7, C0, C1 }
#define MATRIX_COL_PINS { C2, C3, C4, C5, C6, C7, D0, D1, D2 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* number of backlight levels */


/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#define ONESHOT_TIMEOUT 500

/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)


//UART settings for communication with the RF microcontroller
#define SERIAL_UART_BAUD 1000000
#define SERIAL_UART_DATA UDR1
#define SERIAL_UART_UBRR (F_CPU / (16UL * SERIAL_UART_BAUD) - 1)
#define SERIAL_UART_TXD_READY (UCSR1A & _BV(UDRE1))
#define SERIAL_UART_RXD_PRESENT (UCSR1A & _BV(RXC1))
#define SERIAL_UART_INIT() do { \
    	/* baud rate */ \
    	UBRR1L = SERIAL_UART_UBRR; \
    	/* baud rate */ \
    	UBRR1H = SERIAL_UART_UBRR >> 8; \
    	/* enable TX and RX */ \
    	UCSR1B = _BV(TXEN1) | _BV(RXEN1); \
    	/* 8-bit data */ \
    	UCSR1C = _BV(UCSZ11) | _BV(UCSZ10); \
  	} while(0)


