/* Copyright 2020 Stephen Bush
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
#include QMK_KEYBOARD_H

/* Define a stand-in from dancelayers.h in case tap-dance isn't enabled */
#ifndef TAP_DANCE_ENABLE
#    define TD_LAYR XXXXXXX
#endif

/* Misc */

#define HY_ESC HYPR_T(KC_ESC)
#define HY_BSPC HYPR_T(KC_BSPC)

/* Tap Mod Layers */

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define NAV MO(_NAV)

#define ADJ_DEL LT(_ADJUST, KC_DEL)
#define LOW_ENT LT(_LOWER, KC_ENT)
#define LOW_SPC LT(_LOWER, KC_SPC)
#define LOW_BSP LT(_LOWER, KC_BSPC)
#define NAV_SPC LT(_NAV, KC_SPC)
#define RAI_BSP LT(_RAISE, KC_BSPC)
#define RAI_ENT LT(_RAISE, KC_ENT)
#define RAI_SPC LT(_RAISE, KC_SPC)
#define RAI_TAB LT(_RAISE, KC_TAB)

/* Miryoku Home-row Mods

NOTE: Uses GACS.
*/

// Left-hand home row mods (colemak)
#define HR_A LGUI_T(KC_A)
#define HR_R LALT_T(KC_R)
#define HR_S LCTL_T(KC_S)
#define HR_T LSFT_T(KC_T)

// Right-hand home row mods (colemak)
#define HR_N RSFT_T(KC_N)
#define HR_E RCTL_T(KC_E)
#define HR_I LALT_T(KC_I)
#define HR_O RGUI_T(KC_O)

// Right-hand Numpad
#define HR_4 RSFT_T(KC_4)
#define HR_5 RCTL_T(KC_5)
#define HR_6 LALT_T(KC_6)

// Layout-specific mods
#define TM_VSFT LSFT_T(KC_V)  // For Using V in layer combos (e.g., planck)

// GACS (Lower)
#define HR_LBRC LCTL_T(KC_LBRC)
#define HR_RBRC LSFT_T(KC_RBRC)

// Left-hand home row mods (lower)---
// #define HOME_UND LCTL_T(KC_UNDS)  // NOTE: Mod-tap restricted to basic keycodes
#define HOME_MIN LSFT_T(KC_MINS)
