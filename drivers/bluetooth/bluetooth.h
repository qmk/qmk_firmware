/*
 * Copyright 2022
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
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

#include <stdint.h>
#include <stdbool.h>
#include "report.h"

/**
 * \brief Initialize the Bluetooth system.
 */
void bluetooth_init(void);

/**
 * \brief Perform housekeeping tasks.
 */
void bluetooth_task(void);

/**
 * \brief Detects if Bluetooth is connected.
 *
 * \return `true` if connected, `false` otherwise.
 */
bool bluetooth_is_connected(void);

/**
 * \brief Detects if `bluetooth_send_nkro` should be used over `bluetooth_send_keyboard`.
 */
bool bluetooth_can_send_nkro(void);

/**
 * \brief Get current LED state.
 */
uint8_t bluetooth_keyboard_leds(void);

/**
 * \brief Send a keyboard report.
 *
 * \param report The keyboard report to send.
 */
void bluetooth_send_keyboard(report_keyboard_t *report);

/**
 * \brief Send a nkro report.
 *
 * \param report The nkro report to send.
 */
void bluetooth_send_nkro(report_nkro_t *report);

/**
 * \brief Send a mouse report.
 *
 * \param report The mouse report to send.
 */
void bluetooth_send_mouse(report_mouse_t *report);

/**
 * \brief Send a consumer usage.
 *
 * \param usage The consumer usage to send.
 */
void bluetooth_send_consumer(uint16_t usage);

/**
 * \brief Send a system usage.
 *
 * \param usage The system usage to send.
 */
void bluetooth_send_system(uint16_t usage);

/**
 * \brief Send a raw_hid packet.
 *
 * \param data A pointer to the buffer to be sent. Always 32 bytes in length.
 * \param length The length of the buffer. Always 32.
 */
void bluetooth_send_raw_hid(uint8_t *data, uint8_t length);

/**
 * \brief Maximum number of Bluetooth profiles supported by the active driver.
 *
 * Single-host drivers return 1. Profile-aware drivers return the count of stored bond slots.
 *
 * \return Profile count (>=1).
 */
uint8_t bluetooth_get_max_profile(void);

/**
 * \brief Activate a Bluetooth profile.
 *
 * \param profile Zero-based profile index.
 * \return `true` on success, `false` if `profile` is out of range.
 */
bool bluetooth_set_profile(uint8_t profile);

/**
 * \brief Currently active Bluetooth profile.
 *
 * \return Zero-based profile index.
 */
uint8_t bluetooth_get_profile(void);

/**
 * \brief Drop the bond stored at the active Bluetooth profile.
 */
void bluetooth_unpair(void);
