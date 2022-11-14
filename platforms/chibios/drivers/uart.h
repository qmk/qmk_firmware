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

#ifndef SD_TX_PIN
#    define SD_TX_PIN A9
#endif

#ifndef SD_RX_PIN
#    define SD_RX_PIN A10
#endif

//CTS currently not implemented
#ifndef SD_CTS_PIN
#    define SD_CTS_PIN A11
#endif

//RTS currently not implemented
#ifndef SD_RTS_PIN
#    define SD_RTS_PIN A12
#endif

#if !defined(USE_GPIOV1)
#    ifndef SD_TX_PAL_MODE
#        define SD_TX_PAL_MODE 7
#    endif

#    ifndef SD_RX_PAL_MODE
#        define SD_RX_PAL_MODE 7
#    endif

#    ifndef SD_CTS_PAL_MODE
#        define SD_CTS_PAL_MODE 7
#    endif

#    ifndef SD_RTS_PAL_MODE
#        define SD_RTS_PAL_MODE 7
#    endif
#endif

#ifndef SD_CR1
#    define SD_CR1 0
#endif

#ifndef SD_CR2
#    define SD_CR2 0
#endif

#ifndef SD_CR3
#    define SD_CR3 0
#endif

#ifndef SD_WRDLEN
#    define SD_WRDLEN 3
#endif

#ifndef SD_STPBIT
#    define SD_STPBIT 0
#endif

#ifndef SD_PARITY
#    define SD_PARITY 0
#endif

#ifndef SD_ATFLCT
#    define SD_ATFLCT 0
#endif

void uart_init(uint32_t baud);

void uart_write(uint8_t data);

uint8_t uart_read(void);

void uart_transmit(const uint8_t *data, uint16_t length);

void uart_receive(uint8_t *data, uint16_t length);

bool uart_available(void);
