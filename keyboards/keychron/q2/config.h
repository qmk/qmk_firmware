/* Copyright 2021 @ Keychron (https://www.keychron.com)
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

/* USB Device descriptor parameter */
#define VENDOR_ID       0x3434
#define MANUFACTURER    Keychron
#define PRODUCT         Keychron Q2

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

/* key matrix pins */
#define MATRIX_ROW_PINS { B4, B3, A15, A14, A13 }
#define MATRIX_COL_PINS { C14, C15, A0, A1, A2, A3, A4, A5, A6, A7, B0, B1, A8, A9, H3 }

/* DIP switch */
#define DIP_SWITCH_MATRIX_GRID  { {4, 4} }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Disable DIP switch in matrix data */
#define MATRIX_MASKED

/* NKRO */
#define FORCE_NKRO

/* turn off effects when suspended */
#define RGB_DISABLE_WHEN_USB_SUSPENDED

/* Use 5 dynamic keymap layers */
#define DYNAMIC_KEYMAP_LAYER_COUNT 5

/* EEPROM Driver Configuration */
#define EXTERNAL_EEPROM_I2C_BASE_ADDRESS 0b10100010
