/*
  Copyright 2018 Eric Gebhart <e.a.gebhart@gmail.com>

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

#ifndef USERSPACE_CONFIG_H
#define USERSPACE_CONFIG_H

#include "../../config.h"

#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
#define COMBO_MUST_HOLD_MODS
#define COMBO_HOLD_TERM 150
// Sets good default for the speed of the mouse.
#undef MOUSEKEY_INTERVAL
#undef MOUSEKEY_DELAY
#undef MOUSEKEY_TIME_TO_MAX
#undef MOUSEKEY_MAX_SPEED

#define MOUSEKEY_INTERVAL       20
#define MOUSEKEY_DELAY          100
#define MOUSEKEY_TIME_TO_MAX    60
#define MOUSEKEY_MAX_SPEED      7

#undef MOUSEKEY_WHEEL_MAX_SPEED
#undef MOUSEKEY_WHEEL_TIME_TO_MAX
#undef MOUSEKEY_WHEEL_DELAY

#define MOUSEKEY_WHEEL_MAX_SPEED    5
#define MOUSEKEY_WHEEL_TIME_TO_MAX  60
#define MOUSEKEY_WHEEL_DELAY        100

#undef TAPPING_TOGGLE
#undef TAPPING_TERM
#undef IGNORE_MOD_TAP_INTERRUPT

#define TAPPING_TOGGLE  2
#define TAPPING_TERM    200
#define IGNORE_MOD_TAP_INTERRUPT


/* Control switches for my keymaps. */
/* if needed, this goes in the keyboard's config.h */
/* Alternately, fix the number row in the layout template. */
/* #define BASE_NUMBER_ROW    // turn on 4 row base templates. */

// Turn on the layers
#define DVORAK_LAYER_ENABLE
#define QWERTY_LAYER_ENABLE
#define COLEMAK_LAYER_ENABLE
#define BEAKL_LAYER_ENABLE
//#define CARPLAX_LAYER_ENABLE
//#define WORKMAN_LAYER_ENABLE
//#define NORMAN_LAYER_ENABLE
//#define MALTRON_LAYER_ENABLE
//#define EUCALYN_LAYER_ENABLE

// Enable bepo layers.
// This will add bepo versions of qwerty layers if they exist.
#define BEPO_ENABLE
#define BEPO_LAYER_ENABLE  // Bepo only works on bepo.

// enable transient function layers.
#define SYMBOL_LAYER_ENABLE
#define NAV_LAYER_ENABLE
#define TOPROWS_LAYER_ENABLE
#define LAYERS_LAYER_ENABLE
#define KEYPAD_LAYER_ENABLE
//#define ADJUST_LAYER_ENABLE
//#define RGB_LAYER_ENABLE

/* configure the function layers. */

/* keypads */
//#define KEYPAD_RIGHT
#define KEYPAD_BEAKL         // beakl doesn't have a rightside, swap hands?

/* symbols */
//#define SYMBOL_BEAKL       // original
//#define SYMBOL_BEAKL_EXT   // extended.
#define SYMBOL_BEAKL_EXT_VI  // extended with vi keybinding in mind.

/* toprows. */
#define TOPROWS_BKL_NUMS     // center row with Beakl order. 40123 76598.

#endif
