/* Copyright 2021 Harrison Chan (Xelus)
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

/* key matrix size */
#define MATRIX_ROWS 18
#define MATRIX_COLS 14

#define MATRIX_COL_PINS { C11, C12, D0, D1, B10, E15, E14, E13, E12, E11, A13, A1,  C5, C4 }
#define MATRIX_ROW_PINS { B6,  B5,  B3, B4, D6,  D7,  D4,  D5,  D2,  D3,  A15, C10, A3, A2, B1, B0, B2, E7 }
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

// Encoders
#define ENCODERS_PAD_A { B11, B13, B15, D9,  D11, D13, D15, C7, C9, A9,  B7, B9, E1, E3, E5, C13, C15, H1, C1, C3 }
#define ENCODERS_PAD_B { B12, B14, D8,  D10, D12, D14, C6,  C8, A8, A10, B8, E0, E2, E4, E6, C14, H0,  C0, C2, A0 }
#define ENCODER_RESOLUTION 4

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

// Dynamic EEPROM
#define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR 32767

// Force NKRO
#define FORCE_NKRO

#define DEBUG_EEPROM_OUTPUT

// wear levelling
#define WEAR_LEVELING_LOGICAL_SIZE 32768
#define WEAR_LEVELING_BACKING_SIZE 65536
