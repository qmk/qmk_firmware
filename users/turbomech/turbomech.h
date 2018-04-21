/* Copyright 2017 @TurboMech /u/TurboMech <discord> @A9entOran9e#6134
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


#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"

// Definine layer names
#define _QWERTY 0
#define _FUNCTION 1

#ifdef RGBLIGHT_ENABLE
//values are HSV (Hue, Sat, Val) - except Sat and Val equal 255 for 100%.
#define rgblight_set_blue        rgblight_sethsv (240, 255, 255);
#define rgblight_set_red         rgblight_sethsv (0, 255, 255);
#define rgblight_set_green       rgblight_sethsv (120, 255, 255);
#define rgblight_set_orange      rgblight_sethsv (30, 255, 255);
#define rgblight_set_teal        rgblight_sethsv (195, 255, 255);
#define rgblight_set_magenta     rgblight_sethsv (300, 255, 255);
#define rgblight_set_yellow      rgblight_sethsv (60, 255, 255);
#define rgblight_set_purple      rgblight_sethsv (270, 255, 255);
#define rgblight_set_cyan        rgblight_sethsv (180, 255, 255);
#define rgblight_set_white       rgblight_sethsv (0, 0, 255)
#endif

//must use KC_RESET in order to have RESET indicate a color/mode
enum userspace_custom_keycodes {
  EPRM = SAFE_RANGE,  //should always be here
  KC_RESET,
  KC_MAKE_ALU84,
  KC_QMK,
  _FLIP,
  NEW_SAFE_RANGE
};
#endif
