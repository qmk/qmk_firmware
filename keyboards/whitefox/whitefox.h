/*
Copyright 2014 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "quantum.h"

#define XXX KC_NO

/*
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
 * │   │   │   │   │   │   │   │   │   │   │   │   │   │   │   │   │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┼───┤
 * │     │   │   │   │   │   │   │   │   │   │   │   │   │     │   │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬────┼───┤
 * │      │   │   │   │   │   │   │   │   │   │   │   │   │    │   │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┼───┤
 * │    │   │   │   │   │   │   │   │   │   │   │   │      │   │   │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┼───┤
 * │    │    │    │                        │   │   │   │   │   │   │
 * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┴───┘
 */
#define LAYOUT_all( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k10, k11, k12, k13, k14, k15, k16, \
    k17, k18, k20, k21, k22, k23, k24, k25, k26, k27, k28, k30, k31, k32, k33, \
    k34, k35, k36, k37, k38, k40, k41, k42, k43, k44, k45, k46, k47, k48, k50, \
    k51, k52, k53, k54, k55, k56, k57, k58, k60, k61, k62, k63, k64, k65, k66, \
    k67, k68, k70,                k71,           k72, k73, k74, k75, k76, k77 \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08 }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18 }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28 }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38 }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48 }, \
    { k50, k51, k52, k53, k54, k55, k56, k57, k58 }, \
    { k60, k61, k62, k63, k64, k65, k66, k67, k68 }, \
    { k70, k71, k72, k73, k74, k75, k76, k77, XXX } \
}

/*
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
 * │   │   │   │   │   │   │   │   │   │   │   │   │   │       │   │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
 * │     │   │   │   │   │   │   │   │   │   │   │   │   │     │   │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
 * │      │   │   │   │   │   │   │   │   │   │   │   │        │   │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
 * │        │   │   │   │   │   │   │   │   │   │   │      │   │   │
 * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┼───┤
 * │    │    │    │                        │   │   │   │   │   │   │
 * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┴───┘
 */
#define LAYOUT_65_ansi( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k10, k11, k12, k13, k15, k16, \
    k17, k18, k20, k21, k22, k23, k24, k25, k26, k27, k28, k30, k31, k32, k33, \
    k34, k35, k36, k37, k38, k40, k41, k42, k43, k44, k45, k46,      k48, k50, \
    k51,      k53, k54, k55, k56, k57, k58, k60, k61, k62, k63, k64, k65, k66, \
    k67, k68, k70,                k71,           k72, k73, k74, k75, k76, k77 \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08 }, \
    { k10, k11, k12, k13, XXX, k15, k16, k17, k18 }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28 }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38 }, \
    { k40, k41, k42, k43, k44, k45, k46, XXX, k48 }, \
    { k50, k51, XXX, k53, k54, k55, k56, k57, k58 }, \
    { k60, k61, k62, k63, k64, k65, k66, k67, k68 }, \
    { k70, k71, k72, k73, k74, k75, k76, k77, XXX } \
}

/*
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
 * │   │   │   │   │   │   │   │   │   │   │   │   │   │       │   │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
 * │     │   │   │   │   │   │   │   │   │   │   │   │   │     │   │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
 * │      │   │   │   │   │   │   │   │   │   │   │   │        │   │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
 * │        │   │   │   │   │   │   │   │   │   │   │      │   │   │
 * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬─┬───┼───┼───┤
 * │    │    │    │                        │    │    │ │   │   │   │
 * └────┴────┴────┴────────────────────────┴────┴────┘ └───┴───┴───┘
 */
#define LAYOUT_65_ansi_blocker( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k10, k11, k12, k13, k15, k16, \
    k17, k18, k20, k21, k22, k23, k24, k25, k26, k27, k28, k30, k31, k32, k33, \
    k34, k35, k36, k37, k38, k40, k41, k42, k43, k44, k45, k46,      k48, k50, \
    k51,      k53, k54, k55, k56, k57, k58, k60, k61, k62, k63, k64, k65, k66, \
    k67, k68, k70,                k71,                k72, k73, k75, k76, k77 \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08 }, \
    { k10, k11, k12, k13, XXX, k15, k16, k17, k18 }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28 }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38 }, \
    { k40, k41, k42, k43, k44, k45, k46, XXX, k48 }, \
    { k50, k51, XXX, k53, k54, k55, k56, k57, k58 }, \
    { k60, k61, k62, k63, k64, k65, k66, k67, k68 }, \
    { k70, k71, k72, k73, XXX, k75, k76, k77, XXX } \
}

/*
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
 * │   │   │   │   │   │   │   │   │   │   │   │   │   │   │   │   │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┼───┤
 * │     │   │   │   │   │   │   │   │   │   │   │   │   │     │   │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
 * │      │   │   │   │   │   │   │   │   │   │   │   │        │   │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
 * │        │   │   │   │   │   │   │   │   │   │   │      │   │   │
 * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬─┬───┼───┼───┤
 * │    │    │    │                        │    │    │ │   │   │   │
 * └────┴────┴────┴────────────────────────┴────┴────┘ └───┴───┴───┘
 */
#define LAYOUT_65_ansi_blocker_split_bs( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k10, k11, k12, k13, k14, k15, k16, \
    k17, k18, k20, k21, k22, k23, k24, k25, k26, k27, k28, k30, k31, k32, k33, \
    k34, k35, k36, k37, k38, k40, k41, k42, k43, k44, k45, k46,      k48, k50, \
    k51,      k53, k54, k55, k56, k57, k58, k60, k61, k62, k63, k64, k65, k66, \
    k67, k68, k70,                k71,                k72, k73, k75, k76, k77 \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08 }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18 }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28 }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38 }, \
    { k40, k41, k42, k43, k44, k45, k46, XXX, k48 }, \
    { k50, k51, XXX, k53, k54, k55, k56, k57, k58 }, \
    { k60, k61, k62, k63, k64, k65, k66, k67, k68 }, \
    { k70, k71, k72, k73, XXX, k75, k76, k77, XXX } \
}

/*
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
 * │   │   │   │   │   │   │   │   │   │   │   │   │   │       │   │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
 * │     │   │   │   │   │   │   │   │   │   │   │   │   │     │   │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    ├───┤
 * │      │   │   │   │   │   │   │   │   │   │   │   │   │    │   │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┼───┤
 * │    │   │   │   │   │   │   │   │   │   │   │   │      │   │   │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┼───┤
 * │    │    │    │                        │   │   │   │   │   │   │
 * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┴───┘
 */
#define LAYOUT_65_iso( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k10, k11, k12, k13, k15, k16, \
    k17, k18, k20, k21, k22, k23, k24, k25, k26, k27, k28, k30, k31,      k33, \
    k34, k35, k36, k37, k38, k40, k41, k42, k43, k44, k45, k46, k47, k48, k50, \
    k51, k52, k53, k54, k55, k56, k57, k58, k60, k61, k62, k63, k64, k65, k66, \
    k67, k68, k70,                k71,           k72, k73, k74, k75, k76, k77 \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08 }, \
    { k10, k11, k12, k13, XXX, k15, k16, k17, k18 }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28 }, \
    { k30, k31, XXX, k33, k34, k35, k36, k37, k38 }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48 }, \
    { k50, k51, k52, k53, k54, k55, k56, k57, k58 }, \
    { k60, k61, k62, k63, k64, k65, k66, k67, k68 }, \
    { k70, k71, k72, k73, k74, k75, k76, k77, XXX } \
}

/*
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
 * │   │   │   │   │   │   │   │   │   │   │   │   │   │       │   │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
 * │     │   │   │   │   │   │   │   │   │   │   │   │   │     │   │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    ├───┤
 * │      │   │   │   │   │   │   │   │   │   │   │   │   │    │   │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┼───┤
 * │    │   │   │   │   │   │   │   │   │   │   │   │      │   │   │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬─┬───┼───┼───┤
 * │    │    │    │                        │    │    │ │   │   │   │
 * └────┴────┴────┴────────────────────────┴────┴────┘ └───┴───┴───┘
 */
#define LAYOUT_65_iso_blocker( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k10, k11, k12, k13, k15, k16, \
    k17, k18, k20, k21, k22, k23, k24, k25, k26, k27, k28, k30, k31,      k33, \
    k34, k35, k36, k37, k38, k40, k41, k42, k43, k44, k45, k46, k47, k48, k50, \
    k51, k52, k53, k54, k55, k56, k57, k58, k60, k61, k62, k63, k64, k65, k66, \
    k67, k68, k70,                k71,                k72, k73, k75, k76, k77 \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08 }, \
    { k10, k11, k12, k13, XXX, k15, k16, k17, k18 }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28 }, \
    { k30, k31, XXX, k33, k34, k35, k36, k37, k38 }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48 }, \
    { k50, k51, k52, k53, k54, k55, k56, k57, k58 }, \
    { k60, k61, k62, k63, k64, k65, k66, k67, k68 }, \
    { k70, k71, k72, k73, XXX, k75, k76, k77, XXX } \
}

/*
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
 * │   │   │   │   │   │   │   │   │   │   │   │   │   │   │   │   │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┼───┤
 * │     │   │   │   │   │   │   │   │   │   │   │   │   │     │   │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    ├───┤
 * │      │   │   │   │   │   │   │   │   │   │   │   │   │    │   │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┼───┤
 * │    │   │   │   │   │   │   │   │   │   │   │   │      │   │   │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬─┬───┼───┼───┤
 * │    │    │    │                        │    │    │ │   │   │   │
 * └────┴────┴────┴────────────────────────┴────┴────┘ └───┴───┴───┘
 */
#define LAYOUT_65_iso_blocker_split_bs( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k10, k11, k12, k13, k14, k15, k16, \
    k17, k18, k20, k21, k22, k23, k24, k25, k26, k27, k28, k30, k31,      k33, \
    k34, k35, k36, k37, k38, k40, k41, k42, k43, k44, k45, k46, k47, k48, k50, \
    k51, k52, k53, k54, k55, k56, k57, k58, k60, k61, k62, k63, k64, k65, k66, \
    k67, k68, k70,                k71,                k72, k73, k75, k76, k77 \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08 }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18 }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28 }, \
    { k30, k31, XXX, k33, k34, k35, k36, k37, k38 }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48 }, \
    { k50, k51, k52, k53, k54, k55, k56, k57, k58 }, \
    { k60, k61, k62, k63, k64, k65, k66, k67, k68 }, \
    { k70, k71, k72, k73, XXX, k75, k76, k77, XXX } \
}

#define LAYOUT LAYOUT_all
#define LAYOUT_aria LAYOUT_65_ansi_blocker
#define LAYOUT_iso LAYOUT_65_iso
#define LAYOUT_truefox LAYOUT_65_ansi_blocker_split_bs
#define LAYOUT_vanilla LAYOUT_65_ansi
