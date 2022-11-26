/* Copyright 2021-2022 Selene ToyKeeper
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
#include "version.h"  // for the TK_INFO key
#include "layouts.h"  // for qwerty/dvorak/colemak/etc layout definitions


///// things which can be defined in individual keymaps /////

// RGB Matrix?
//#define HAS_RGB

// Keychron switch on the back?
//#define HAS_DIPSWITCH

// enable numpad layer?
//#define USE_NUMPAD

// F1-F12 row?
//#define HAS_F_ROW

// Keychron Q65 has a column of extra keys on the left side
//#define HAS_XTRA_COLUMN

// has palm keys?  (Keyboardio Model01)
//#define USE_PALM

// lockable ctrl keys (unused)
//#define USE_TK_CLK

// If there's no physical key for mouselock, overload the GUI key (Whitefox)
//#define USE_RGUI_2TAP_MOUSELOCK

// Extend CapsWord's "word" characters for better compatibility on non-qwerty hosts?
//#define USE_CAPSWORD_KLUDGE

// don't include build info key
//#define DONT_USE_TK_INFO

// don't include "Any" key
//#define DONT_USE_ANY_KEY

// don't allow user to swap I and U keys on dvorak layer
//#define DONT_USE_TK_IUUI

// don't save any user config data (saves space)
//#define DONT_USE_EEPROM


// layers
enum {
    L_QWERTY = 0,
    L_DVORAK,
    L_UNDVORAK,
    L_COLEMAK,
    #ifdef USE_NUMPAD
    L_NUMPAD,
    #endif
    #ifdef HAS_F_ROW
    L_FLCK,   // toggle F1-F12 behavior (only used on 75% boards and bigger)
    #endif
    #ifdef USE_PALM  // palm Fn keys
    L_LPALM,  // left palm key
    L_RPALM,  // right palm key
    L_BOTH,   // both palm keys
    #else  // regular Fn keys
    L_MOUSE,  // lower right
    L_FN1,    // lower left
    L_FN2,    // upper right
    #endif
    #ifdef HAS_XTRA_COLUMN
    L_XC1,
    L_XC2,
    L_XC3,
    #endif
};
#define L_BOTTOM (L_COLEMAK+1)  // lowest non-default layer

enum custom_keycodes {
    TK_INFO = SAFE_RANGE,  // print build version / info
    // activate base layers like DF(N), and save them to the current switch slot
    TK_DF_0,  // qwerty
    TK_DF_1,  // dvorak
    TK_DF_2,  // undvorak
    TK_DF_3,  // colemak-dh traditional w/ TK mods
    // like base layers, but for the extra keys only
    TK_XC_0,  // Xtra Column mode 0
    TK_XC_1,  // Xtra Column mode 1
    TK_XC_2,  // Xtra Column mode 2
    TK_XC_3,  // Xtra Column mode 3
    // other custom keys
    TK_IUUI,  // toggle U/I swap on dvorak layer
    TK_ANY,   // the "Any" key, spits out random characters
};

// custom keys which don't need a custom enum
#ifdef USE_PALM
// Keyboardio Model-01
#define TK_LPLM MO(L_LPALM)
#define TK_RPLM MO(L_RPALM)
#define TK_BOTH MO(L_BOTH)
#define TK_MOON TK_LPLM
#define TK_STAR TK_RPLM
#define TK_VOID TK_BOTH
#else
// 65% to 75% layouts
#define TK_MOON  MT(L_FN1,L_FN1)  // hold / lock / clear L_FN1
#define TK_STAR  LT(L_FN2,KC_HOME)
#define TK_MOUS  TT(L_MOUSE)
#define TK_FN1   TK_MOON
#define TK_FN2   TK_STAR
#define TK_HOME  TK_STAR
#endif

#define TK_RCTL  MT(MOD_RCTL,_______)  // RCTL / toggle(L_NUMPAD)
#define TK_LALT  LALT_T(KC_BSPC)       // LALT / Backspace
#define TK_LGUI  MT(MOD_LGUI,_______)  // LGUI / oneshot(LALT) / hold(LALT)
#define TK_RGUI  MT(MOD_RGUI,_______)  // RGUI / oneshot(RALT) / hold(RALT)
#define TK_SESC  S(KC_ESC)
#define TK_SINS  S(KC_INS)
#define TK_WARP  KC_F23  // mouse warp, handled by host OS
#define TK_BSTG  BS_TOGG
#ifndef BS_TOGG
#define BS_TOGG  _______  // don't break build on old versions
#endif
// TODO, maybe, someday: lockable control keys
#define TK_LCLK KC_LCTL
#define TK_RCLK KC_RCTL


#ifndef DONT_USE_EEPROM
// remember the user's preferred settings
typedef union {
    uint32_t raw;
    struct {
        #ifdef HAS_DIPSWITCH
            unsigned switch_off : 2;  // layer to use in "Mac" position (left / toward USB port)
            unsigned switch_on  : 2;  // layer to use in "Win" position (right / away from USB port)
        #endif
        #ifdef HAS_F_ROW
            unsigned f_lock     : 1;  // is F-Lock active?
        #endif
        #ifndef DONT_USE_TK_IUUI
            unsigned dvoriuk        : 1;  // swap U and I in dvorak layer?
        #endif
    };
} user_config_t;
#endif  // ifndef DONT_USE_EEPROM

