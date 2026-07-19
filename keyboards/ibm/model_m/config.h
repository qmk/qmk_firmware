/*
Copyright 2024 Richard George

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

/*
 * Arduino Pro Micro Pin Mapping
 * ---------------------------
 * Physical pin locations preserved from original design:
 * D5  (Arduino Pin 5)  -> PC6 -> QMK: C6  (CS1 - Expander A, address 0x01, long 16-pin connector, columns)
 * D6  (Arduino Pin 6)  -> PD7 -> QMK: D7  (CS2 - Expander B, address 0x00, short 8-pin connector, rows)
 * D14 (Arduino Pin 14) -> PB3 -> QMK: B3  (MISO)
 * D15 (Arduino Pin 15) -> PB1 -> QMK: B1  (SCK)
 * D16 (Arduino Pin 16) -> PB2 -> QMK: B2  (MOSI)
 *
 * MCP23S17 Configuration:
 * - Expander A (CS1): Connected to long 16-pin connector, handles columns, address 0x01
 *   GPA0->pin1, GPA1->pin2, ..., GPA7->pin8, GPB0->pin9, ..., GPB7->pin16
 * - Expander B (CS2): Connected to short 8-pin connector, handles rows, address 0x00
 *   GPA0->pin1, GPA1->pin2, ..., GPA7->pin8
 */

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 16

/* SPI for MCP23S17 - mapped to Arduino Pro Micro physical pins */
#define SPI_DRIVER SPID1    /* Using hardware SPI on pins D14-D16 */
#define MCP23S17_CS1_PIN C6 /* D5 -> PC6 (CS1 - Expander A for columns) */
#define MCP23S17_CS2_PIN D7 /* D6 -> PD7 (CS2 - Expander B for rows) */
