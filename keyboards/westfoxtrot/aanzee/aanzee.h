/* Copyright 2019 westfoxtrot
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

#define ___ KC_NO

#include "quantum.h"

/* This a shortcut to help you visually see your layout.
*
* The first section contains all of the arguments representing the physical
* layout of the board and position of the keys.
*
* The second converts the arguments into a two-dimensional array which
* represents the switch matrix.
*/
#define LAYOUT_ansi( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0F, k0D, k0E, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C,      k1D, k1E, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B,           k2D, k2E, \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C,      k3D, k3E, \
    k40, k41, k42,                k46,           k49, k4A,      k4C,      k4D, k4E \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, k0F }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, ___ }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, ___, k2D, k2E, ___ }, \
    { k30, ___, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E, ___ }, \
    { k40, k41, k42, ___, ___, ___, k46, ___, ___, k49, k4A, ___, k4C, k4D, k4E, ___ } \
}

#define LAYOUT_iso( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C,      k1E, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2E, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E, \
    k40, k41, k42,                k46,           k49, k4A,      k4C, k4D, k4E \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, ___ }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, ___, k1E, ___ }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2E, ___ }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E, ___ }, \
    { k40, k41, k42, ___, ___, ___, k46, ___, ___, k49, k4A, ___, k4C, k4D, k4E, ___ } \
}

void matrix_init_user(void);
void matrix_scan_user(void);
