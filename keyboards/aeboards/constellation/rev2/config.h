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

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x4145 // AE
#define PRODUCT_ID      0x065C // 65 - Constellation
#define DEVICE_VER      0x0001
#define MANUFACTURER    AEBoards
#define PRODUCT         AEBoards Constellation Rev2

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

/* key matrix pins */
#define MATRIX_ROW_PINS { B15, A14, A2, B13, B14 }
#define MATRIX_COL_PINS { B12, H0, C15, C14, B11, B10, B2, B1, B0, A7, A6, A5, A4, A3 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

// I2C setup
#define I2C1_SCL            8
#define I2C1_SDA            9
#define I2C1_SCL_PAL_MODE   4
#define I2C1_SDA_PAL_MODE   4
#define I2C1_TIMINGR_PRESC  0U
#define I2C1_TIMINGR_SCLDEL 11U
#define I2C1_TIMINGR_SDADEL 0U
#define I2C1_TIMINGR_SCLH   14U
#define I2C1_TIMINGR_SCLL   42U

// I2C EEPROM
#define EEPROM_I2C_24LC64
