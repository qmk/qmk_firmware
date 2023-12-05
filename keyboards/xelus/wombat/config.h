/* Copyright 2023 Harrison Chan (Xelus)
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

// SPI EEPROM left in because I couldn't get it working
// So using Wear-leveling for now
// SPI Setup
#define SPI_DRIVER        SPID1
#define SPI_SCK_PIN       A5
#define SPI_SCK_PAL_MODE  5
#define SPI_MOSI_PIN      A7
#define SPI_MOSI_PAL_MODE 5
#define SPI_MISO_PIN      A6
#define SPI_MISO_PAL_MODE 5

// SPI EEPROM Defines
#define EXTERNAL_EEPROM_SPI_SLAVE_SELECT_PIN A4
#define EXTERNAL_EEPROM_SPI_CLOCK_DIVISOR    64
#define EXTERNAL_EEPROM_BYTE_COUNT           65536
#define EXTERNAL_EEPROM_PAGE_SIZE            256
#define EXTERNAL_EEPROM_ADDRESS_SIZE         3

// wear levelling
#define WEAR_LEVELING_LOGICAL_SIZE 32768
#define WEAR_LEVELING_BACKING_SIZE 65536
