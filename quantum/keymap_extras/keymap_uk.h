/* Copyright 2015-2016 Jack Humbert
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
#ifndef KEYMAP_UK_H
#define KEYMAP_UK_H

#include "keymap.h"

// Alt gr
#define UK_ALGR KC_RALT

// Normal characters
#define UK_HASH KC_NUHS
#define UK_BSLS	KC_NUBS

// Shifted characters
#define UK_NOT	LSFT(KC_GRV)
#define UK_DQUO	LSFT(KC_2)
#define UK_PND	LSFT(KC_3)
#define UK_AT	LSFT(KC_QUOT)
#define UK_TILD	LSFT(KC_NUHS)
#define UK_PIPE	LSFT(KC_NUBS)

// Alt Gr-ed characters
#define UK_BRKP	ALGR(KC_GRV)
#define UK_EURO	ALGR(KC_4)
#define UK_EACT	ALGR(KC_E)
#define UK_UACT	ALGR(KC_U)
#define UK_IACT ALGR(KC_I)
#define UK_OACT ALGR(KC_O)
#define UK_AACT ALGR(KC_A)

// Duplicate US keyboard so that we don't have to use it
#define UK_A KC_A
#define UK_B KC_B
#define UK_C KC_C
#define UK_D KC_D
#define UK_E KC_E
#define UK_F KC_F
#define UK_G KC_G
#define UK_H KC_H
#define UK_I KC_I
#define UK_J KC_J
#define UK_K KC_K
#define UK_L KC_L
#define UK_M KC_M
#define UK_N KC_N
#define UK_O KC_O
#define UK_P KC_P
#define UK_Q KC_Q
#define UK_R KC_R
#define UK_S KC_S
#define UK_T KC_T
#define UK_U KC_U
#define UK_V KC_V
#define UK_W KC_W
#define UK_X KC_X
#define UK_Y KC_Y
#define UK_Z KC_Z

#define UK_1 KC_1
#define UK_2 KC_2
#define UK_3 KC_3
#define UK_4 KC_4
#define UK_5 KC_5
#define UK_6 KC_6
#define UK_7 KC_7
#define UK_8 KC_8
#define UK_9 KC_9
#define UK_0 KC_0

#define UK_F1 KC_F1
#define UK_F2 KC_F2
#define UK_F3 KC_F3
#define UK_F4 KC_F4
#define UK_F5 KC_F5
#define UK_F6 KC_F6
#define UK_F7 KC_F7
#define UK_F8 KC_F8
#define UK_F9 KC_F9
#define UK_F10 KC_F10
#define UK_F11 KC_F11
#define UK_F12 KC_F12
#define UK_F13 KC_F13
#define UK_F14 KC_F14
#define UK_F15 KC_F15
#define UK_F16 KC_F16
#define UK_F17 KC_F17
#define UK_F18 KC_F18
#define UK_F19 KC_F19
#define UK_F20 KC_F20
#define UK_F21 KC_F21
#define UK_F22 KC_F22
#define UK_F23 KC_F23
#define UK_F24 KC_F24

#define UK_SCLN KC_SCLN
#define UK_COMM KC_COMM
#define UK_DOT KC_DOT
#define UK_SLSH KC_SLSH
#define UK_EXLM KC_EXLM
#define UK_UNDS KC_UNDS
#define UK_MINS KC_MINS
#define UK_LCBR KC_LCBR
#define UK_RCBR KC_RCBR
#define UK_DLR KC_DLR
#define UK_PERC KC_PERC
#define UK_PLUS KC_PLUS
#define UK_EQL KC_EQL
#define UK_LPRN KC_LPRN
#define UK_RPRN KC_RPRN
#define UK_CIRC KC_CIRC
#define UK_AMPR KC_AMPR
#define UK_LABK KC_LABK
#define UK_LBRC KC_LBRC
#define UK_RBRC KC_RBRC
#define UK_RABK KC_RABK
#define UK_GRV KC_GRV
#define UK_ASTR KC_ASTR
#define UK_QUOT KC_QUOT

#define UK_P1 KC_P1
#define UK_P2 KC_P2
#define UK_P3 KC_P3
#define UK_P4 KC_P4
#define UK_P5 KC_P5
#define UK_P6 KC_P6
#define UK_P7 KC_P7
#define UK_P8 KC_P8
#define UK_P9 KC_P9
#define UK_P0 KC_P0
#define UK_PDOT KC_PDOT
#define UK_PCMM KC_PCMM
#define UK_PSLS KC_PSLS
#define UK_PAST KC_PAST
#define UK_PMNS KC_PMNS
#define UK_PPLS KC_PPLS
#define UK_PEQL KC_PEQL
#define UK_PENT KC_PENT

#define UK_TAB KC_TAB
#define UK_ENT KC_ENT
#define UK_LSFT KC_LSFT
#define UK_LCTL KC_LCTL
#define UK_LALT KC_LALT
#define UK_LGUI KC_LGUI
#define UK_SPC KC_SPC
#define UK_DEL KC_DEL
#define UK_BSPC KC_BSPC
#define UK_RSFT KC_RSFT
#define UK_RCTL KC_RCTL
#define UK_RALT KC_RALT
#define UK_RGUI KC_RGUI
#define UK_ESC KC_ESC
#define UK_PSCR KC_PSCR
#define UK_SLCK KC_SLCK
#define UK_PAUS KC_PAUS
#define UK_INS KC_INS
#define UK_HOME KC_HOME
#define UK_PGUP KC_PGUP
#define UK_END KC_END
#define UK_PGDN KC_PGDN
#define UK_LEFT KC_LEFT
#define UK_RGHT KC_RGHT
#define UK_UP KC_UP
#define UK_DOWN KC_DOWN

#endif
