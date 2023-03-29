/* Copyright 2021 WestM
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


/* Ensure we jump to bootloader if the QK_BOOT keycode was pressed */
#define EARLY_INIT_PERFORM_BOOTLOADER_JUMP TRUE

#define MATRIX_ROW_PINS { A13, B9, F1, A10, A9 }
#define MATRIX_COL_PINS { B14, B13, B12, B11, B10, B2, B1, B8, B7, B6, B5, B4, B3, A15, A14 }
#define DIODE_DIRECTION COL2ROW

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
