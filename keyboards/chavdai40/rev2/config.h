/* Copyright 2020 t-miyajima
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


#define EARLY_INIT_PERFORM_BOOTLOADER_JUMP FALSE

/* usb power settings */
#define USB_MAX_POWER_CONSUMPTION 100

#define MATRIX_ROW_PINS { A0, A15, B5, B6 }
#define MATRIX_COL_PINS { B7, B4, B3, A8, B1, B0, A7, A6, A5, A4, A3, A2, A1 }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW
