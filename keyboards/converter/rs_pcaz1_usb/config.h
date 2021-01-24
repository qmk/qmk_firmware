/*
Copyright 2021 Kamel Makhloufi <melkalehun@gmail.com>

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

#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x3333
#define DEVICE_VER      0x0100
#define MANUFACTURER    QMK
#define PRODUCT         Rohde & Schwarz PCA-Z1 converter

/* matrix size */
#define MATRIX_ROWS 12
#define MATRIX_COLS 8

/* Modifier to use for Ctrl+key combinations */
#define CTRL_MOD KC_LCTRL

/* Serial(USART) configuration
 *     asynchronous, negative logic, 9600baud, no flow control
 *     1-start bit, 8-data bit, non parity, 1-stop bit
 */
#define SERIAL_SOFT_BAUD            2400
#define SERIAL_SOFT_PARITY_NONE
#define SERIAL_SOFT_BIT_ORDER_LSB
/* RXD Port */
#define SERIAL_SOFT_RXD_ENABLE

// we are using Pro micro pin 3 / D0 as serial
#define SERIAL_SOFT_RXD_DDR         DDRD
#define SERIAL_SOFT_RXD_PORT        PORTD
#define SERIAL_SOFT_RXD_PIN         PIND
#define SERIAL_SOFT_RXD_BIT         0
#define SERIAL_SOFT_RXD_VECT        INT0_vect

/* RXD Interupt */
#define SERIAL_SOFT_RXD_INIT()      do { \
    /* pin configuration: input with pull-up */ \
    SERIAL_SOFT_RXD_DDR &= ~(1<<SERIAL_SOFT_RXD_BIT); \
    SERIAL_SOFT_RXD_PORT |= (1<<SERIAL_SOFT_RXD_BIT); \
    /* enable interrupt: INT0(falling edge) */ \
    EICRA &= ~(_BV(ISC00) | _BV(ISC01)); \
    EIMSK |= _BV(INT0); \
    sei(); \
} while (0)

#define SERIAL_SOFT_RXD_INT_ENTER()
#define SERIAL_SOFT_RXD_INT_EXIT()  do { \
    /* clear interrupt  flag */ \
    EIFR = (1<<INTF0); \
} while (0)
#define SERIAL_SOFT_RXD_READ()      (SERIAL_SOFT_RXD_PIN&(1<<SERIAL_SOFT_RXD_BIT))

/* TXD Port */
#define SERIAL_SOFT_TXD_HI()        do { } while (0)
#define SERIAL_SOFT_TXD_LO()        do { } while (0)
#define SERIAL_SOFT_TXD_INIT()      do { } while (0)
