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

#ifdef SD1_BANK
#    define SD1_TX_BANK SD1_BANK
#    define SD1_RX_BANK SD1_BANK
#endif

#ifndef SD1_TX_BANK
#    define SD1_TX_BANK GPIOA
#endif

#ifndef SD1_RX_BANK
#    define SD1_RX_BANK GPIOA
#endif

#ifndef SD1_TX
#    define SD1_TX 9
#endif
#ifndef SD1_RX
#    define SD1_RX 10
#endif

#ifndef SERIAL_DRIVER
#    define SERIAL_DRIVER SD1
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

#ifdef USE_GPIOV1
#    ifndef SD1_TX_PAL_MODE
#        define SD1_TX_PAL_MODE PAL_MODE_STM32_ALTERNATE_OPENDRAIN
#    endif
#    ifndef SD1_RX_PAL_MODE
#        define SD1_RX_PAL_MODE PAL_MODE_STM32_ALTERNATE_OPENDRAIN
#    endif
#else
// The default PAL alternate modes are used to signal that the pins are used for USART
#    ifndef SD1_TX_PAL_MODE
#        define SD1_TX_PAL_MODE 7
#    endif
#    ifndef SD1_RX_PAL_MODE
#        define SD1_RX_PAL_MODE 7
#    endif
#endif

void uart_init(uint32_t baud);

void uart_putchar(uint8_t c);

uint8_t uart_getchar(void);

uint8_t uart_available(void);
