/*
Copyright 2018 Mattia Dal Ben <matthewdibi@gmail.com>

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

/* Use I2C or Serial, not both */
// #define USE_SERIAL
#define USE_I2C

/* Select hand configuration */
// #define MASTER_LEFT
// #define MASTER_RIGHT
#define EE_HANDS

// Left half wiring
#ifdef MATRIX_ROW_PINS
    #undef MATRIX_ROW_PINS
#endif
#ifdef MATRIX_COL_PINS
    #undef MATRIX_COL_PINS
#endif
#define MATRIX_ROW_PINS { C6, D7, E6, B4, B5 }
#define MATRIX_COL_PINS { B6, B2, B3, B1, F7, F6, F5 }

// Tapping time for mod-tap
#define TAPPING_TERM 200

// Prevent normal rollover on alphas from accidentally triggering mods (Home row mods)
#define IGNORE_MOD_TAP_INTERRUPT

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat (Home row mods)
#define TAPPING_FORCE_HOLD_PER_KEY
