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
#define TAPPING_TERM 230
// #define PERMISSIVE_HOLD
#define TAPPING_FORCE_HOLD
//#define RETRO_TAPPING
//

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
