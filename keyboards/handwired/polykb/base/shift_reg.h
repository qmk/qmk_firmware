/* Copyright 2019
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

#include "quantum.h"

// Shift register helper functions
void sr_hw_setup(void);

// Initialize the shift register by pulling SR_NMR_PIN to low for 10 usec
void sr_init(void);

// Send a single byte to the shift register using SR_CLK_PIN and SR_DATA_PIN
void sr_shift_out(uint8_t val);

// Send a single byte and pull SR_LATCH_PIN to high for 10 usec to apply the byte to the outputs
void sr_shift_out_latch(uint8_t val);

void sr_shift_out_buffer_latch(const uint8_t* val, uint8_t len);
