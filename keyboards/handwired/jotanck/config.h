/* Copyright 2023 jotix <jujodeve@gmail.com>
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

/* pro_micro pin-out */
#define MATRIX_ROW_PINS { D7, E6, B6, B2 }
#define MATRIX_COL_PINS { F4, F5, F6, F7, B1, B3, D3, D2, D1, D0, D4, C6 }

/* leds */
#define JOTANCK_LEDS
#define JOTANCK_LED1 B5
#define JOTANCK_LED2 B4

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
