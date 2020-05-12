/* Copyright 2019 Maarten Dekkers <maartenwut@gmail.com>
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
 
#define LAYOUT_all LAYOUT_fullsize_iso

#define LAYOUT_fullsize_ansi( \
    k05,      k64, k62, k22, k02, k31, k0c, k2f, k6f, k6b, k3b, k0b, k5b,      k33, k43, k41,                          \
    k65, k35, k34, k32, k30, k60, k6a, k3a, k3c, k3f, k3d, k6d, k6c, k2b,      k67, k6e, k66,      k78, k77, k76, k56, \
    k25, k45, k44, k42, k40, k20, k2a, k4a, k4c, k4f, k4d, k2d, k2c, k1b,      k68, k3e, k36,      k48, k47, k46, k4e, \
    k24, k15, k14, k12, k10, k00, k0a, k1a, k1c, k1f, k1d, k0d,      k7b,                          k28, k27, k26,      \
    k29,      k75, k74, k72, k70, k50, k5a, k7a, k7c, k7f, k5d,      k19,           k0e,           k18, k17, k16, k1e, \
    k61, k21, k03,                k08,                k53, k11, k23, k71,      k5e, k58, k57,      k07,      k06       \
) \
{ \
    { k00, XXX, k02, k03, XXX, k05, k06, k07, k08, XXX, k0a, k0b, k0c, k0d, k0e, XXX }, \
    { k10, k11, k12, XXX, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, XXX, k2f }, \
    { k30, k31, k32, k33, k34, k35, k36, XXX, XXX, XXX, k3a, k3b, k3c, k3d, k3e, k3f }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48, XXX, k4a, XXX, k4c, k4d, k4e, k4f }, \
    { k50, XXX, XXX, k53, XXX, XXX, k56, k57, k58, XXX, k5a, k5b, XXX, k5d, k5e, XXX }, \
    { k60, k61, k62, XXX, k64, k65, k66, k67, k68, XXX, k6a, k6b, k6c, k6d, k6e, k6f }, \
    { k70, k71, k72, XXX, k74, k75, k76, k77, k78, XXX, k7a, k7b, k7c, XXX, XXX, k7f }  \
}

#define LAYOUT_fullsize_iso( \
    k05,      k64, k62, k22, k02, k31, k0c, k2f, k6f, k6b, k3b, k0b, k5b,      k33, k43, k41,                          \
    k65, k35, k34, k32, k30, k60, k6a, k3a, k3c, k3f, k3d, k6d, k6c, k2b,      k67, k6e, k66,      k78, k77, k76, k56, \
    k25, k45, k44, k42, k40, k20, k2a, k4a, k4c, k4f, k4d, k2d, k2c,           k68, k3e, k36,      k48, k47, k46, k4e, \
    k24, k15, k14, k12, k10, k00, k0a, k1a, k1c, k1f, k1d, k0d, k1b, k7b,                          k28, k27, k26,      \
    k29, k04, k75, k74, k72, k70, k50, k5a, k7a, k7c, k7f, k5d,      k19,           k0e,           k18, k17, k16, k1e, \
    k61, k21, k03,                k08,                k53, k11, k23, k71,      k5e, k58, k57,      k07,      k06       \
) \
{ \
    { k00, XXX, k02, k03, k04, k05, k06, k07, k08, XXX, k0a, k0b, k0c, k0d, k0e, XXX }, \
    { k10, k11, k12, XXX, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, XXX, k2f }, \
    { k30, k31, k32, k33, k34, k35, k36, XXX, XXX, XXX, k3a, k3b, k3c, k3d, k3e, k3f }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48, XXX, k4a, XXX, k4c, k4d, k4e, k4f }, \
    { k50, XXX, XXX, k53, XXX, XXX, k56, k57, k58, XXX, k5a, k5b, XXX, k5d, k5e, XXX }, \
    { k60, k61, k62, XXX, k64, k65, k66, k67, k68, XXX, k6a, k6b, k6c, k6d, k6e, k6f }, \
    { k70, k71, k72, XXX, k74, k75, k76, k77, k78, XXX, k7a, k7b, k7c, XXX, XXX, k7f }  \
}

#define LAYOUT_tkl_ansi( \
    k05,      k64, k62, k22, k02, k31, k0c, k2f, k6f, k6b, k3b, k0b, k5b,      k33, k43, k41, \
    k65, k35, k34, k32, k30, k60, k6a, k3a, k3c, k3f, k3d, k6d, k6c, k2b,      k67, k6e, k66, \
    k25, k45, k44, k42, k40, k20, k2a, k4a, k4c, k4f, k4d, k2d, k2c, k1b,      k68, k3e, k36, \
    k24, k15, k14, k12, k10, k00, k0a, k1a, k1c, k1f, k1d, k0d,      k7b,                     \
    k29,      k75, k74, k72, k70, k50, k5a, k7a, k7c, k7f, k5d,      k19,           k0e,      \
    k61, k21, k03,                k08,                k53, k11, k23, k71,      k5e, k58, k57  \
) \
{ \
    { k00, XXX, k02, k03, XXX, k05, XXX, XXX, k08, XXX, k0a, k0b, k0c, k0d, k0e, XXX }, \
    { k10, k11, k12, XXX, k14, k15, XXX, XXX, XXX, k19, k1a, k1b, k1c, k1d, XXX, k1f }, \
    { k20, k21, k22, k23, k24, k25, XXX, XXX, XXX, k29, k2a, k2b, k2c, k2d, XXX, k2f }, \
    { k30, k31, k32, k33, k34, k35, k36, XXX, XXX, XXX, k3a, k3b, k3c, k3d, k3e, k3f }, \
    { k40, k41, k42, k43, k44, k45, XXX, XXX, XXX, XXX, k4a, XXX, k4c, k4d, XXX, k4f }, \
    { k50, XXX, XXX, k53, XXX, XXX, XXX, k57, k58, XXX, k5a, k5b, XXX, k5d, k5e, XXX }, \
    { k60, k61, k62, XXX, k64, k65, k66, k67, k68, XXX, k6a, k6b, k6c, k6d, k6e, k6f }, \
    { k70, k71, k72, XXX, k74, k75, XXX, XXX, XXX, XXX, k7a, k7b, k7c, XXX, XXX, k7f }  \
}

#define LAYOUT_tkl_iso( \
    k05,      k64, k62, k22, k02, k31, k0c, k2f, k6f, k6b, k3b, k0b, k5b,      k33, k43, k41, \
    k65, k35, k34, k32, k30, k60, k6a, k3a, k3c, k3f, k3d, k6d, k6c, k2b,      k67, k6e, k66, \
    k25, k45, k44, k42, k40, k20, k2a, k4a, k4c, k4f, k4d, k2d, k2c,           k68, k3e, k36, \
    k24, k15, k14, k12, k10, k00, k0a, k1a, k1c, k1f, k1d, k0d, k1b, k7b,                     \
    k29, k04, k75, k74, k72, k70, k50, k5a, k7a, k7c, k7f, k5d,      k19,           k0e,      \
    k61, k21, k03,                k08,                k53, k11, k23, k71,      k5e, k58, k57  \
) \
{ \
    { k00, XXX, k02, k03, k04, k05, XXX, XXX, k08, XXX, k0a, k0b, k0c, k0d, k0e, XXX }, \
    { k10, k11, k12, XXX, k14, k15, XXX, XXX, XXX, k19, k1a, k1b, k1c, k1d, XXX, k1f }, \
    { k20, k21, k22, k23, k24, k25, XXX, XXX, XXX, k29, k2a, k2b, k2c, k2d, XXX, k2f }, \
    { k30, k31, k32, k33, k34, k35, k36, XXX, XXX, XXX, k3a, k3b, k3c, k3d, k3e, k3f }, \
    { k40, k41, k42, k43, k44, k45, XXX, XXX, XXX, XXX, k4a, XXX, k4c, k4d, XXX, k4f }, \
    { k50, XXX, XXX, k53, XXX, XXX, XXX, k57, k58, XXX, k5a, k5b, XXX, k5d, k5e, XXX }, \
    { k60, k61, k62, XXX, k64, k65, k66, k67, k68, XXX, k6a, k6b, k6c, k6d, k6e, k6f }, \
    { k70, k71, k72, XXX, k74, k75, XXX, XXX, XXX, XXX, k7a, k7b, k7c, XXX, XXX, k7f }  \
}
