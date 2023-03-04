/* Copyright 2022 W. Alex Ronke, a.k.a. NoPunIn10Did (w.alex.ronke@gmail.com)
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


/* key matrix pins */
#define MATRIX_ROW_PINS     { B2, B3, B1, D4, B4, D1, E6, B0, F0, F1, F4, F5 }
#define MATRIX_COL_PINS     { D0, D2, D3, D5, B5, D7, F6, F7, C7, B6 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION     COL2ROW

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* Reducing layer count to 3 for via support */
#define DYNAMIC_KEYMAP_LAYER_COUNT  3
