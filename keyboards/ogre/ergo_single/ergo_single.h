/* Copyright 2020 ctrlshiftba
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

#define LAYOUT( \
  k63, k00, k10, k20, k30, k40, k50, k60, k65, k55, k45, k35, k25, k15, k05, k68, \
       k01, k11, k21, k31, k41, k51, k61, k66, k56, k46, k36, k26, k16, k06, \
       k02, k12, k22, k32, k42, k52, k62, k67, k57, k47, k37, k27, k17, k07, \
       k03, k13, k23, k33, k43, k53,           k58, k48, k38, k28, k18, k08, \
       k04, k14, k24, k34, k44, k54, k64, k69, k59, k49, k39, k29, k19, k09 \
) \
{ \
 { k00, k10, k20, k30, k40, k50, k60 }, \
 { k01, k11, k21, k31, k41, k51, k61 }, \
 { k02, k12, k22, k32, k42, k52, k62 }, \
 { k03, k13, k23, k33, k43, k53, k63 }, \
 { k04, k14, k24, k34, k44, k54, k64 }, \
 { k05, k15, k25, k35, k45, k55, k65 }, \
 { k06, k16, k26, k36, k46, k56, k66 }, \
 { k07, k17, k27, k37, k47, k57, k67 }, \
 { k08, k18, k28, k38, k48, k58, k68 }, \
 { k09, k19, k29, k39, k49, k59, k69 }, \
}
