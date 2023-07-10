/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
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

/*** Keymap configurations ***/
/* Tap Hold configuration */
#define IGNORE_MOD_TAP_INTERRUPT
#define PERMISSIVE_HOLD
#define TAPPING_TERM 185

/* Combos */
#define COMBO_VARIABLE_LEN
#define COMBO_TERM 75

/* Capsword */
#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD

/*** Hardware configurations ***/
/* Trackball configuration */
//undefine charybdis default configuration
#undef ROTATIONAL_TRANSFORM_ANGLE
#undef POINTING_DEVICE_INVERT_X
//define Wimads trackball configuration
#define POINTING_DEVICE_INVERT_Y
#define CHARYBDIS_MINIMUM_SNIPING_DPI 300
#define CHARYBDIS_MINIMUM_DEFAULT_DPI 700
#define CHARYBDIS_DRAGSCROLL_REVERSE_Y
#define CHARYBDIS_DRAGSCROLL_BUFFER_SIZE 2

/* Elite-c pinout configuration */
//undefine charybdis default configuration
#undef MATRIX_ROW_PINS
#undef MATRIX_COL_PINS
#undef MATRIX_ROW_PINS_RIGHT
#undef MATRIX_COL_PINS_RIGHT
#undef SOFT_SERIAL_PIN
#undef PMW33XX_CS_PIN
//define Wimads pinout configuration
#define MATRIX_ROW_PINS       { B5, F7, F6, B6 }
#define MATRIX_COL_PINS       { E6, C6, B1, B3, B2 }
#define MATRIX_ROW_PINS_RIGHT { B5, F7, F6, B6 }
#define MATRIX_COL_PINS_RIGHT { E6, C6, F1, C7, D5 }
#define SOFT_SERIAL_PIN D0
#define PMW33XX_CS_PIN F0
