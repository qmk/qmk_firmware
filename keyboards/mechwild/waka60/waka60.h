/* Copyright 2021 Kyle McCreery
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

#define ___ KC_NO

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
 
 /*
  * KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,             KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  * KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
  * MO(1),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,             KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT, KC_ENT,
  * KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
  * KC_LCTL, KC_LGUI, KC_LALT, MO(1),   KC_SPC,  KC_SPC, KC_SPC,   KC_SPC,  KC_SPC,  MO(1),   KC_RALT, KC_RGUI, KC_RCTL
  */
#define LAYOUT( \
	k00, k01, k02, k03, k04, k05,      k50, k51, k52, k53, k54, k55, \
	k10, k11, k12, k13, k14, k15,      k60, k61, k62, k63, k64, k65, \
	k20, k21, k22, k23, k24, k25,      k70, k71, k72, k73, k74, k75, \
	k30, k31, k32, k33, k34, k35, k36, k80, k81, k82, k83, k84, k85, \
	k40, k41, k42, k43, k44, k45, k46, k90, k91, k92, k93, k94, k95  \
) { \
    { k00, k01, k02, k03, k04, k05, ___}, \
    { k10, k11, k12, k13, k14, k15, ___}, \
    { k20, k21, k22, k23, k24, k25, ___}, \
    { k30, k31, k32, k33, k34, k35, k36}, \
    { k40, k41, k42, k43, k44, k45, k46}, \
	{ k50, k51, k52, k53, k54, k55, ___}, \
	{ k60, k61, k62, k63, k64, k65, ___}, \
	{ k70, k71, k72, k73, k74, k75, ___}, \
	{ k80, k81, k82, k83, k84, k85, ___}, \
	{ k90, k91, k92, k93, k94, k95, ___}  \
}
