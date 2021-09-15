/*
Copyright 2017 Balz Guenat

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

#define LAYOUT( \
    k13, k10, k11, k12, k14, k16, k17, k15, k1B, k18, k19, k1A, k1C, k1E,      k1F, \
    k03, k00, k01, k02, k04, k06, k07, k05, k0B, k08, k09, k0A, k0C, k0E,      k0F, \
    k43, k40, k41, k42, k44, k46, k47, k45, k4B, k48, k49, k4A,      k4E, \
    k33, k31, k32, k34, k36, k37, k35, k3B, k38, k39, k3A,           k3C, k3D, \
    k23, k21, k22,                k27,                k28, k2A, k2C, k2E, k2D, k2F  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, XXX, k0E, k0F }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, XXX, k1E, k1F }, \
    { XXX, k21, k22, k23, XXX, XXX, XXX, k27, k28, XXX, k2A, XXX, k2C, k2D, k2E, k2F }, \
    { XXX, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, XXX, XXX }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B, XXX, XXX, k4E, XXX } \
}
