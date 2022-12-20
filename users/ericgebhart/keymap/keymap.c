/*
  Copyright 2022 Eric Gebhart <e.a.gebhart@gmail.com>

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

/* This is my keymap. Enable the layers you want in config.h. */

#include QMK_KEYBOARD_H
#include "ericgebhart.h"
#include "layouts.h"

#include "keyboards.h"

// set up the wrapper macros.
#define BASE_LAYER(NAME, ...)  [NAME] = BASE(__VA_ARGS__)
#define BASE_LAYERt6(NAME, ...)  [NAME] = BASEt6(__VA_ARGS__)
#define T_LAYER(LNAME, ...)  [LNAME] = TRANS(__VA_ARGS__)


// One that takes 5 and one that takes 6 for bepo and other big maps
// that need 3x12 instead of 3x10.
#ifdef BASE_NUMBER_ROW
#define B_LAYER(LNAME, NUMS, LAYOUT) BASE_LAYER(LNAME, NUMS, LAYOUT)
#define B_LAYERt6(LNAME, NUMS, LAYOUT) BASE_LAYERt6(LNAME, NUMS, LAYOUT)
#else
// if there is no number row, don't give it one.
#define B_LAYER(LNAME, NUMS, LAYOUT) BASE_LAYER(LNAME, LAYOUT)
#define B_LAYERt6(LNAME, NUMS, LAYOUT) BASE_LAYERt6(LNAME, LAYOUT)
#endif

// Find alt local key definitions.
// DV for dvorak/qwerty maps on bepo.
// BK, BKW for beakl maps on en-qwerty and bepo.
// BKW is automatic in map_beakl.h
#define ALT_TARGET_IS NONE // NONE, DV=dvorak, BK=Beakl, BK2, BKW=Beaklwi.


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // Default lang, Base layers
#include "map_dvorak.h"
#include "map_maks.h"
#include "map_qwerty.h"
#include "map_beakl.h"
#include "map_alt.h"
#include "map_gap.h"
#include "map_carpalx.h"
#include "map_hd.h"
#include "map_bepo.h"

  // create a set of layers for a second locale.
#ifdef SECOND_LOCALE
#undef LANG_IS
#define LANG_IS SECOND_LOCALE

  // changes alt target for us, because both en-qwerty and fr-bepo
  // need a beakl alt target.
#include "map_beakl.h"

  // Qwerty based layers. Need a DV alt target to get the right shifted keys.
#undef ALT_TARGET_IS
#define ALT_TARGET_IS DV // NONE, DV = dvorak, BK=Beakl, BKW=Beaklwi.

#include "map_dvorak.h"
#include "map_maks.h"
#include "map_qwerty.h"
#include "map_alt.h"
#include "map_gap.h"
#include "map_carpalx.h"
#include "map_hd.h"

#undef ALT_TARGET_IS
#define ALT_TARGET_IS NONE // NONE, DV = dvorak, BK=Beakl, BKW=Beaklwi.

#include "map_bepo.h"

#undef LANG_IS
#define LANG_IS DEFAULT_LANG
#endif // bepo


// SYMBOL LAYER
#include "map_symbols.h"

#ifdef SECOND_LOCALE
#undef LANG_IS
#define LANG_IS SECOND_LOCALE

#include "map_symbols.h"

#undef LANG_IS
#define LANG_IS DEFAULT_LANG
#endif


  // KEYPAD LAYER
#include "map_keypads.h"

#ifdef SECOND_LOCALE
#undef LANG_IS
#define LANG_IS SECOND_LOCALE

#include "map_keypads.h"

#undef LANG_IS
#define LANG_IS DEFAULT_LANG
#endif


// TOPROWS LAYER
#include "map_toprows.h"

#include "map_accented.h"

#ifdef SECOND_LOCALE
#undef LANG_IS
#define LANG_IS SECOND_LOCALE

#include "map_toprows.h"

#include "map_accented.h"

#undef LANG_IS
#define LANG_IS EN
#endif

// functional non language based layers.
#include "map_funcs.h"

};
