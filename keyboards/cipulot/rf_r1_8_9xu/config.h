/* Copyright 2023 Cipulot
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

#define MATRIX_ROWS 6
#define MATRIX_COLS 16

/* Custom matrix pins and port select array */
#define MATRIX_ROW_PINS \
    { B15, A8, B13, B12, B14, B0 }
#define MATRIX_COL_CHANNELS \
    { 3, 0, 1, 2, 4, 6, 7, 5 }
#define MUX_SEL_PINS \
    { B4, B5, B6 }

/* Hardware peripherals pins */
#define APLEX_EN_PIN_0 B7
#define APLEX_EN_PIN_1 A6
#define DISCHARGE_PIN A4
#define ANALOG_PORT A3

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define DEFAULT_ACTUATION_LEVEL 700
#define DEFAULT_RELEASE_LEVEL 650

#define DISCHARGE_TIME 10
