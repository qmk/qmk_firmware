/* Copyright 2020 Terence Rudkin
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

#include "muse.h"


#include "wrappers.h"

#define TAP_CODE_DELAY 5

bool process_record_mine(uint16_t keycode, keyrecord_t *record);

enum my_layers {
    _COLEMAK,
    _QWERTY,
    _DVORAK,
    _LOWER,
    _RAISE,
    _NUMPAD,
//_MOUSE,
    _FUNCTION,
    _ADJUST,
};

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  LOWER,
  RAISE,
  KC_MAKE,
    SECRET1, 
    SECRET2, 
    SECRET3, 
    SECRET4, 
    SECRET5,
  MY_PIPE,
 MY_PRINT_LAYOUT,

    NEW_SAFE_RANGE
};

#ifndef NO_SECRETS

#if __has_include ("secrets.h")
#    include "secrets.h"
#endif


/* these are defined in secrets if it is found */
#ifndef SS_R2C1
#   define SS_R2C1 "ls -tlr"
#endif
#ifndef SS_R2C2
#   define SS_R2C2 "grep -r  *" SS_TAP(X_LEFT) SS_TAP(X_LEFT)
#endif
#ifndef SS_R2C3
#   define SS_R2C3 "du -k|sort -n"
#endif
#ifndef SS_R2C4
#   define SS_R2C4  "No secrets here"
#endif
#ifndef SS_R2C5
#   define SS_R2C5  "No secrets here"
#endif




#endif

#define NUMPAD TG(_NUMPAD)

#ifdef TAP_DANCE_ENABLE
#   include "tap.h"

enum  td_keycodes {
    TD_ESC_CAPS,
    TD_DEL_INS,
    TD_BKSP_DEL,
    TD_SPC_ENT,
    TD_CUT,
    TD_COPY,
    TD_PASTE,
    MOD_FN,
    LBRC_9,
    RBRC_0,
    TD_PIPE,
    MOD_LOW,
    MOD_RAI,
    TD_B,
    TD_SAFE_RANGE
};





#   define MY_LOW TD(MOD_LOW)
#   define MY_RAI TD(MOD_RAI)
#   define MY_ESC TD(TD_ESC_CAPS)
#   define MY_K TD(MOD_FN)
#   define MY_X KC_X
#   define MY_C KC_C
#   define MY_V KC_V
#   define MY_LGUI LGUI_T(KC_F23)
#   define MY_DEL TD(TD_DEL_INS)
#   define MY_BKSP TD(TD_BKSP_DEL)
#   define MY_9 TD(LBRC_9)
#   define MY_0 TD(RBRC_0)
#   define MY_B TD(TD_B)
#else
#   define MY_LOW TT(_LOWER)
#   define MY_RAI TT(_RAISE)
#   define MY_ESC KC_ESC
#   define MY_K KC_K 
#   define MY_Q KC_Q
#   define MY_X KC_X
#   define MY_C KC_C
#   define MY_V KC_V
#   define MY_LGUI LGUI_T(KC_F23)
#   define MY_BKSP KC_BSPC
#   define MY_DEL KC_DEL
#   define MY_9 KC_9
#   define MY_0 KC_0
#   define KC_M KC_M
#endif 


