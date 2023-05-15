/*
Copyright 2020 kb-elmo<mail@elmo.space>

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
 * Keyboard Matrix Assignments
 */
#define MATRIX_ROW_PINS { D5, C1, C4, D0, C3, C2, B3, B4 }
#define MATRIX_COL_PINS { A1, A0, A2, A3, A4, A5, A6, A7, C7, C6, C5, C0, D6, D1 }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* reduce EEPROM usage */
#define DYNAMIC_KEYMAP_LAYER_COUNT 3
#define LAYER_STATE_8BIT
