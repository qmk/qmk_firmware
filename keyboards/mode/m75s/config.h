/*
 Copyright 2020 Álvaro "Gondolindrim" Volpato <alvaro.volpato@usp.br>

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

/* key matrix size */
#define MATRIX_ROWS 7
#define MATRIX_COLS 16
                       // C0, C1, C2,  C3,  C4,  C5,  C6,  C7, C8,  C9, C10, C11, C12, C13, C14, C15
#define MATRIX_COL_PINS { C8, A8, A10, B13, B12, B10, B1, C10, C11, D2, C12, B3,  B4,  B5,  B8,  B9 }
                       // R0, R1, R2,  R3,  R4,  R5 , R6
#define MATRIX_ROW_PINS { C5, B0, B14, B15, C7 , C9 , A15} 
#define DIODE_DIRECTION COL2ROW

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define BACKLIGHT_PIN C6
#define BACKLIGHT_LEVELS 20
#define BACKLIGHT_CAPS_LOCK
#define BACKLIGHT_DEFAULT_LEVEL 20
#define BACKLIGHT_PWM_DRIVER PWMD3
#define BACKLIGHT_PWM_CHANNEL 1
#define BACKLIGHT_PAL_MODE 2

#define WEAR_LEVELING_LOGICAL_SIZE 2048
#define WEAR_LEVELING_BACKING_SIZE 4096
