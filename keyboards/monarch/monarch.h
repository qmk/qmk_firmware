/*
Copyright 2021 King Keyboards www.kingkbs.com
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

// ANSI enter
#define LAYOUT_ansi( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,      k1e, k1f, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,      k2d,      k2f, \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,      k3d, k3e,      \
    k40, k41, k42,                     k47,                k4b,      k4d, k4e, k4f \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, XXX, k1e, k1f }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, XXX, k2d, XXX, k2f }, \
    { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, XXX, k3d, k3e, XXX }, \
    { k40, k41, k42, XXX, XXX, XXX, XXX, k47, XXX, XXX, XXX, k4b, XXX, k4d, k4e, k4f }, \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX }, \
}

// ISO enter
// Split left shift
#define LAYOUT_iso( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,      k1e, k1f, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,      k2d,      k2f, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,      k3d, k3e,      \
    k40, k41, k42,                     k47,                k4b,      k4d, k4e, k4f \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, XXX, k1e, k1f }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, XXX, k2d, XXX, k2f }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, XXX, k3d, k3e, XXX }, \
    { k40, k41, k42, XXX, XXX, XXX, XXX, k47, XXX, XXX, XXX, k4b, XXX, k4d, k4e, k4f }, \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX }, \
}

// VIA-specific layout with extra buttons for changing rotary encoder functionality
#define LAYOUT_all( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,      k1e, k1f, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,      k2d,      k2f, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,      k3d, k3e,      \
    k40, k41, k42,                     k47,                k4b,      k4d, k4e, k4f, \
    k50, k51 \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, XXX, k1e, k1f }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, XXX, k2d, XXX, k2f }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, XXX, k3d, k3e, XXX }, \
    { k40, k41, k42, XXX, XXX, XXX, XXX, k47, XXX, XXX, XXX, k4b, XXX, k4d, k4e, k4f }, \
    { k50, k51, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX }, \
}
