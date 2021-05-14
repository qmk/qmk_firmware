/* Copyright 2021 keebnewb
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

#define LAYOUT_default( \
    k00, k01, k61, k02, k62, k03, k63, k04, k64, k05, k65, k06, k66, k67,  \
    k10, k70, k11, k71, k12, k72, k13, k73, k14, k74, k15, k75, k16, k76, k17,  \
    k20, k80, k21, k81, k22, k82, k23, k83, k24, k84, k25, k85, k26, k27,  \
    k30, k90, k31, k91, k32, k92, k33, k93, k34, k94, k35, k95, k37,  \
    k40, k41, ka1, k42, ka2, k43, ka3, k44, ka4, k45, ka5, ka6, k47,  \
    k50, k51, k53, kb5, k57
){ \
    { k00, k01, k02, k03, k04, k05, k06, ___ },  \
    { k10, k11, k12, k13, k14, k15, k16, k17 },  \
    { k20, k21, k22, k23, k24, k25, k26, k27 },  \
    { k30, k31, k32, k33, k34, k35, ___, k37 },  \
    { k40, k41, k42, k43, k44, k45, ___, k47 },  \
    { k50, k51, ___, k53, ___, ___, ___, k57 },  \
    { ___, k61, k62, k63, k64, k65, k66, k67 },  \
    { k70, k71, k72, k73, k74, k75, k76, ___ },  \
    { k80, k81, k82, k83, k84, k85, ___, ___ },  \
    { k90, k91, k92, k93, k94, k95, ___, ___ },  \
    { ___, ka1, ka2, ka3, ka4, ka5, ka6, ___ },  \
    { ___, ___, ___, ___, ___, kb5, ___, ___ }
}

#define LAYOUT_DeBaccaBean( \
    k00, k01, k61, k02, k62, k03, k63, k04, k64, k05, k65, k06, k66, k67,  \
    k10, k70, k11, k71, k12, k72, k13, k73, k14, k74, k15, k75, k16, k76, k17,  \
    k20, k80, k21, k81, k22, k82, k23, k83, k24, k84, k25, k85, k26, k86, k27,  \
    k30, k90, k31, k91, k32, k92, k33, k93, k34, k94, k35, k95, k36, k96, k37,  \
    k40, ka0, k41, ka1, k42, ka2, k43, ka3, k44, ka4, k45, ka5, k46, ka6, k47,  \
    k50, k51, k52, k53, k54, kb5, k57
){ \
    { k00, k01, k02, k03, k04, k05, k06, ___ },  \
    { k10, k11, k12, k13, k14, k15, k16, k17 },  \
    { k20, k21, k22, k23, k24, k25, k26, k27 },  \
    { k30, k31, k32, k33, k34, k35, k36, k37 },  \
    { k40, k41, k42, k43, k44, k45, k46, k47 },  \
    { k50, k51, k52, k53, k54, ___, ___, k57 },  \
    { ___, k61, k62, k63, k64, k65, k66, k67 },  \
    { k70, k71, k72, k73, k74, k75, k76, ___ },  \
    { k80, k81, k82, k83, k84, k85, k86, ___ },  \
    { k90, k91, k92, k93, k94, k95, k96, ___ },  \
    { ka0, ka1, ka2, ka3, ka4, ka5, ka6, ___ },  \
    { ___, ___, ___, ___, ___, kb5, ___, ___ }
}
