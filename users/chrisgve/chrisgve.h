/* Copyright 2021 Christian C. Berclaz
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

// Custom layers
enum CHRISGVE_layers {
    _QWERTY_MAC,
    _MAC_NAV_1,
    _MAC_NAV_2,
    _QWERTY_LINUX,
    _LINUX_NAV_1,
    _LINUX_NAV_2,
    _QWERTY_WIN,
    _WIN_NAV_1,
    _WIN_NAV_2,
    _ADJUST,
    _CONFIG,
    _TMUX,
    _VIM,
};

// Custom keys
enum custom_keycodes {
    TM_CREATE = SAFE_RANGE,
    TM_SEL1,
    TM_SEL2,
    TM_SEL3,
    TM_SEL4,
    TM_SEL5,
    TM_SEL6,
    TM_SEL7,
    TM_SEL8,
};


#define CHAR_MOVE   KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT
#define LINE_MOVE   KC_HOME, KC_PGDN, KC_PGUP, KC_END

#define MAC_NAV     _______, S_SHIFT, _______, M_NAV_2,   _______
#define LINUX_NAV   _______, S_SHIFT, _______, L_NAV_2,   _______
#define WIN_NAV     _______, S_SHIFT, _______, W_NAV_2,   _______

#define TWO_TRS     _______, _______
#define THREE_TRS   TWO_TRS, _______
#define FOUR_TRS    THREE_TRS, _______
#define FIVE_TRS    FOUR_TRS, _______
#define SIX_TRS     FIVE_TRS, _______
#define SEVEN_TRS   SIX_TRS, _______

#define TWO_NOP     XXXXXXX, XXXXXXX
#define THREE_NOP   TWO_NOP, XXXXXXX
#define FOUR_NOP    THREE_NOP, XXXXXXX
#define FIVE_NOP    FOUR_NOP, XXXXXXX
#define SIX_NOP     FIVE_NOP, XXXXXXX
#define SEVEN_NOP   SIX_NOP, XXXXXXX
#define KC_FUNC     KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12

#define CPS_CTL     CTL_T(KC_CAPS)
#define ADJUST      MO(_ADJUST)
#define CONFIG      MO(_CONFIG)
#define TMUX        LT(_TMUX, KC_SCLN)
#define VIM         LT(_VIM, KC_V;)
#define S_SHIFT     SFT_T(KC_S)

#define DF_MAC      DF(_QWERTY_MAC)
#define DF_WIN      DF(_QWERTY_WIN)
#define DF_LINUX    DF(_QWERTY_LINUX)

// Mac only definitions
#define M_NAV_1     LT(_MAC_NAV_1, KC_D)
#define M_NAV_2     MO(_MAC_NAV_2)
#define M_F_WORD    A(KC_RIGHT)
#define M_B_WORD    A(KC_LEFT)

// Linux only definitions
#define L_NAV_1     LT(_LINUX_NAV_1, KC_D)
#define L_NAV_2     MO(_LINUS_NAV_2)
#define L_F_WORD    A(KC_RIGHT)
#define L_B_WORD    A(KC_LEFT)

// Windows only definitions
#define W_NAV_1     LT(_WIN_NAV_1, KC_D)
#define W_NAV_2     MO(_WIN_NAV_2)
#define W_F_WORD    C(KC_RIGHT)
#define W_B_WORD    C(KC_LEFT)


// VIM only definitions


// TMUX only definitions


#define TMUX_SL  TM_SEL1, TM_SEL2, TM_SEL3, TM_SEL4, TM_SEL5, TM_SEL6, TM_SEL7, TM_SEL8

/*
 * Move via D + any of CHAR_MOVE or D + F + any of LINE_MOVE
 * Hidden keys, e.g. function keys, via Fn + Adjust layer
 * Configuation keys via Fn  + RCTL + Config layer
 * TMUX keys via ; + Tmux layer
 * VIM keys via V + VIM layer
 */

/*
 * VIM layer:
 * ----------
 *
 */

/*
 * TMUX layer:
 * -----------
 * C -> TM_CREA
 * 1 -> TM_SEL1
 * 2 -> TM_SEL2
 * 3 -> TM_SEL3
 * 4 -> TM_SEL4
 */

/*
 * Adjust layer:
 * -------------
 *
 * ESC -> GRV
 * 1 to = -> F1 to F12
 * BS -> DEL
 * SPACE -> PLAY
 * H -> PREVIOUS
 * J -> VOLUME DOWN
 * K -> VOLUME UP
 * L -> NEXT
 * M -> MUTE
 * R -> KC_WREF (Web refresh)
 * B -> KC_WBAK (Web back)
 * F -> KC_WFWD (Web forward)
 * S -> KC_WSCH (Web search)
 * R CTRL -> CONFIG
 */

/*
 * Config layer:
 * -------------
 * Tab -> RESET
 * Q -> NK_ON
 * W -> NK_OFF
 * E -> EEP_RST
 * A -> GE_SWAP
 * S -> GE_NORM
 * D -> DEBUG
 * F -> RGB_MOD
 * G -> RGB_HUI
 * H -> RGB_SAI
 * J -> RGB_SPI
 * K -> RGB_VAI
 * L -> RGB_M_B
 * Z -> LAG_SWP
 * X -> LAG_NRM
 * 1 -> MACOS (DF_MAC)
 * 2 -> LINUX (DF_LINUX)
 * 3 -> WIN   (DF_WIN)
 */
