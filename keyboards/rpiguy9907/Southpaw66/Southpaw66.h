 /* Copyright 2020 gooberpsycho
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

// The first section contains all of the arguments
// The second converts the arguments into a two-dimensional array
#define LAYOUT( \
  k00, k10, k20, k30, k40, k50, k60, k01, k11, k21, k31, k41, k51, k61, k02,    \
  k12, k22, k32, k42, k52, k62, k03, k13, k23, k33, k43, k53, k63, k04, k14,    \
  k24, k34, k44, k54, k64, k05, k15, k25, k35, k45, k55, k65, k06,              \
  k16, k26, k36, k46, k56, k66, k07, k17, k27, k37, k47, k57, k67,              \
  k08, k18, k28, k38, k48, k58, k68, k09, k19                                   \
) \
{ \
  {k00,   k10,   k20,   k30,   k40,   k50,   k60,   k01,   k11,   k21}, \
  {k31,   k41,   k51,   k61,   k02,   k12,   k22,   k32,   k42,   k52}, \
  {k62,   k03,   k13,   k23,   k33,   k43,   k53,   k63,   k04,   KC_NO}, \
  {k14,   k24,   k34,   k44,   k54,   k64,   k05,   k15,   k25,   KC_NO}, \
  {k35,   k45,   k55,   k65,   k06,   k16,   k26,   k36,   k46,   KC_NO}, \
  {k56,   k66,   k07,   k17,   k27,   k37,   k47,   k57,   k67,   KC_NO}, \
  {k08,   k18,   k28,   k38,   k48,   k58,   k68,   k09,   k19,   KC_NO} \
}
