/* Copyright 2016 Sébastien Pérochon
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
#ifndef KEYMAP_BELGIAN_OSX_H
#define KEYMAP_BELGIAN_OSX_H

#include "keymap.h"

// Normal characters
#define BE_A  KC_Q                // a
#define BE_Z  KC_W                // z
#define BE_W  KC_Z                // w
#define BE_Q  KC_A                // a
#define BE_M  KC_SCLN             // m

#define BE_AT KC_NUBS             // @
#define BE_AMP	KC_1              // &
#define BE_EACU	KC_2              // é
#define BE_QUOT	KC_3              // "
#define BE_APOS	KC_4              // '
#define BE_LPRN	KC_5              // (
#define BE_SECT	KC_6              // §
#define BE_EGRV	KC_7              // è
#define BE_EXLM	KC_8              // !
#define BE_CCED	KC_9              // ç
#define BE_AGRV	KC_0              // à
#define BE_RPRN	KC_MINS           // )
#define BE_MINS KC_EQL            // -
#define BE_UGRV KC_QUOT           // ù
#define BE_DLR  KC_RBRC           // $
#define BE_LESS KC_GRV            // <
#define BE_GRV	KC_NUHS           // `
#define BE_CIRC KC_LBRC           // ^
#define BE_COMM	KC_M              // ,
#define BE_SCLN	KC_COMM           // ;
#define BE_COLN	KC_DOT            // :
#define BE_EQL	KC_SLSH           // =

// Shifted characters
#define BE_HASH	LSFT(BE_AT)       // #
#define BE_1 	LSFT(KC_1)          // 1
#define BE_2 	LSFT(KC_2)          // 2
#define BE_3 	LSFT(KC_3)          // 3
#define BE_4 	LSFT(KC_4)          // 4
#define BE_5 	LSFT(KC_5)          // 5
#define BE_6 	LSFT(KC_6)          // 6
#define BE_7 	LSFT(KC_7)          // 7
#define BE_8 	LSFT(KC_8)          // 8
#define BE_9 	LSFT(KC_9)          // 9
#define BE_0 	LSFT(KC_0)          // 0
#define BE_UNDS LSFT(BE_MINS)     // _
#define BE_ASTR	LSFT(BE_DLR)      // *
#define BE_PERC	LSFT(BE_UGRV)     // %
#define BE_PND  LSFT(BE_GRV)      // £
#define BE_UMLT LSFT(BE_CIRC)     // ¨
#define BE_GRTR	LSFT(BE_LESS)     // >
#define BE_QUES	LSFT(BE_COMM)     // ?
#define BE_DOT	LSFT(BE_SCLN)     // .
#define BE_SLSH	LSFT(BE_COLN)     // /
#define BE_PLUS	LSFT(BE_EQL)      // +

// Alted characters
#define BE_BULET LALT(BE_AT)      // •
#define BE_LCBR	LALT(KC_5)        // {
#define BE_RCBR	LALT(BE_RPRN)     // }
#define BE_BULT	LALT(KC_E)        // ê
#define BE_EURO	LALT(BE_DLR)      // €
#define BE_TILD	LALT(KC_N)        // ~

// Shift+Alt-ed characters
#define BE_LBRC	LSFT(LALT(KC_5))    // [
#define BE_RBRC	LSFT(LALT(BE_RPRN)) // ]
#define BE_PIPE	LSFT(LALT(KC_L))    // |
#define BE_BSLS LSFT(LALT(BE_COLN)) // back slash
#define BE_ACUT LALT(LSFT(KC_1))  // ´

// special
#define BE_BRUP KC_PAUS             // brigtness up
#define BE_BRDN	KC_SLCK             // brigtness down

#endif
