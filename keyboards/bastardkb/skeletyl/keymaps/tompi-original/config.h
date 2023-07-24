/*
Copyright 2020 Pierre Chevalier <pierrechevalier83@gmail.com>

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

#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD

// Pick good defaults for enabling homerow modifiers
#define TAPPING_TERM 240
// #define PERMISSIVE_HOLD
#define IGNORE_MOD_TAP_INTERRUPT
#define TAPPING_FORCE_HOLD
//#define RETRO_TAPPING
//
#undef MATRIX_COL_PINS
#define MATRIX_COL_PINS \
     { B1, B10, B4, B3, B8 }
#undef MATRIX_COL_PINS_RIGHT
#define MATRIX_COL_PINS_RIGHT \
     { B1, B10, B3, B4, B5 }

#undef MATRIX_ROW_PINS
#define MATRIX_ROW_PINS \
     { A2, B5, B9, A8 }
#undef MATRIX_ROW_PINS_RIGHT
#define MATRIX_ROW_PINS_RIGHT \
     { A2, B8, A8, B9 }

// Underglow configuration
#ifdef RGBLIGHT_ENABLE
  #define RGBLIGHT_ANIMATIONS
  #define RGBLIGHT_HUE_STEP 8
  #define RGBLIGHT_SAT_STEP 8
  #define RGBLIGHT_VAL_STEP 8
#endif

 /* Top left key on left half */
  #undef BOOTMAGIC_LITE_ROW
  #undef BOOTMAGIC_LITE_COLUMN
  #define BOOTMAGIC_LITE_ROW    0
  #define BOOTMAGIC_LITE_COLUMN 0
  /* Top right key on right half */
  #undef BOOTMAGIC_LITE_ROW_RIGHT
  #undef BOOTMAGIC_LITE_COLUMN_RIGHT
  #define BOOTMAGIC_LITE_ROW_RIGHT    4
  #define BOOTMAGIC_LITE_COLUMN_RIGHT 4
