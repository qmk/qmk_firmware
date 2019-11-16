/* Copyright 2019 Matthew Lyon
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

enum {
    _QWERTY,
    _NAVNUM,
    _SYMBOL,
    _FUNCT,
};

// == Thumbs
// left hand
#define ESC_HYP MT(MOD_HYPR, KC_ESC)
#define TAB_NUM LT(_NAVNUM, KC_TAB)
#define SPC_SFT MT(MOD_LSFT, KC_SPC)
#define ENT_SYM LT(_SYMBOL, KC_ENT)


// right hand
#define SPC_SFT MT(MOD_LSFT, KC_SPC)
#define BSP_SYM LT(_SYMBOL, KC_BSPC)
#define DEL_WRP MT(MOD_LCTL | MOD_LALT | MOD_LGUI, KC_DEL)

#define NAVLOCK TG(_NAVNUM)
#define SYMLOCK TG(_SYMBOL)


// == QWERTY
// left hand home row
#define A_CTRL  MT(MOD_LCTL, KC_A)
#define S_ALT   MT(MOD_LALT, KC_S)
#define D_GUI   MT(MOD_LGUI, KC_D)
#define F_SHFT  MT(MOD_LSFT, KC_F)
// left hand aux
#define W_CTRL MT(MOD_LCTL, KC_W)
#define E_ALT  MT(MOD_LALT, KC_E)
#define R_GUI  MT(MOD_LGUI, KC_R)

// right hand home row
#define J_SHFT  MT(MOD_RSFT, KC_J)
#define K_GUI   MT(MOD_RGUI, KC_K)
#define L_ALT   MT(MOD_RALT, KC_L)
#define MINSCTL MT(MOD_RCTL, KC_MINS)
// right hand aux
#define U_GUI   MT(MOD_RGUI, KC_U)
#define I_ALT   MT(MOD_RALT, KC_I)
#define O_CTRL  MT(MOD_RCTL, KC_O)

// == OS X default keys
// movement by word
#define BWORD   LALT(KC_LEFT)
#define FWORD   LALT(KC_RIGHT)

// gui navigation
#define NWIN    LGUI(KC_GRV)        // Next Window
#define PWIN    LGUI(LSFT(KC_GRV))  // Prev Window
#define NTAB    LGUI(LSFT(KC_RBRC)) // Next Tab
#define PTAB    LGUI(LSFT(KC_LBRC)) // Prev Tab
#define NAVBACK LGUI(KC_LBRC)       // Navigate Forward
#define NAVFWD  LGUI(KC_RBRC)       // Navigate Back

// my personal mappings to window manager commands
#define XALLWIN HYPR(KC_F14)
#define XDESKTP HYPR(KC_F15)
#define XNXTSPC HYPR(KC_F16)
#define XPRVSPC HYPR(KC_F17)
#define XNOTIFY HYPR(KC_F18)

// == UNDERGLOW
#ifdef RGBLIGHT_ENABLE
#define HSV_CAPS     60, 255, 255
#define HSV_DEFAULT  30, 255, 255
#define HSV_SYMBOL   18, 255, 255
#define HSV_NAVNUM  250, 255, 255
#define HSV_FUNCT   238, 255, 255
#define HSV_RESET   180, 255, 255
#endif

#endif

