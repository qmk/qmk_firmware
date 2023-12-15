// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>

/**
 * \file
 *
 * \defgroup raw_hid Raw HID API
 * \{
 */

/**
 * \brief Callback, invoked when a raw HID report has been received from the host.
 *
 * \param data A pointer to the received data. Always 32 bytes in length.
 * \param length The length of the buffer. Always 32.
 */
void raw_hid_receive(uint8_t *data, uint8_t length);

/**
 * \brief Send an HID report.
 *
 * \param data A pointer to the data to send. Must always be 32 bytes in length.
 * \param length The length of the buffer. Must always be 32.
 */
void raw_hid_send(uint8_t *data, uint8_t length);

/** \} */
