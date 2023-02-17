/* Copyright 2022 bojiguard (@bojiguard)
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

/* select keyboard  master board  - I2C or Serial communication master    */
#define MASTER_RIGHT


// wiring of each half
#define MATRIX_COL_PINS { F4, F5, F6, F7, B1, B3, B2}
#define MATRIX_ROW_PINS { D4, C6, D7, E6, B4, B5}

#define MATRIX_COL_PINS_RIGHT {F7, F6, F5, F4, B5, B4, E6}
#define MATRIX_ROW_PINS_RIGHT { D1, D0, D4, C6, D7, D3}    	// TX




/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW



/*************************************/
/**       public parameter       **/
/*************************************/

#define MATRIX_IO_DELAY 15  // default  30
#define TAP_CODE_DELAY  50   // default 0, disabled

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

//지정된 횟수로 눌러야 토글됨
#define TAPPING_TOGGLE 3


