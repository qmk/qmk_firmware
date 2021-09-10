/* Copyright 2018 Jack Humbert <jack.humb@gmail.com>
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

#include "planck.h"

#define XXX KC_NO

#define LAYOUT_planck_1x2uC( \
    k00, k01, k02, k03, k04, k05, k40, k41, k42, k43, k44, k45, \
    k10, k11, k12, k13, k14, k15, k50, k51, k52, k53, k54, k55, \
    k20, k21, k22, k23, k24, k25, k60, k61, k62, k63, k64, k65, \
    k30, k31, k32, k73, k74,    k70,   k71, k72, k33, k34, k35 \
) { \
    { k00, k01, k02, k03, k04, k05 }, \
    { k10, k11, k12, k13, k14, k15 }, \
    { k20, k21, k22, k23, k24, k25 }, \
    { k30, k31, k32, k33, k34, k35 }, \
    { k40, k41, k42, k43, k44, k45 }, \
    { k50, k51, k52, k53, k54, k55 }, \
    { k60, k61, k62, k63, k64, k65 }, \
    { k70, k71, k72, k73, k74, XXX } \
}

#define LAYOUT_planck_1x2uR( \
    k00, k01, k02, k03, k04, k05, k40, k41, k42, k43, k44, k45, \
    k10, k11, k12, k13, k14, k15, k50, k51, k52, k53, k54, k55, \
    k20, k21, k22, k23, k24, k25, k60, k61, k62, k63, k64, k65, \
    k30, k31, k32, k73, k74, k75,   k71,    k72, k33, k34, k35 \
) { \
    { k00, k01, k02, k03, k04, k05 }, \
    { k10, k11, k12, k13, k14, k15 }, \
    { k20, k21, k22, k23, k24, k25 }, \
    { k30, k31, k32, k33, k34, k35 }, \
    { k40, k41, k42, k43, k44, k45 }, \
    { k50, k51, k52, k53, k54, k55 }, \
    { k60, k61, k62, k63, k64, k65 }, \
    { XXX, k71, k72, k73, k74, k75 } \
}

#define LAYOUT_planck_1x2uL( \
    k00, k01, k02, k03, k04, k05, k40, k41, k42, k43, k44, k45, \
    k10, k11, k12, k13, k14, k15, k50, k51, k52, k53, k54, k55, \
    k20, k21, k22, k23, k24, k25, k60, k61, k62, k63, k64, k65, \
    k30, k31, k32, k73,   k75,    k70, k71, k72, k33, k34, k35 \
) { \
    { k00, k01, k02, k03, k04, k05 }, \
    { k10, k11, k12, k13, k14, k15 }, \
    { k20, k21, k22, k23, k24, k25 }, \
    { k30, k31, k32, k33, k34, k35 }, \
    { k40, k41, k42, k43, k44, k45 }, \
    { k50, k51, k52, k53, k54, k55 }, \
    { k60, k61, k62, k63, k64, k65 }, \
    { k70, k71, k72, k73, XXX, k75 } \
}

#define LAYOUT_planck_2x2u( \
    k00, k01, k02, k03, k04, k05, k40, k41, k42, k43, k44, k45, \
    k10, k11, k12, k13, k14, k15, k50, k51, k52, k53, k54, k55, \
    k20, k21, k22, k23, k24, k25, k60, k61, k62, k63, k64, k65, \
    k30, k31, k32, k73,   k75,      k71,    k72, k33, k34, k35 \
) { \
    { k00, k01, k02, k03, k04, k05 }, \
    { k10, k11, k12, k13, k14, k15 }, \
    { k20, k21, k22, k23, k24, k25 }, \
    { k30, k31, k32, k33, k34, k35 }, \
    { k40, k41, k42, k43, k44, k45 }, \
    { k50, k51, k52, k53, k54, k55 }, \
    { k60, k61, k62, k63, k64, k65 }, \
    { XXX, k71, k72, k73, XXX, k75 } \
}

#define LAYOUT_ortho_4x12( \
    k00, k01, k02, k03, k04, k05, k40, k41, k42, k43, k44, k45, \
    k10, k11, k12, k13, k14, k15, k50, k51, k52, k53, k54, k55, \
    k20, k21, k22, k23, k24, k25, k60, k61, k62, k63, k64, k65, \
    k30, k31, k32, k73, k74, k75, k70, k71, k72, k33, k34, k35 \
) { \
    { k00, k01, k02, k03, k04, k05 }, \
    { k10, k11, k12, k13, k14, k15 }, \
    { k20, k21, k22, k23, k24, k25 }, \
    { k30, k31, k32, k33, k34, k35 }, \
    { k40, k41, k42, k43, k44, k45 }, \
    { k50, k51, k52, k53, k54, k55 }, \
    { k60, k61, k62, k63, k64, k65 }, \
    { k70, k71, k72, k73, k74, k75 } \
}

#define LAYOUT LAYOUT_ortho_4x12
#define LAYOUT_planck_mit LAYOUT_planck_1x2uC
#define LAYOUT_planck_grid LAYOUT_ortho_4x12
