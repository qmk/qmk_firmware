/* Copyright 2020 kb-elmo<mail@elmo.space>
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

#define LAYOUT_all(\
   k10, k00,   k11, k01, k12, k02, k13, k03, k14, k04, k15, k05, k16, k06, k17, k07, k18,   k08, k19, \
   k30, k20,   k31, k21, k32, k22, k33, k23, k34, k24, k35, k25, k36, k26, k37, k27, k38,   k28, k39, \
   k40, k50,   k41, k51, k42, k52, k43, k53, k44, k54, k45, k55, k46, k56,    k47,   k58,   k48, k59, \
   k60, k70,      k61,   k71, k62, k72, k63, k73, k64, k74, k65, k75, k66, k76, k67, k78,   k68, k79, \
   k80, k90,   k81, k91, k82,                k93,                     k86, k96, k87, k98,   k88, k99  \
) { \
   {k00, k01, k02, k03, k04, k05, k06, k07, k08, ___}, \
   {k10, k11, k12, k13, k14, k15, k16, k17, k18, k19}, \
   {k20, k21, k22, k23, k24, k25, k26, k27, k28, ___}, \
   {k30, k31, k32, k33, k34, k35, k36, k37, k38, k39}, \
   {k40, k41, k42, k43, k44, k45, k46, k47, k48, ___}, \
   {k50, k51, k52, k53, k54, k55, k56, ___, k58, k59}, \
   {k60, k61, k62, k63, k64, k65, k66, k67, k68, ___}, \
   {k70, k71, k72, k73, k74, k75, k76, ___, k78, k79}, \
   {k80, k81, k82, ___, ___, ___, k86, k87, k88, ___}, \
   {k90, k91, ___, k93, ___, ___, k96, ___, k98, k99}  \
}
