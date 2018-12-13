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
#ifndef KEYMAP_BELGIAN_H
#define KEYMAP_BELGIAN_H

#include "keymap.h"

#define BE_LGUI KC_LALT
#define BE_LALT KC_LGUI

// Alt gr
#define BE_ALGR KC_RALT

// Normal characters
// Line 1
#define BE_SUP2	KC_GRV
#define BE_AMP	KC_1
#define BE_EACU	KC_2
#define BE_QUOT	KC_3
#define BE_APOS	KC_4
#define BE_LPRN	KC_5
#define BE_PARA	KC_6
#define BE_EGRV	KC_7
#define BE_EXLM	KC_8
#define BE_CCED	KC_9
#define BE_AGRV	KC_0
#define BE_RPRN	KC_MINS
#define BE_MINS	KC_EQL

// Line 2
#define BE_A    KC_Q
#define BE_Z	  KC_W
#define	BE_CIRC	KC_LBRC
#define BE_DLR	KC_RBRC

// Line 3
#define BE_Q 	  KC_A
#define BE_M 	  KC_SCLN
#define BE_UGRV	KC_QUOT
#define BE_MU 	KC_NUHS

// Line 4
#define BE_LESS	KC_NUBS
#define BE_W	  KC_Z
#define BE_COMM	KC_M
#define BE_SCLN	KC_COMM
#define BE_COLN	KC_DOT
#define BE_EQL	KC_SLSH

// Shifted characters
// Line 1
#define BE_SUP3 KC_TILD
#define BE_1  	LSFT(KC_1)
#define BE_2 	  LSFT(KC_2)
#define BE_3 	  LSFT(KC_3)
#define BE_4 	  LSFT(KC_4)
#define BE_5 	  LSFT(KC_5)
#define BE_6 	  LSFT(KC_6)
#define BE_7 	  LSFT(KC_7)
#define BE_8 	  LSFT(KC_8)
#define BE_9 	  LSFT(KC_9)
#define BE_0 	  LSFT(KC_0)
#define BE_OVRR	KC_UNDS
#define BE_UNDS KC_PLUS

// Line 2
#define BE_UMLT	LSFT(BE_CIRC)
#define BE_PND	LSFT(BE_DLR)

// Line 3
#define	BE_PERC	LSFT(BE_UGRV)

// Line 4
#define BE_GRTR	LSFT(BE_LESS)
#define BE_QUES	LSFT(BE_COMM)
#define BE_DOT	LSFT(BE_SCLN)
#define BE_SLSH	LSFT(BE_COLN)
#define BE_PLUS	LSFT(BE_EQL)

// Alt Gr-ed characters
// Line 1
#define BE_PIPE ALGR(KC_1)
#define BE_AT	  ALGR(KC_2)
#define BE_HASH	ALGR(KC_3)
#define BE_LCBR ALGR(KC_9)
#define BE_RCBR	ALGR(KC_0)

// Line 2
#define BE_EURO	ALGR(KC_E)
#define BE_LSBR ALGR(BE_CIRC)
#define BE_RSBR ALGR(BE_DLR)

// Line 3
#define BE_ACUT ALGR(BE_UGRV)
#define BE_GRV	ALGR(BE_MU)

// Line 4
#define BE_BSLS ALGR(BE_LESS)
#define BE_TILT ALGR(BE_EQL)

#endif
