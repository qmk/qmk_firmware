/* Copyright 2022
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

/**
 * Driver for 74x138 3-to-8 decoder/demultiplexer with inverting outputs
 * https://assets.nexperia.com/documents/data-sheet/74HC_HCT138.pdf
 */

/**
 * Initialize the address and output enable pins.
 */
void sn74x138_init(void);

/**
 * Set the enabled state.
 *
 * When enabled is true, pulls the E1 and E2 pins low, and the E3 pin high.
 *
 * \param enabled The enable state to set.
 */
void sn74x138_set_enabled(bool enabled);

/**
 * Set the output pin address.
 *
 * The selected output pin will be pulled low, while the remaining output pins will be high.
 *
 * \param address The address to set, from 0 to 7.
 */
void sn74x138_set_addr(uint8_t address);
