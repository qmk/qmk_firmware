/* Copyright 2018 wanleg
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

// place overrides here
#undef MATRIX_ROW_PINS
#define MATRIX_ROW_PINS { B4 }
#undef MATRIX_COL_PINS
#define MATRIX_COL_PINS { B6 }

/* COL2ROW, ROW2COL*/
#undef DIODE_DIRECTION
#define DIODE_DIRECTION COL2ROW

#define BACKLIGHT_PIN B5
#define BACKLIGHT_BREATHING
#define BACKLIGHT_LEVELS 3
#define BREATHING_PERIOD 5

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#undef DEBOUNCE
#define DEBOUNCE 5

// set flashing LED with QMK DFU
#define QMK_LED B0

// set audio pin
#define AUDIO_PIN C6
