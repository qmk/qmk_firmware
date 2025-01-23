// Copyright 2024 Stefan Kerkmann
// Copyright 2021 QMK
// Copyright 2024 Stefan Kerkmann
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>
#include <stdbool.h>

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
