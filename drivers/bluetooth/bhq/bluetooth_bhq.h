/* Copyright 2024 keymagichorse
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
#include "action.h"
#include "report.h"

/**
 * \brief Initialize the Bluetooth system.
 */
void bluetooth_bhq_init(void);

/**
 * \brief Perform housekeeping tasks.
 */
void bluetooth_bhq_task(void);


/**
 * \brief Send a keyboard report.
 *
 * \param report The keyboard report to send.
 */
void bluetooth_bhq_send_keyboard(report_keyboard_t *report);

/**
 * \brief Send a mouse report.
 *
 * \param report The mouse report to send.
 */
void bluetooth_bhq_send_mouse(report_mouse_t *report);

/**
 * \brief Send a consumer usage.
 *
 * \param usage The consumer usage to send.
 */
void bluetooth_bhq_send_consumer(uint16_t usage);

/**
 * \brief Send a system usage.
 *
 * \param usage The system usage to send.
 */
void bluetooth_bhq_send_system(uint16_t usage);


/**
 * \brief Send a nkro report.
 *
 * \param report The nkro report to send.
 */
void bluetooth_bhq_send_nkro(report_nkro_t *report);


/**
 * \brief Send a hid_raw report.
 *
 * \param report The hid_raw report to send.
 */
void bluetooth_bhq_send_hid_raw(uint8_t *data, uint8_t length);


/**
 * \brief Set Bluetooth led state.
 *
 * \param report Set Bluetooth led state.
 */
void bluetooth_bhq_set_keyboard_leds(uint8_t led_sta);

/**
 * \brief Get Bluetooth led state.
 *
 * \param report Get Bluetooth led state.
 */
uint8_t bluetooth_bhq_get_keyboard_leds(void);