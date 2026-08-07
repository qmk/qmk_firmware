// Copyright 2022 Stefan Kerkmann
// SPDX-License-Identifier: GPL-2.0-or-later

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#pragma once

/**
 * @brief Clears any intermediate sending or receiving state of the driver to a known good
 * state. This happens after errors in the middle of transactions, to start with
 * a clean slate.
 */
void serial_transport_driver_clear(void);

/**
 * @brief Driver specific initialization on the slave half.
 */
void serial_transport_driver_slave_init(void);

/**
 * @brief Driver specific specific initialization on the master half.
 */
void serial_transport_driver_master_init(void);

/**
 * @brief  Blocking receive of size * bytes.
 *
 * @return true Receive success.
 * @return false Receive failed, e.g. by bit errors.
 */
bool __attribute__((nonnull, hot)) serial_transport_receive(uint8_t* destination, const size_t size);

/**
 * @brief Blocking receive of size * bytes with an implicitly defined timeout.
 *
 * @return true Receive success.
 * @return false Receive failed, e.g. by timeout or bit errors.
 */
bool __attribute__((nonnull, hot)) serial_transport_receive_blocking(uint8_t* destination, const size_t size);

/**
 * @brief Blocking send of buffer with timeout.
 *
 * @return true Send success.
 * @return false Send failed, e.g. by timeout or bit errors.
 */
bool __attribute__((nonnull, hot)) serial_transport_send(const uint8_t* source, const size_t size);
