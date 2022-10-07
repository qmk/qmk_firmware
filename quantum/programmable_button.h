/*
Copyright 2021 Thomas Weißschuh <thomas@t-8ch.de>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <stdint.h>
#include <stdbool.h>

/**
 * \defgroup programmable_button
 *
 * HID Programmable Buttons
 * \{
 */

/**
 * \brief Clear the programmable button report.
 */
void programmable_button_clear(void);

/**
 * \brief Add a button press to the report.
 *
 * \param index The index of the button to add, from 0 to 31.
 */
void programmable_button_add(uint8_t index);

/**
 * \brief Remove a button press from the report.
 *
 * \param index The index of the button to remove, from 0 to 31.
 */
void programmable_button_remove(uint8_t index);

/**
 * \brief Add a button press to the report, and flush it.
 *
 * \param index The index of the button to add, from 0 to 31.
 */
void programmable_button_register(uint8_t index);

/**
 * \brief Remove a button press from the report, and flush it.
 *
 * \param index The index of the button to remove, from 0 to 31.
 */
void programmable_button_unregister(uint8_t index);

/**
 * \brief Get the state of a programmable button.
 *
 * \param index The index of the button to check, from 0 to 31.
 *
 * \return `true` if the button is asserted.
 */
bool programmable_button_is_on(uint8_t index);

/**
 * \brief Send the programmable button report to the host.
 */
void programmable_button_flush(void);

/**
 * \brief Get the programmable button report.
 *
 * \return The bitmask of programmable buttons.
 */
uint32_t programmable_button_get_report(void);

/**
 * \brief Set the programmable button report.
 *
 * \param report A bitmask of programmable buttons.
 */
void programmable_button_set_report(uint32_t report);

/** \} */
