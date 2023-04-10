/* Copyright 2022 Nathan Spears
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

#define XXX KC_NO

#define LAYOUT_grid( \
    k00, k10, k11, k01, k02, k12, k13, k03, k04, k14, k15, k05, \
    k20, k30, k31, k21, k22, k32, k33, k23, k24, k34, k35, k25, \
    k40, k50, k51, k41, k42, k52, k53, k43, k44, k54, k55, k45, \
    k60, k70, k71, k61, k62, k72, k73, k63, k64, k74, k75, k65 \
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
#define LAYOUT_2u( \
    k00, k10, k11, k01, k02, k12, k13, k03, k04, k14, k15, k05, \
    k20, k30, k31, k21, k22, k32, k33, k23, k24, k34, k35, k25, \
    k40, k50, k51, k41, k42, k52, k53, k43, k44, k54, k55, k45, \
    k60, k70, k71, k61, k62,      k73, k63, k64, k74, k75, k65 \
) { \
    { k00, k01, k02, k03, k04, k05 }, \
    { k10, k11, k12, k13, k14, k15 }, \
    { k20, k21, k22, k23, k24, k25 }, \
    { k30, k31, k32, k33, k34, k35 }, \
    { k40, k41, k42, k43, k44, k45 }, \
    { k50, k51, k52, k53, k54, k55 }, \
    { k60, k61, k62, k63, k64, k65 }, \
    { k70, k71, XXX, k73, k74, k75 } \
}
#define LAYOUT_2x225u( \
    k00, k10, k11, k01, k02, k12, k13, k03, k04, k14, k15, k05, \
    k20, k30, k31, k21, k22, k32, k33, k23, k24, k34, k35, k25, \
    k40, k50, k51, k41, k42, k52, k53, k43, k44, k54, k55, k45, \
    k60, k70,      k61, k62,           k63, k64,      k75, k65 \
) { \
    { k00, k01, k02, k03, k04, k05 }, \
    { k10, k11, k12, k13, k14, k15 }, \
    { k20, k21, k22, k23, k24, k25 }, \
    { k30, k31, k32, k33, k34, k35 }, \
    { k40, k41, k42, k43, k44, k45 }, \
    { k50, k51, k52, k53, k54, k55 }, \
    { k60, k61, k62, k63, k64, k65 }, \
    { k70, XXX, XXX, XXX, XXX, k75 } \
}
#define LAYOUT_2x3u( \
    k00, k10, k11, k01, k02, k12, k13, k03, k04, k14, k15, k05, \
    k20, k30, k31, k21, k22, k32, k33, k23, k24, k34, k35, k25, \
    k40, k50, k51, k41, k42, k52, k53, k43, k44, k54, k55, k45, \
    k60, k70, k71,      k62,           k63,      k74, k75, k65 \
) { \
    { k00, k01, k02, k03, k04, k05 }, \
    { k10, k11, k12, k13, k14, k15 }, \
    { k20, k21, k22, k23, k24, k25 }, \
    { k30, k31, k32, k33, k34, k35 }, \
    { k40, k41, k42, k43, k44, k45 }, \
    { k50, k51, k52, k53, k54, k55 }, \
    { k60, XXX, k62, k63, XXX, k65 }, \
    { k70, k71, XXX, XXX, k74, k75 } \
}
