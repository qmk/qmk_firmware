/* Copyright 2017 Andreas Lindhé
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

#ifndef KEYMAP_SWEDISH_H
#define KEYMAP_SWEDISH_H

#include "keymap.h"

// Normal characters
#define SE_HALF KC_GRV
#define SE_PLUS KC_MINS
#define SE_ACUT KC_EQL

#define SE_AM KC_LBRC
#define SE_QUOT KC_RBRC  // this is the "umlaut" char on Nordic keyboards, Apple layout
#define SE_AE KC_QUOT    // ä
#define SE_OSLH KC_SCLN  // ö
#define SE_APOS KC_NUHS

#define SE_LESS KC_NUBS
#define SE_MINS KC_SLSH

// Shifted characters
#define SE_SECT LSFT(SE_HALF)
#define SE_QUO2 LSFT(KC_2)
#define SE_BULT LSFT(KC_4)
#define SE_AMPR LSFT(KC_6)
#define SE_SLSH LSFT(KC_7)
#define SE_LPRN LSFT(KC_8)
#define SE_RPRN LSFT(KC_9)
#define SE_EQL LSFT(KC_0)
#define SE_QUES LSFT(SE_PLUS)
#define SE_GRV LSFT(SE_ACUT)

#define SE_CIRC LSFT(KC_RBRC)  // ^

#define SE_GRTR LSFT(SE_LESS)
#define SE_SCLN LSFT(KC_COMM)
#define SE_COLN LSFT(KC_DOT)
#define SE_UNDS LSFT(SE_MINS)

// Alt Gr-ed characters
#define SE_AT ALGR(KC_2)
#define SE_PND ALGR(KC_3)
#define SE_DLR ALGR(KC_4)
#define SE_LCBR ALGR(KC_7)
#define SE_LBRC ALGR(KC_8)
#define SE_RBRC ALGR(KC_9)
#define SE_RCBR ALGR(KC_0)
#define SE_PIPE ALGR(KC_NUBS)

#define SE_EURO ALGR(KC_E)
#define SE_TILD ALGR(SE_QUOT)

#define SE_BSLS ALGR(KC_MINS)
#define SE_MU ALGR(KC_M)

#define SE_AA KC_LBRC          // å
#define SE_ASTR LSFT(KC_BSLS)  // *

// Norwegian unique MAC characters (not vetted for Swedish)
#define SE_ACUT_MAC KC_EQL            // =
#define SE_APOS_MAC KC_NUBS           // '
#define SE_AT_MAC KC_BSLS             // @
#define SE_BSLS_MAC ALGR(LSFT(KC_7))  // '\'
#define SE_DLR_MAC ALGR(KC_4)         // $
#define SE_GRV_MAC ALGR(SE_BSLS)      // `
#define SE_GRTR_MAC LSFT(KC_GRV)      // >
#define SE_LCBR_MAC ALGR(LSFT(KC_8))  // {
#define SE_LESS_MAC KC_GRV            // <
#define SE_PIPE_MAC ALGR(KC_7)        // |
#define SE_RCBR_MAC ALGR(LSFT(KC_9))  // }

#endif
