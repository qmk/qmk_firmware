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

//#ifdef KEYBOARD_mechwild_obe_eeprom
//#    include "eeprom.h"
//#endif

#include "quantum.h"

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT( \
    k55, k54, k53, k52, k51, k50, k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, \
    k65, k59, k58, k57, k56, k10, k11, k12, k13, k14, k15, k16, k17, k18,      k19, \
    k64, k69, k68, k63, k20, k21, k22, k23, k24, k25, k26, k27, k28,           k29, \
         k62, k60, k67, k66, k30, k31, k32, k33, k34, k35, k36, k37, k38,      k39, \
         k61, k40, k41,      k42, k43,      k44,      k45, k46, k47, k48,      k49  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09 }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19 }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29 }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39 }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48, k49 }, \
	{ k50, k51, k52, k53, k54, k55, k56, k57, k58, k59 }, \
	{ k60, k61, k62, k63, k64, k65, k66, k67, k68, k69 }  \
}
