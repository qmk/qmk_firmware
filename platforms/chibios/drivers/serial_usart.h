/* Copyright 2021 QMK
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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

#include "quantum.h"
#include "serial.h"
#include "printf.h"

#include <ch.h>
#include <hal.h>

#if !defined(SERIAL_USART_DRIVER)
#    define SERIAL_USART_DRIVER SD1
#endif

#if !defined(USE_GPIOV1)
/* The default PAL alternate modes are used to signal that the pins are used for USART. */
#    if !defined(SERIAL_USART_TX_PAL_MODE)
#        define SERIAL_USART_TX_PAL_MODE 7
#    endif
#    if !defined(SERIAL_USART_RX_PAL_MODE)
#        define SERIAL_USART_RX_PAL_MODE 7
#    endif
#endif

#if defined(SOFT_SERIAL_PIN)
#    define SERIAL_USART_TX_PIN SOFT_SERIAL_PIN
#endif

#if !defined(SERIAL_USART_TX_PIN)
#    define SERIAL_USART_TX_PIN A9
#endif

#if !defined(SERIAL_USART_RX_PIN)
#    define SERIAL_USART_RX_PIN A10
#endif

#if !defined(USART_CR1_M0)
#    define USART_CR1_M0 USART_CR1_M // some platforms (f1xx) dont have this so
#endif

#if !defined(SERIAL_USART_CR1)
#    define SERIAL_USART_CR1 (USART_CR1_PCE | USART_CR1_PS | USART_CR1_M0) // parity enable, odd parity, 9 bit length
#endif

#if !defined(SERIAL_USART_CR2)
#    define SERIAL_USART_CR2 (USART_CR2_STOP_1) // 2 stop bits
#endif

#if !defined(SERIAL_USART_CR3)
#    define SERIAL_USART_CR3 0
#endif

#if defined(USART1_REMAP)
#    define USART_REMAP                             \
        do {                                        \
            (AFIO->MAPR |= AFIO_MAPR_USART1_REMAP); \
        } while (0)
#elif defined(USART2_REMAP)
#    define USART_REMAP                             \
        do {                                        \
            (AFIO->MAPR |= AFIO_MAPR_USART2_REMAP); \
        } while (0)
#elif defined(USART3_PARTIALREMAP)
#    define USART_REMAP                                          \
        do {                                                     \
            (AFIO->MAPR |= AFIO_MAPR_USART3_REMAP_PARTIALREMAP); \
        } while (0)
#elif defined(USART3_FULLREMAP)
#    define USART_REMAP                                       \
        do {                                                  \
            (AFIO->MAPR |= AFIO_MAPR_USART3_REMAP_FULLREMAP); \
        } while (0)
#endif

#if !defined(SELECT_SOFT_SERIAL_SPEED)
#    define SELECT_SOFT_SERIAL_SPEED 1
#endif

#if defined(SERIAL_USART_SPEED)
// Allow advanced users to directly set SERIAL_USART_SPEED
#elif SELECT_SOFT_SERIAL_SPEED == 0
#    define SERIAL_USART_SPEED 460800
#elif SELECT_SOFT_SERIAL_SPEED == 1
#    define SERIAL_USART_SPEED 230400
#elif SELECT_SOFT_SERIAL_SPEED == 2
#    define SERIAL_USART_SPEED 115200
#elif SELECT_SOFT_SERIAL_SPEED == 3
#    define SERIAL_USART_SPEED 57600
#elif SELECT_SOFT_SERIAL_SPEED == 4
#    define SERIAL_USART_SPEED 38400
#elif SELECT_SOFT_SERIAL_SPEED == 5
#    define SERIAL_USART_SPEED 19200
#else
#    error invalid SELECT_SOFT_SERIAL_SPEED value
#endif

#if !defined(SERIAL_USART_TIMEOUT)
#    define SERIAL_USART_TIMEOUT 20
#endif

#define HANDSHAKE_MAGIC 7
