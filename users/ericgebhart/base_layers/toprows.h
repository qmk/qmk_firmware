#pragma once
/*
  Copyright 2018-2022 Eric Gebhart <e.a.gebhart@gmail.com>

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
/*******************************************************************/
/** TOP ROWS  Func,Symbols, Numbers you find there.               **/
/*******************************************************************/
// ltkc  language target keycode DV, BK, BKW, NONE
//   _1 = DV_1 or _1 = BP_DV_1 or KC_1
#define ___10_NUMBERS___                                \
  LANG_ROW(_1, _2, _3, _4, _5, _6, _7, _8, _9, _0)

/*  40123 76598  */
#define ___10_NUMBERS_BEAKL15___                        \
  LANG_ROW(_4, _0, _1, _2, _3, _7, _6, _5, _9, _8)

/*  32104 76598  */
#define ___10_NUMBERS_BEAKL19___                        \
  LANG_ROW(_3, _2, _1, _0, _4, _7, _6, _5, _9, _8)

// a top symbol row if someone wants it.
#define ___10_SYMBOLS___                                                \
  LANG_ROW(_EXLM, _AT, _HASH, _DLR, _PERC, _CIRC, _AMPR, _ASTR, _LPRN, _RPRN)

// standard bepo top row
#define ___10_SYMBOLS_BEPO___                                           \
  LANG_ROW(_DQUO, _LDAQ, _RDAQ, _LPRN, _RPRN, _AT, _PLUS, _MINS, _SLSH, _ASTR)

#define ___12_SYMBOLS_BEPO___                           \
  LANG_ROW12(_DLR, _DQUO, _LDAQ, _RDAQ, _LPRN, _RPRN,   \
             _AT,  _PLUS, _MINS, _SLSH, _ASTR, _EQL)

// function key rows work for everyone.
#define ___10_FUNCS___                                                  \
  KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10

#define ___12_FUNCS___ ___10_FUNCS___, KC_F11, KC_F12

#define ___10_FUNCS_BEAKL15___                  \
  KC_F4,   KC_F10,   KC_F1,   KC_F2,   KC_F3,   \
    KC_F7,   KC_F6,   KC_F5,   KC_F9,   KC_F8

#define ___12_FUNCS_BEAKL15___ KC_F11, ___10_FUNCS_BEAKL15___, KC_F12
