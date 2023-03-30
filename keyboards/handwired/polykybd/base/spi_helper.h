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

// SPI helper functions
void spi_hw_setup(void);

// Prepare SPI device for command transfer; SPI_DC_PIN will be set to low
void spi_prepare_commands(void);

// Prepare SPI device for data transfer; SPI_DC_PIN will be set to high
void spi_prepare_data(void);

// Reset all connected SPI devices by pulling SPI_RST_PIN to low for 1 msec
void spi_reset(void);
