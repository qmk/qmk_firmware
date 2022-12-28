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

#pragma once

#include "keymap.h"

// Normal characters
#define NO_HALF KC_GRV
#define NO_PLUS KC_MINS
#define NO_ACUT KC_EQL

#define NO_AM KC_LBRC
#define NO_QUOT KC_RBRC // this is the "umlaut" char on Nordic keyboards, Apple layout
#define NO_AE KC_SCLN
#define NO_OSLH KC_QUOT
#define NO_APOS KC_NUHS

#define NO_LESS KC_NUBS
#define NO_MINS KC_SLSH

// Shifted characters
#define NO_SECT LSFT(NO_HALF)
#define NO_QUO2 LSFT(KC_2)
#define NO_BULT LSFT(KC_4)
#define NO_AMPR LSFT(KC_6)
#define NO_SLSH LSFT(KC_7)
#define NO_LPRN LSFT(KC_8)
#define NO_RPRN LSFT(KC_9)
#define NO_EQL LSFT(KC_0)
#define NO_QUES LSFT(NO_PLUS)
#define NO_GRV LSFT(NO_ACUT)

#define NO_CIRC LSFT(NO_QUOT)

#define NO_GRTR LSFT(NO_LESS)
#define NO_SCLN LSFT(KC_COMM)
#define NO_COLN LSFT(KC_DOT)
#define NO_UNDS LSFT(NO_MINS)

// Alt Gr-ed characters
#define NO_AT ALGR(KC_2)
#define NO_PND ALGR(KC_3)
#define NO_DLR ALGR(KC_4)
#define NO_LCBR ALGR(KC_7)
#define NO_LBRC ALGR(KC_8)
#define NO_RBRC ALGR(KC_9)
#define NO_RCBR ALGR(KC_0)
#define NO_PIPE ALGR(KC_NUBS)

#define NO_EURO ALGR(KC_E)
#define NO_TILD ALGR(NO_QUOT)

#define NO_BSLS ALGR(KC_MINS)
#define NO_MU ALGR(KC_M)
