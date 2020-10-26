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
  k60, k50, k40, k30, k20, k10, k00, k61, k51, k41, k31, k21, k11, k01, k62,    \
  k52, k42, k32, k22, k12, k02, k63, k53, k43, k33, k23, k13, k03, k64, k54,    \
  k44, k34, k24, k14, k04, k65, k55, k45, k35, k25, k15, k05, k66,              \
  k56, k46, k36, k26, k16, k06, k67, k57, k47, k37, k27, k17, k07,              \
  k68, k58, k48, k38, k28, k18, k08, k69, k59                                   \
) \
{ \
  {k60,   k50,   k40,   k30,   k20,   k10,   k00,   k61,   k51,   k41,   k31,   k21,   k11,   k01,   k62}, \
  {k52,   k42,   k32,   k22,   k12,   k02,   k63,   k53,   k43,   k33,   k23,   k13,   k03,   k64,   k54}, \
  {k44,   k34,   k24,   k14,   k04,   k65,   k55,   k45,   k35,   k25,   k15,   k05,   k66},               \
  {k56,   k46,   k36,   k26,   k16,   k06,   k67,   k57,   k47,   k37,   k27,   k17,   k07},               \
  {k68,   k58,   k48,   k38,   k28,   k18,   k08,   k69,   k59}                                           \
}
