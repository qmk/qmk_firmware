// clang-format off
// Copyright (C) 2021 Jerrell, Jacob <@jjerrell>
// 
// This file is part of qmk_firmware.
// 
// qmk_firmware is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// qmk_firmware is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with qmk_firmware.  If not, see <http://www.gnu.org/licenses/>.
#pragma once
#include "jjerrell.h"

#if (!defined(LAYOUT) && defined(KEYMAP))
#    define LAYOUT KEYMAP
#endif

#if (defined(KEYBOARD_planck_ez))
/**
 * Basic Planck EZ Wrapper to expand "block" defines before sending 
 * to LAYOUT_ortho_4x12
 */
#   define WRAPPER_ortho_4x12(...) LAYOUT_ortho_4x12(__VA_ARGS__)

#   define WRAPPER_planck_common( \
        K01, K02, K03, K04, K05,           K08, K09, K0A, K0B, K0C, \
        K11, K12, K13, K14, K15,           K18, K19, K1A, K1B, K1C, \
        K21, K22, K23, K24, K25,           K28, K29, K2A, K2B, K2C, \
                            K35,    K36,    K38                     \
    ) WRAPPER_ortho_4x12( \
        K01,     K02,     K03,     K04,     K05, XXXXXXX,  XXXXXXX,      K08,      K09,     K0A,     K0B,     K0C, \
        K11,     K12,     K13,     K14,     K15, XXXXXXX,  XXXXXXX,      K18,      K19,     K1A,     K1B,     K1C, \
        K21,     K22,     K23,     K24,     K25, XXXXXXX,  XXXXXXX,      K28,      K29,     K2A,     K2B,     K2C, \
    KC_LSFT, KC_LEAD, XXXXXXX,  KC_MEH,     K35,     K36,  XXXXXXX,      K38,  KC_HYPR, XXXXXXX, XXXXXXX, BACKLIT  \
    )

#   define WRAPPER_planck_mods( \
        K01, K02, K03, K04, K05,           K08, K09, K0A, K0B, K0C, \
        K11, K12, K13, K14, K15,           K18, K19, K1A, K1B, K1C, \
        K21, K22, K23, K24, K25,           K28, K29, K2A, K2B, K2C, \
                            K35,    K36,    K38                     \
    ) WRAPPER_planck_common( \
                K01 ,       K02 ,       K03 ,       K04 , K05,            K08 ,       K09 ,       K0A ,       K0B ,       K0C , \
                K11 , SFT_T(K12), GUI_T(K13), ALT_T(K14), K15,            K18 , ALT_T(K19), GUI_T(K1A), SFT_T(K1B),       K1C , \
          CTL_T(K21),       K22 ,       K23 ,       K24 , K25,            K28 ,       K29 ,       K2A ,       K2B , CTL_T(K2C), \
                                                          K35,    K36,    K38                                                   \
        )

#   define LAYOUT_planck_common(...)    WRAPPER_planck_common(__VA_ARGS__)
#   define LAYOUT_planck_mods(...)      WRAPPER_planck_mods(__VA_ARGS__)
#endif // KEYBOARD_planck_ez
/**
 * Alpha
 */

#define __________________WORKMN_L1__________________   KC_Q, KC_D, KC_R, KC_W, KC_B
#define __________________WORKMN_L2__________________   KC_A, KC_S, KC_H, KC_T, KC_G
#define __________________WORKMN_L3__________________   KC_Z, KC_X, KC_M, KC_C, KC_V

#define __________________WORKMN_R1__________________   KC_J, KC_F, KC_U,    KC_P,   KC_SCLN
#define __________________WORKMN_R2__________________   KC_Y, KC_N, KC_E,    KC_O,   KC_I
#define __________________WORKMN_R3__________________   KC_K, KC_L, KC_COMM, KC_DOT, KC_SLSH

// clang-format on