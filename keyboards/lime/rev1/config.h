 /* Copyright 2021 HellSingCoder
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

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 12
#define MATRIX_COLS 6

// wiring of each half
#define MATRIX_ROW_PINS { D4, C6, D7, E6, B4, B5 }
#define MATRIX_COL_PINS { F6, F7, B1, B3, B2, B6 }
#define DIODE_DIRECTION COL2ROW

#define TAPPING_TERM 100
#define DEBOUNCE 5

/* encoder support */
#ifdef ENCODER_ENABLE
#   define ENCODERS_PAD_A { F5 }
#   define ENCODERS_PAD_B { F4 }
#   define ENCODERS_PAD_A_RIGHT { F4 }
#   define ENCODERS_PAD_B_RIGHT { F5 }
#   define ENCODER_RESOLUTION 2
#endif

/* joystick support */
#ifdef JOYSTICK_ENABLE
#   define JOYSTICK_AXIS_COUNT 2
#   define JOYSTICK_BUTTON_COUNT 1
#   define JOYSTICK_AXIS_RESOLUTION 8
#endif

#define TAP_CODE_DELAY 10

/* communication between sides */
#define SOFT_SERIAL_PIN D2

#define SPLIT_USB_DETECT

#ifdef WPM_ENABLE
#    define SPLIT_WPM_ENABLE
#endif

