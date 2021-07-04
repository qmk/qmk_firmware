/**
 * Copyright (C) 2021 Jerrell, Jacob <@jjerrell>
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * 
 * This file is part of qmk_firmware.
 * 
 * qmk_firmware is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * qmk_firmware is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with qmk_firmware.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once
#include "jjerrell.h"

/****************************** Layout Blocks *******************************/

/**
 * Numerics
 */

#define __________________NUMS__LHS__________________   KC_1, KC_2, KC_3, KC_4, KC_5
#define __________________NUMS__RHS__________________   KC_6, KC_7, KC_8, KC_9, KC_0

#define __________________SYMB__LHS__________________   KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC
#define __________________SYMB__RHS__________________   KC_CIRC, KC_AMPR, KC_ASTR, KC_MINS, KC_EQL

/**
 * Alpha
 */

#define __________________WORKMN_L1__________________   KC_Q, KC_D, KC_R, KC_W, KC_B
#define __________________WORKMN_L2__________________   KC_A, KC_S, KC_H, KC_T, KC_G
#define __________________WORKMN_L3__________________   KC_Z, KC_X, KC_M, KC_C, KC_V

#define __________________WORKMN_R1__________________   KC_J, KC_F, KC_U,    KC_P,   KC_SCLN
#define __________________WORKMN_R2__________________   KC_Y, KC_N, KC_E,    KC_O,   KC_I
#define __________________WORKMN_R3__________________   KC_K, KC_L, KC_COMM, KC_DOT, KC_SLSH

#define __________________QWERTY_L1__________________   KC_Q, KC_W, KC_E, KC_R, KC_T
#define __________________QWERTY_L2__________________   KC_A, KC_S, KC_D, KC_F, KC_G
#define __________________QWERTY_L3__________________   KC_Z, KC_X, KC_C, KC_V, KC_B

#define __________________QWERTY_R1__________________   KC_Y, KC_U, KC_I,    KC_O,   KC_P
#define __________________QWERTY_R2__________________   KC_H, KC_J, KC_K,    KC_L,   KC_SCLN
#define __________________QWERTY_R3__________________   KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH

/************************* Keyboard Layout Wrappers *************************/

#if (!defined(LAYOUT) && defined(KEYMAP))
#    define LAYOUT KEYMAP
#endif

/**
 *  Moonlander
 */
#define LAYOUT_moonlander_wrapper(...)  LAYOUT_moonlander(__VA_ARGS__)

#define LAYOUT_moonlander_overlay( \
        k00, k01, k02, k03, k04, k05, k06,   k60, k61, k62, k63, k64, k65, k66, \
        k10, k11, k12, k13, k14, k15, k16,   k70, k71, k72, k73, k74, k75, k76, \
        k20, k21, k22, k23, k24, k25, k26,   k80, k81, k82, k83, k84, k85, k86, \
        k30, k31, k32, k33, k34, k35,             k91, k92, k93, k94, k95, k96, \
        k40, k41, k42, k43, k44,      k53,   kb3,      ka2, ka3, ka4, ka5, ka6, \
                            k50, k51, k52,   kb4, kb5, kb6 \
    ) \
    LAYOUT_moonlander_wrapper( \
        k00,       k01,       k02,       k03,       k04,       k05,       k06, /* LHS / RHS */ k60,       k61,        k62,       k63,       k64,        k65,       k66, \
        k10,       k11,       k12,       k13,       k14,       k15,       k16, /* LHS / RHS */ k70,       k71,        k72,       k73,       k74,        k75,       k76, \
        k20,       k21,SFT_T(k22),GUI_T(k23),ALT_T(k24),       k25,       k26, /* LHS / RHS */ k80,       k81,RALT_T(k82),GUI_T(k83),SFT_T(k84),        k85,       k86, \
        k30,CTL_T(k31),       k32,       k33,       k34,       k35,            /* LHS / RHS */            k91,        k92,       k93,       k94,RCTL_T(k95),       k96, \
        k40,       k41,       k42,       k43,       k44,                  k53, /* LHS / RHS */ kb3,                   ka2,       ka3,       ka4,        ka5,       ka6, \
                                            HYPR_T(k50),       k51,       k52, /* LHS / RHS */ kb4,       kb5, MEH_T(kb6)                                               \
    )


/**
 * Ergodox
 */



/**
 * Planck
 */

