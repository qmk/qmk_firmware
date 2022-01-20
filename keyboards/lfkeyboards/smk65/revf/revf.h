/*
Copyright 2020 LFKeyboards
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

// readability
#define ___ KC_NO

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */

#define LAYOUT_65_ansi( \
    k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D,         k1F, k1G, \
    k21,   k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D,       k2F, k2G, \
    k31,    k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C,           k3F, k3G, \
    k41,      k43, k44, k45, k46, k47, k48, k49, k4A, k4B, k4C,         k4D, k4F, k4G, \
    k51, k52, k53,              k57,                     k5B, k5C, k5D, k5E, k3E, k4E  \
) { \
    { k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, ___, k1F, k1G }, \
    { k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, ___, k2F, k2G }, \
    { k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, ___, k3E, k3F, k3G }, \
    { k41, ___, k43, k44, k45, k46, k47, k48, k49, k4A, k4B, k4C, k4D, k4E, k4F, k4G }, \
    { k51, k52, k53, ___, ___, ___, k57, ___, ___, ___, k5B, k5C, k5D, k5E, ___, ___ }, \
}

#define LAYOUT_65_iso( \
    k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D,         k1F, k1G, \
    k21,   k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D,            k2G, \
    k31,    k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C,      k3D, k2F, k3G, \
    k41, k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B, k4C,         k4D, k4F, k4G, \
    k51, k52, k53,              k57,                     k5B, k5C, k5D, k5E, k3E, k4E  \
) { \
    { k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, ___, k1F, k1G }, \
    { k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, ___, k2F, k2G }, \
    { k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E, ___, k3G }, \
    { k41, k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B, k4C, k4D, k4E, k4F, k4G }, \
    { k51, k52, k53, ___, ___, ___, k57, ___, ___, ___, k5B, k5C, k5D, k5E, ___, ___ }, \
}

#define LAYOUT_all( \
    k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E,    k1F, k1G, \
    k21,   k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D,       k2F, k2G, \
    k31,    k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C,      k3D, k3F, k3G, \
    k41, k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B, k4C,         k4D, k4F, k4G, \
    k51, k52, k53,         k55, k57, k59,                k5B, k5C, k5D, k5E, k3E, k4E  \
) { \
    { k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, k1F, k1G }, \
    { k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, ___, k2F, k2G }, \
    { k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E, k3F, k3G }, \
    { k41, k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B, k4C, k4D, k4E, k4F, k4G }, \
    { k51, k52, k53, ___, k55, ___, k57, ___, k59, ___, k5B, k5C, k5D, k5E, ___, ___ }, \
}
