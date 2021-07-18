/* Copyright 2020 Evy Dekkers
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

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
 
#define LAYOUT_all LAYOUT_tkl_iso

#define LAYOUT_tkl_ansi( \
    k3e,      k0d, k0b, k4b, k3b, k21, k36, k45, k05, k03, k23, k33, k63,      k28, k18, k11, \
    k0e, k2e, k2d, k2b, k29, k09, k07, k27, k26, k25, k24, k04, k06, k43,      k02, k0a, k0c, \
    k4e, k1e, k1d, k1b, k19, k49, k47, k17, k16, k15, k14, k44, k46, k73,      k00, k2a, k2c, \
    k4d, k7e, k7d, k7b, k79, k39, k37, k77, k76, k75, k74, k34,      k53,                     \
    k4c,      k5e, k5d, k5b, k59, k69, k67, k57, k56, k55, k64,      k7c,           k3a,      \
    k01, k4a, k38,                k30,                k68, k71, k65, k51,      k6a, k60, k62  \
) \
{ \
    { k00, k01, k02, k03, k04, k05, k06, k07, XXX, k09, k0a, k0b, k0c, k0d, k0e }, \
    { XXX, k11, XXX, XXX, k14, k15, k16, k17, k18, k19, XXX, k1b, XXX, k1d, k1e }, \
    { XXX, k21, XXX, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e }, \
    { k30, XXX, XXX, k33, k34, XXX, k36, k37, k38, k39, k3a, k3b, XXX, XXX, k3e }, \
    { XXX, XXX, XXX, k43, k44, k45, k46, k47, XXX, k49, k4a, k4b, k4c, k4d, k4e }, \
    { XXX, k51, XXX, k53, XXX, k55, k56, k57, XXX, k59, XXX, k5b, XXX, k5d, k5e }, \
    { k60, XXX, k62, k63, k64, k65, XXX, k67, k68, k69, k6a, XXX, XXX, XXX, XXX }, \
    { XXX, k71, XXX, k73, k74, k75, k76, k77, XXX, k79, XXX, k7b, k7c, k7d, k7e }  \
}

#define LAYOUT_tkl_iso( \
    k3e,      k0d, k0b, k4b, k3b, k21, k36, k45, k05, k03, k23, k33, k63,      k28, k18, k11, \
    k0e, k2e, k2d, k2b, k29, k09, k07, k27, k26, k25, k24, k04, k06, k43,      k02, k0a, k0c, \
    k4e, k1e, k1d, k1b, k19, k49, k47, k17, k16, k15, k14, k44, k46,           k00, k2a, k2c, \
    k4d, k7e, k7d, k7b, k79, k39, k37, k77, k76, k75, k74, k34, k73, k53,                     \
    k4c, k3d, k5e, k5d, k5b, k59, k69, k67, k57, k56, k55, k64,      k7c,           k3a,      \
    k01, k4a, k38,                k30,                k68, k71, k65, k51,      k6a, k60, k62  \
) \
{ \
    { k00, k01, k02, k03, k04, k05, k06, k07, XXX, k09, k0a, k0b, k0c, k0d, k0e }, \
    { XXX, k11, XXX, XXX, k14, k15, k16, k17, k18, k19, XXX, k1b, XXX, k1d, k1e }, \
    { XXX, k21, XXX, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e }, \
    { k30, XXX, XXX, k33, k34, XXX, k36, k37, k38, k39, k3a, k3b, XXX, k3d, k3e }, \
    { XXX, XXX, XXX, k43, k44, k45, k46, k47, XXX, k49, k4a, k4b, k4c, k4d, k4e }, \
    { XXX, k51, XXX, k53, XXX, k55, k56, k57, XXX, k59, XXX, k5b, XXX, k5d, k5e }, \
    { k60, XXX, k62, k63, k64, k65, XXX, k67, k68, k69, k6a, XXX, XXX, XXX, XXX }, \
    { XXX, k71, XXX, k73, k74, k75, k76, k77, XXX, k79, XXX, k7b, k7c, k7d, k7e }  \
}
