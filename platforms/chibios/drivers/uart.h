/* Copyright 2021
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include <stdint.h>

#include <hal.h>

#ifndef SERIAL_DRIVER
#    define SERIAL_DRIVER SD1
#endif

#ifndef SD1_TX_PIN
#    define SD1_TX_PIN A9
#endif

#ifndef SD1_RX_PIN
#    define SD1_RX_PIN A10
#endif

#ifndef SD1_CTS_PIN
#    define SD1_CTS_PIN A11
#endif

#ifndef SD1_RTS_PIN
#    define SD1_RTS_PIN A12
#endif

#ifdef USE_GPIOV1
#    ifndef SD1_TX_PAL_MODE
#        define SD1_TX_PAL_MODE PAL_MODE_ALTERNATE_OPENDRAIN
#    endif

#    ifndef SD1_RX_PAL_MODE
#        define SD1_RX_PAL_MODE PAL_MODE_ALTERNATE_OPENDRAIN
#    endif

#    ifndef SD1_CTS_PAL_MODE
#        define SD1_CTS_PAL_MODE PAL_MODE_ALTERNATE_OPENDRAIN
#    endif

#    ifndef SD1_RTS_PAL_MODE
#        define SD1_RTS_PAL_MODE PAL_MODE_ALTERNATE_OPENDRAIN
#    endif
#else
#    ifndef SD1_TX_PAL_MODE
#        define SD1_TX_PAL_MODE 7
#    endif

#    ifndef SD1_RX_PAL_MODE
#        define SD1_RX_PAL_MODE 7
#    endif

#    ifndef SD1_CTS_PAL_MODE
#        define SD1_CTS_PAL_MODE 7
#    endif

#    ifndef SD1_RTS_PAL_MODE
#        define SD1_RTS_PAL_MODE 7
#    endif
#endif

#ifndef SD1_CR1
#    define SD1_CR1 0
#endif

#ifndef SD1_CR2
#    define SD1_CR2 0
#endif

#ifndef SD1_CR3
#    define SD1_CR3 0
#endif

#ifndef SD1_WRDLEN
#    define SD1_WRDLEN 3
#endif

#ifndef SD1_STPBIT
#    define SD1_STPBIT 0
#endif

#ifndef SD1_PARITY
#    define SD1_PARITY 0
#endif

#ifndef SD1_ATFLCT
#    define SD1_ATFLCT 0
#endif

void uart_init(uint32_t baud);

void uart_write(uint8_t data);

uint8_t uart_read(void);

void uart_transmit(const uint8_t *data, uint16_t length);

void uart_receive(uint8_t *data, uint16_t length);

bool uart_available(void);
