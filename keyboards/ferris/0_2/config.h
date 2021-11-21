/*
Copyright 2020 Pierre Chevalier <pierrechevalier83@gmail.com>

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

/* USB Device descriptor parameter */
#define VENDOR_ID 0xC2AB
#define PRODUCT_ID 0x0001
#define DEVICE_VER 0x0002
#define MANUFACTURER Cuddly Keyboards Ltd.
#define PRODUCT Ferris 0.2

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 10

#define MATRIX_ROWS_PER_SIDE (MATRIX_ROWS / 2)
#define MATRIX_COLS_PER_SIDE (MATRIX_COLS / 2)

#define UNUSED_MCU 24
#define UNUSED_MCP 7

// wiring
#define MATRIX_ROW_PINS_MCU \
    { B7, B6, B5, A2 }
#define MATRIX_COL_PINS_MCU \
    { B8, B4, B3, A15, A14 }
#define UNUSED_PINS_MCU \
    { A0, A1, A3, A4, A5, A6, A7, A8, A9, A10, A13, B0, B1, B2, B9, B12, B13, B14, B15, C13, C14, C15, F0, F1 }
#define MATRIX_ROW_PINS_MCP \
    { B0, B1, B2, B3 }
#define MATRIX_COL_PINS_MCP \
    { A0, A1, A2, A3, A4 }
#define UNUSED_PINS_MCP \
    { B4, B5, B6, B7, A5, A6, A7 }

#define MATRIX_ROW_PINS \
    { B7, B6, B5, A2, A0, A0, A0, A0 }
#define MATRIX_COL_PINS \
    { B8, B4, B3, A15, A14, A1, A1, A1, A1, A1 }
#define UNUSED_PINS \
    { A3, A4, A5, A6, A7, A8, A9, A10, A13, B0, B1, B2, B9, B12, B13, B14, B15, C13, C14, C15, F0, F1 }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* define if matrix has ghost (lacks anti-ghosting diodes) */
//#define MATRIX_HAS_GHOST

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* i2c settings */

#define I2C_DRIVER I2CD2
#define I2C1_SCL_BANK GPIOB
#define I2C1_SCL 10
#define I2C1_SDA_BANK GPIOB
#define I2C1_SDA 11
#define I2C1_TIMINGR_PRESC 2U
#define I2C1_TIMINGR_SCLDEL 1U
#define I2C1_TIMINGR_SDADEL 0U
#define I2C1_TIMINGR_SCLH 9U
#define I2C1_TIMINGR_SCLL 26U
#define I2C1_SCL_PAL_MODE 1
#define I2C1_SDA_PAL_MODE 1
