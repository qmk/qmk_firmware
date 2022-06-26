/* Copyright 2022 toinux
  * Copyright 2022 emdashii
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

enum crkbd_layers {
  _QWERTY,
  _NAVIGATION,
  _NUMBER,
  _SYMBOL,
  _FUNCTION,
  _ADJUST,
  _GAMING
};


// Left-hand home row mods
#define HOME_A LGUI_T(KC_A)
#define HOME_S LALT_T(KC_S)
#define HOME_D LSFT_T(KC_D)
#define HOME_F LCTL_T(KC_F)

// Right-hand home row mods
#define HOME_J RCTL_T(KC_J)
#define HOME_K RSFT_T(KC_K)
#define HOME_L LALT_T(KC_L)
#define HOME_SCLN RGUI_T(KC_SCLN)

// Special layer navigation keys
#define LNUMSPC LT(_NUMBER, KC_SPC)
#define LSYMDEL LT(_SYMBOL, KC_DEL)
#define LNAVSPC LT(_NAVIGATION, KC_SPC)
#define LOSLFUN OSL(_FUNCTION)
#define SQWERTY DF(_QWERTY)
#define LQWERTY TO(_QWERTY)
#define LGAMING TO(_GAMING)
#define LNAV    TO(_NAVIGATION)
#define LNUMFUN LT(_NUMBER, OSL(_FUNCTION)) // On tap, takes you to the function layer for one press. On hold, takes you to the number layers
#define LADJUST LT(_ADJUST)
#define LNAVCSX LT(C(S(_NAVIGATION)), XXXXXXX)  // This is a test
#define LNAVENT LT(C(_NAVIGATION), KC_ENT)      // This is a test

// Misc combined keys
#define CTRLSPC LCTL_T(KC_SPC)
#define CTRLSFT C(KC_LSFT)
#define COLON S(KC_SCLN)
#define TABLGUI LGUI_T(KC_TAB)

// Tab movement
#define TABFWRD C(KC_TAB)
#define TABBKWD C(S(KC_TAB))

//OSM(MOD_LSFT) One Shot Modifer Shift Key
