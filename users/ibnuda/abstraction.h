/* Copyright 2021 Ibnu D. Aji
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
#include "quantum.h"

enum {
    _BASE,
    _LOWER,
    _RAISE,
    _ADJUST,
};

// keycode abstraction
// ABC:
//  A: L  = left
//     R  = right
//  B: U  = upper row
//     M  = middle row
//     L  = lower row
//  C: P  = pinky finger
//     R  = ring finger
//     M  = middle finger
//     I  = index finger
//     II = inner index finger
#define LUP  KC_Q
#define LUR  KC_V
#define LUM  KC_C
#define LUI  KC_P
#define LUII KC_B
#define LMP  KC_R
#define LMR  KC_S
#define LMM  KC_T
#define LMI  KC_H
#define LMII KC_D
#define LLP  KC_QUOT
#define LLR  KC_J
#define LLM  KC_G
#define LLI  KC_K
#define LLII KC_X

#define RUP  KC_Z
#define RUR  KC_Y
#define RUM  KC_U
#define RUI  KC_L
#define RUII KC_DOT
#define RMP  KC_O
#define RMR  KC_I
#define RMM  KC_A
#define RMI  KC_N
#define RMII KC_F
#define RLP  KC_SLSH
#define RLR  KC_SCLN
#define RLM  KC_W
#define RLI  KC_M
#define RLII KC_COMM


// thumb keys.
#define TRAISE   TG(_RAISE)
#define AL_ENT   ALT_T(KC_ENT)
#define SF_BSPC  SFT_T(KC_BSPC)
#define CT_ESC   CTL_T(KC_ESC)

// home row mods.
#define CTLR    LCTL_T(LMR)
#define CTRR    RCTL_T(RMR)
#define CT_LEFT LCTL_T(KC_LEFT)
#define CT_SIX  RCTL_T(KC_6)

#define SHLP    LSFT_T(LMP)
#define SHRP    RSFT_T(RMP)
#define SH_HASH LSFT_T(KC_HASH)
#define SH_ZERO RSFT_T(KC_0)

#define ALLM    LALT_T(LMM)
#define ALRM    RALT_T(RMM)
#define AL_DOWN LALT_T(KC_DOWN)
#define AL_FIVE RALT_T(KC_5)

#define GULII   RGUI_T(LMII)
#define GURII   LGUI_T(RMII)
#define GU_DLR  RGUI_T(KC_DLR)
#define GU_EQL  LGUI_T(KC_EQL)

// layer toggle.
#define LW_E     LT(_LOWER, KC_E)
#define RS_SPC   LT(_RAISE, KC_SPC)

#define ADDDD    MO(_ADJUST)

// common shortcuts for windows and linux that i use.
#define NXTTAB LCTL(KC_PGDN)
#define PRVTAB LCTL(KC_PGUP)
#define UPTAB  LCTL(LSFT(KC_PGUP))
#define DNTAB  LCTL(LSFT(KC_PGDN))
#define NXTWIN LALT(KC_TAB)
#define PRVWIN LALT(LSFT(KC_TAB))
#define CALDL  LCTL(LALT(KC_DEL))
#define TSKMGR LCTL(LSFT(KC_ESC))
#define EXPLR  LGUI(KC_E)
#define LCKGUI LGUI(KC_L)
#define CONPST LSFT(KC_INS)
#define CLSGUI LALT(KC_F4)
