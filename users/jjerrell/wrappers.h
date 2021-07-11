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

// clang-format off
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
        K01, K02, K03, K04, K05,     K08, K09, K0A, K0B, K0C, \
        K11, K12, K13, K14, K15,     K18, K19, K1A, K1B, K1C, \
        K21, K22, K23, K24, K25,     K28, K29, K2A, K2B, K2C  \
    ) WRAPPER_ortho_4x12( \
        K01,     K02,     K03,     K04,                K05 ,       XXXXXXX ,  XXXXXXX, K08,                 K09,     K0A,     K0B,     K0C,      \
        K11,     K12,     K13,     K14,                K15 ,       XXXXXXX ,  XXXXXXX, K18,                 K19,     K1A,     K1B,     K1C,      \
        K21,     K22,     K23,     K24,                K25 ,       XXXXXXX ,  XXXXXXX, K28,                 K29,     K2A,     K2B,     K2C,      \
    ____________________________________________________________PLANCK_VERBOSE_BOTTOM_ROW_____________________________________________________________ )

/**
 * Shifted Key conflicts:
 * K12, K13, K14, K19, K1A, K1B, K21, K2C
 */
#   define WRAPPER_planck_base( \
        K01, K02, K03, K04, K05,     K08, K09, K0A, K0B, K0C, \
        K11, K12, K13, K14, K15,     K18, K19, K1A, K1B, K1C, \
        K21, K22, K23, K24, K25,     K28, K29, K2A, K2B, K2C  \
    ) WRAPPER_ortho_4x12( \
                K01 ,       K02 ,       K03 ,       K04 ,                K05 ,      XXXXXXX , XXXXXXX, K08,                 K09 ,       K0A ,       K0B ,       K0C,        \
                K11 , SFT_T(K12), GUI_T(K13), ALT_T(K14),                K15 ,      XXXXXXX , XXXXXXX, K18,                 ALT_T(K19), GUI_T(K1A), SFT_T(K1B), K1C,        \
          CTL_T(K21),       K22 ,       K23 ,       K24 ,                K25 ,      XXXXXXX , XXXXXXX, K28,                 K29 ,       K2A ,       K2B ,       CTL_T(K2C), \
                ____________________________________________________________PLANCK_VERBOSE_BOTTOM_ROW_____________________________________________________________   )

#   define WRAPPER_planck_mods( \
        K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, \
        K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, \
        K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, \
        K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C  \
    ) WRAPPER_ortho_4x12( \
                K01 ,       K02 ,       K03 ,       K04 ,            K05 ,         K06 ,     K07, K08,             K09 ,       K0A ,       K0B ,       K0C,        \
                K11 , SFT_T(K12), GUI_T(K13), ALT_T(K14),            K15 ,         K16 ,     K17, K18,             ALT_T(K19), GUI_T(K1A), SFT_T(K1B), K1C,        \
          CTL_T(K21),       K22 ,       K23 ,       K24 ,            K25 ,         K26 ,     K27, K28,             K29 ,       K2A ,       K2B ,       CTL_T(K2C), \
                K31,        K32 ,       K33 ,       K34 , LT(_LOWER, K35),   SFT_T(K36), XXXXXXX, LT(_RAISE, K38), K39 ,       K3A ,       K3B,        K3C         )



// These macros are used when defining layouts in keymap.c
#   define LAYOUT_planck_base(...)    WRAPPER_planck_base(__VA_ARGS__)
#   define LAYOUT_planck_common(...)  WRAPPER_planck_common(__VA_ARGS__)
#   define LAYOUT_planck_mods(...)    WRAPPER_planck_mods(__VA_ARGS__)
#elif (defined(KEYBOARD_moonlander))
/**
 * ( \
        k00, k01, k02, k03, k04, k05, k06,   k60, k61, k62, k63, k64, k65, k66, \
        k10, k11, k12, k13, k14, k15, k16,   k70, k71, k72, k73, k74, k75, k76, \
        k20, k21, k22, k23, k24, k25, k26,   k80, k81, k82, k83, k84, k85, k86, \
        k30, k31, k32, k33, k34, k35,             k91, k92, k93, k94, k95, k96, \
        k40, k41, k42, k43, k44,      k53,   kb3,      ka2, ka3, ka4, ka5, ka6, \
                            k50, k51, k52,   kb4, kb5, kb6 \
    ) \
 */
#   define WRAPPER_moonlander(...)    LAYOUT_moonlander(__VA_ARGS__)
#   define WRAPPER_moonlander_common( \
             k11, k12, k13, k14, k15,             k71, k72, k73, k74, k75, \
             k21, k22, k23, k24, k25,             k81, k82, k83, k84, k85, \
             k31, k32, k33, k34, k35,             k91, k92, k93, k94, k95  \
    ) WRAPPER_moonlander( \
        k00, k01, k02, k03, k04, k05, k06,   k60, k61, k62, k63, k64, k65, k66, \
        k10, k11, k12, k13, k14, k15, k16,   k70, k71, k72, k73, k74, k75, k76, \
        k20, k21, k22, k23, k24, k25, k26,   k80, k81, k82, k83, k84, k85, k86, \
        k30, k31, k32, k33, k34, k35,             k91, k92, k93, k94, k95, k96, \
        k40, k41, k42, k43, k44,      k53,   kb3,      ka2, ka3, ka4, ka5, ka6, \
                LT(_LOWER, k50), k51, k52,   kb4, kb5, LT(_RAISE, kb6) \
    )
#endif // END Keyboard specific wrapper defines
/**
 * Alpha-area key wrappers for portability
 */

// Workman
#define __________________WORKMN_L1__________________   KC_Q, KC_D, KC_R, KC_W, KC_B
#define __________________WORKMN_L2__________________   KC_A, KC_S, KC_H, KC_T, KC_G
#define __________________WORKMN_L3__________________   KC_Z, KC_X, KC_M, KC_C, KC_V

#define __________________WORKMN_R1__________________   KC_J, KC_F, KC_U,    KC_P,   KC_SCLN
#define __________________WORKMN_R2__________________   KC_Y, KC_N, KC_E,    KC_O,   KC_I
#define __________________WORKMN_R3__________________   KC_K, KC_L, KC_COMM, KC_DOT, KC_SLSH

#if (defined(KEYBOARD_planck_ez))
#   define ____________________________________________________________PLANCK_VERBOSE_BOTTOM_ROW_____________________________________________________________ \
           KC_LSFT, KC_LEAD, KC_CCCV, KC_MEH, LT(_LOWER, KC_BSPC), SFT_T(KC_SPC), XXXXXXX, LT(_RAISE, KC_ENT),  KC_HYPR,    RGB_TOG,    RGB_IDL,    LED_LEVEL
#endif
// Lower
#define __________________LOWER_L1___________________   KC_PGUP, KC_TAB,  KC_UP,   KC_ENT,  KC_PGDN
#define __________________LOWER_L2___________________   KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT,  KC_END
#define __________________LOWER_L3___________________   KC_ESC,  KC_BSPC, XXXXXXX, KC_DEL,  XXXXXXX

#define __________________LOWER_R1___________________   XXXXXXX, KC_7, KC_8,   KC_9,    KC_ASTR
#define __________________LOWER_R2___________________   XXXXXXX, KC_4, KC_5,   KC_6,    KC_SLSH
#define __________________LOWER_R3___________________   XXXXXXX, KC_1, KC_2,   KC_3,    KC_MINS
//  Relevant keys: ->                                            KC_0, KC_DOT, KC_COMM, KC_PLUS <- pretty much the only reasons I can't always apply common or base
#if (defined(KEYBOARD_planck_ez))
#   define _________________________________________PLANCK_LOWER_BOTTOM_ROW_________________________________________ \
           KC_LSFT, KC_LEAD, KC_CCCV, KC_MEH,  KC_BSPC,  KC_SPC, XXXXXXX,   KC_ENT, KC_0, KC_DOT, KC_COMM, LED_LEVEL
// TODO: It would be cool to find a way to use a function or something to apply the bottom row with optional left/right varargs. I'm completely unsure if this 
//       language can support something like that though.
#endif // KEYBOARD_planck_ez
 
// Raise
#define __________________RAISE_L1___________________   KC_PERC, KC_UNDS, KC_LBRC, KC_RBRC, KC_CIRC
#define __________________RAISE_L2___________________   KC_BSLS, KC_SLSH, KC_LCBR, KC_RCBR, KC_ASTR
#define __________________RAISE_L3___________________   KC_HASH, KC_DLR , KC_PIPE, KC_TILD, KC_GRV

#define __________________RAISE_R1___________________   KC_EXLM, KC_LABK, KC_RABK, KC_EQL , KC_COLN
#define __________________RAISE_R2___________________   KC_QUES, KC_LPRN, KC_RPRN, KC_MINS, KC_SCLN
#define __________________RAISE_R3___________________   KC_AT,   KC_DQUO, KC_QUOT, KC_PLUS, KC_AMPR

// Adjust
#define __________________ADJUST_L1__________________   KC_MAKE,       DEBUG,     RESET, TERM_ON, TERM_OFF
#define __________________ADJUST_L2__________________   KC__MUTE, KC__VOLDOWN, KC__VOLUP, KC_MPLY,  KC_MNXT
#define __________________ADJUST_L3__________________   KC_VRSN,       AU_ON,    AU_OFF, CG_SWAP,  CG_NORM

#define __________________ADJUST_R1__________________   MU_MOD, MU_ON,   MU_OFF,  MI_ON,   MI_OFF
#define __________________ADJUST_R2__________________   MUV_IN, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD
#define __________________ADJUST_R3__________________   MUV_DE, RGB_TOG, RGB_MOD, RGB_VAI, RGB_VAD
// clang-format on
