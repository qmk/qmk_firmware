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
#define MATRIX_ROW_PINS     { B4, B5, B7, D5, C7, F1, F0, B6 }
#define MATRIX_COL_PINS     { F4, F5, F6, F7, B1, B3, B2, E6, D7 }

/* Indicator LEDs */
#define LED_INDICATOR_TOP   B0
#define LED_INDICATOR_MID   D4
#define LED_INDICATOR_BOT   C6

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION     COL2ROW
