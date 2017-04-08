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
#define ALGR(kc) RALT(kc)
#define NO_ALGR KC_RALT

// Normal characters
#define UK_HASH KC_NUHS

#define UK_BSLS	KC_NUBS

// Shifted characters
#define UK_NOT	LSFT(KC_GRV)
#define UK_QUOT	LSFT(KC_2)
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

#endif
