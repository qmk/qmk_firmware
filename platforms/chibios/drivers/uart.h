// Copyright 2024 Stefan Kerkmann
// Copyright 2021 QMK
// Copyright 2024 Stefan Kerkmann
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>
#include <stdbool.h>

#include <hal.h>

#include "gpio.h"
#include "chibios_config.h"

// ======== DEPRECATED DEFINES - DO NOT USE ========
#ifdef SERIAL_DRIVER
#    define UART_DRIVER SERIAL_DRIVER
#endif
#ifdef SD1_TX_PIN
#    define UART_TX_PIN SD1_TX_PIN
#endif
#ifdef SD1_RX_PIN
#    define UART_RX_PIN SD1_RX_PIN
#endif
#ifdef SD1_CTS_PIN
#    define UART_CTS_PIN SD1_CTS_PIN
#endif
#ifdef SD1_RTS_PIN
#    define UART_RTS_PIN SD1_RTS_PIN
#endif
#ifdef SD1_TX_PAL_MODE
#    define UART_TX_PAL_MODE SD1_TX_PAL_MODE
#endif
#ifdef SD1_RX_PAL_MODE
#    define UART_RX_PAL_MODE SD1_RX_PAL_MODE
#endif
#ifdef SD1_CTS_PAL_MODE
#    define UART_RTS_PAL_MODE SD1_CTS_PAL_MODE
#endif
#ifdef SD1_RTS_PAL_MODE
#    define UART_TX_PAL_MODE SD1_RTS_PAL_MODE
#endif
#ifdef SD1_CR1
#    define UART_CR1 SD1_CR1
#endif
#ifdef SD1_CR2
#    define UART_CR2 SD1_CR2
#endif
#ifdef SD1_CR3
#    define UART_CR3 SD1_CR3
#endif
#ifdef SD1_WRDLEN
#    define UART_WRDLEN SD1_WRDLEN
#endif
#ifdef SD1_STPBIT
#    define UART_STPBIT SD1_STPBIT
#endif
#ifdef SD1_PARITY
#    define UART_PARITY SD1_PARITY
#endif
#ifdef SD1_ATFLCT
#    define UART_ATFLCT SD1_ATFLCT
#endif
// ========

#ifndef UART_DRIVER
#    if (HAL_USE_SERIAL == TRUE)
#        define UART_DRIVER SD1
#    elif (HAL_USE_SIO == TRUE)
#        define UART_DRIVER SIOD1
#    endif
#endif

#ifndef UART_TX_PIN
#    define UART_TX_PIN A9
#endif

#ifndef UART_RX_PIN
#    define UART_RX_PIN A10
#endif

#ifndef UART_CTS_PIN
#    define UART_CTS_PIN A11
#endif

#ifndef UART_RTS_PIN
#    define UART_RTS_PIN A12
#endif

#ifdef USE_GPIOV1
#    ifndef UART_TX_PAL_MODE
#        define UART_TX_PAL_MODE PAL_MODE_ALTERNATE_PUSHPULL
#    endif
#    ifndef UART_RX_PAL_MODE
#        define UART_RX_PAL_MODE PAL_MODE_INPUT
#    endif
#    ifndef UART_CTS_PAL_MODE
#        define UART_CTS_PAL_MODE PAL_MODE_INPUT
#    endif
#    ifndef UART_RTS_PAL_MODE
#        define UART_RTS_PAL_MODE PAL_MODE_ALTERNATE_PUSHPULL
#    endif
#else
#    ifndef UART_TX_PAL_MODE
#        define UART_TX_PAL_MODE 7
#    endif

#    ifndef UART_RX_PAL_MODE
#        define UART_RX_PAL_MODE 7
#    endif

#    ifndef UART_CTS_PAL_MODE
#        define UART_CTS_PAL_MODE 7
#    endif

#    ifndef UART_RTS_PAL_MODE
#        define UART_RTS_PAL_MODE 7
#    endif
#endif

#ifndef UART_CR1
#    define UART_CR1 0
#endif

#ifndef UART_CR2
#    define UART_CR2 0
#endif

#ifndef UART_CR3
#    define UART_CR3 0
#endif

#ifndef UART_WRDLEN
#    define UART_WRDLEN 3
#endif

#ifndef UART_STPBIT
#    define UART_STPBIT 0
#endif

#ifndef UART_PARITY
#    define UART_PARITY 0
#endif

#ifndef UART_ATFLCT
#    define UART_ATFLCT 0
#endif

/**
 * @brief Initialize the UART driver. This function must be called only once,
 * before any of the below functions can be called.
 *
 * @param baud The baud rate to transmit and receive at. This may depend on the
 * device you are communicating with. Common values are 1200, 2400, 4800, 9600,
 * 19200, 38400, 57600, and 115200.
 */
void uart_init(uint32_t baud);

/**
 * @brief Transmit a single byte.
 *
 * @param data The byte to transmit.
 */
void uart_write(uint8_t data);

/**
 * @brief Receive a single byte.
 *
 * @return uint8_t The byte read from the receive buffer. This function will
 * block if the buffer is empty (ie. no data to read).
 */
uint8_t uart_read(void);

/**
 * @brief Transmit multiple bytes.
 *
 * @param data A pointer to the data to write from.
 * @param length The number of bytes to write. Take care not to overrun the
 * length of `data`.
 */
void uart_transmit(const uint8_t *data, uint16_t length);

/**
 * @brief Receive multiple bytes.
 *
 * @param data A pointer to the buffer to read into.
 * @param length The number of bytes to read. Take care not to overrun the
 * length of `data`.
 */
void uart_receive(uint8_t *data, uint16_t length);

/**
 * @brief Return whether the receive buffer contains data. Call this function
 * to determine if `uart_read()` will return data immediately.
 *
 * @return true If there is data available to read.
 * @return false If there is no data available to read.
 */
bool uart_available(void);
