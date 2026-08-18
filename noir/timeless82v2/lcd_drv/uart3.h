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

#ifndef SERIAL3_DRIVER
#    define SERIAL3_DRIVER SD3
#endif

#ifndef SD3_TX_PIN
#    define SD3_TX_PIN C10
#endif

#ifndef SD3_RX_PIN
#    define SD3_RX_PIN C11
#endif

#ifndef SD3_CTS_PIN
#    define SD3_CTS_PIN A11
#endif

#ifndef SD3_RTS_PIN
#    define SD3_RTS_PIN A12
#endif

#ifdef USE_GPIOV1
#    ifndef SD3_TX_PAL_MODE
#        define SD3_TX_PAL_MODE PAL_MODE_ALTERNATE_PUSHPULL
#    endif
#    ifndef SD3_RX_PAL_MODE
#        define SD3_RX_PAL_MODE PAL_MODE_INPUT
#    endif
#    ifndef SD3_CTS_PAL_MODE
#        define SD3_CTS_PAL_MODE PAL_MODE_INPUT
#    endif
#    ifndef SD3_RTS_PAL_MODE
#        define SD3_RTS_PAL_MODE PAL_MODE_ALTERNATE_PUSHPULL
#    endif
#else
#    ifndef SD3_TX_PAL_MODE
#        define SD3_TX_PAL_MODE 7
#    endif

#    ifndef SD3_RX_PAL_MODE
#        define SD3_RX_PAL_MODE 7
#    endif

#    ifndef SD3_CTS_PAL_MODE
#        define SD3_CTS_PAL_MODE 7
#    endif

#    ifndef SD3_RTS_PAL_MODE
#        define SD3_RTS_PAL_MODE 7
#    endif
#endif

#ifndef SD3_CR1
#    define SD3_CR1 0
#endif

#ifndef SD3_CR2
#    define SD3_CR2 0
#endif

#ifndef SD3_CR3
#    define SD3_CR3 0
#endif

#ifndef SD3_WRDLEN
#    define SD3_WRDLEN 3
#endif

#ifndef SD3_STPBIT
#    define SD3_STPBIT 0
#endif

#ifndef SD3_PARITY
#    define SD3_PARITY 0
#endif

#ifndef SD3_ATFLCT
#    define SD3_ATFLCT 0
#endif

void uart3_init(uint32_t baud);

void uart3_write(uint8_t data);

uint8_t uart3_read(void);

void uart3_transmit(const uint8_t *data, uint16_t length);

void uart3_receive(uint8_t *data, uint16_t length);

bool uart3_available(void);
