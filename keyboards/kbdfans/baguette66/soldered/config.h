/* Copyright 2022 DZTECH <moyi4681@Live.cn>
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


#define MATRIX_ROW_PINS { F0, F1, F4, F5, B6 }
#define MATRIX_COL_PINS { C6, C7, F7, F6, B0, B1, B2, B3, D0, D1, D2, D3, D5, D4, D6}

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW
/* disable these deprecated features by default */
#define USB_SUSPEND_WAKEUP_DELAY 5000
#define VIA_EEPROM_LAYOUT_OPTIONS_SIZE 2
