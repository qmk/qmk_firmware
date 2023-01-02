/* Copyright 2020 Paul James
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

#include "eeconfig.h"

enum custom_layers {
    _BASE = 0,
    _SYMBOL,
    _FUNCTION,
    _ADJUST,
};

// Fillers to make layering more clear
#define ______2 KC_TRNS, KC_TRNS
#define ______3 KC_TRNS, KC_TRNS, KC_TRNS
#define ______4 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
#define ______5 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS

enum custom_keycodes {
    MC_ARR = SAFE_RANGE,
    MC_DARR,
    MC_DEQL,
    MC_TEQL,
    KC_RESET
};

#define SYMBOL MO(_SYMBOL)
#define FUNCT MO(_FUNCTION)
#define ADJUST MO(_ADJUST)

#define FN_SPC LT(_FUNCTION, KC_SPC)
#define SY_SPC LT(_SYMBOL, KC_SPC)
#define FN_F LT(_FUNCTION, KC_F)
#define SY_J LT(_SYMBOL, KC_J)

#define CTLESC LCTL_T(KC_ESC)
#define SFTENT RSFT_T(KC_ENT)
#define LOCK LCTL(LGUI(KC_Q))
#define BACK LGUI(KC_LBRC)
#define FORWARD LGUI(KC_RBRC)
#define NXTFUNC LCTL(KC_DOWN)
#define PRVFUNC LCTL(KC_UP)
#define TOP LGUI(KC_UP)
#define BOTTOM LGUI(KC_DOWN)

#ifdef LAYOUT_ortho_4x12
    #define LAYOUT_PEEJ(...) LAYOUT_ortho_4x12(__VA_ARGS__)
#endif

#ifdef LAYOUT_ortho_5x12
    #define LAYOUT_PEEJ(...) LAYOUT_ortho_5x12(__VA_ARGS__)
#endif

#ifdef LAYOUT_ortho_hhkb
    #define LAYOUT_PEEJ_hhkb(...) LAYOUT_ortho_hhkb(__VA_ARGS__)
#endif

#ifdef LAYOUT_ortho_7u
    #define LAYOUT_PEEJ_7u(...) LAYOUT_ortho_7u(__VA_ARGS__)
#endif

#include "layout.h"
