/*
Copyright 2017 Luiz Ribeiro <luizribeiro@gmail.com>

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
    k40, k41, k42, k43, k44, k45, k61, k6B, k7B, k71, k4A, k4B, k4C, k4D, k4E, k0D, \
    k30, k31, k32, k33, k34, k35, k62, k6C, k7C, k72, k3A, k3B, k3C,      k3D, k76, \
    k20, k21, k22, k23, k24, k25, k63, k6D, k7D, k73, k2A, k2B, k2C,      k2D, k78, \
    k10, k03, k11, k12, k13, k14, k15, k64, k6E, k7E, k74, k1A,      k1B, k68, k77, \
    k00, k01, k02,      k04, k65, k05,                k75, k0B, k0C, k69, k67, k66 \
) { \
    { k00, k01, k02, k03, k04, k05, XXX, XXX, XXX, XXX, XXX, k0B, k0C, k0D, XXX }, \
    { k10, k11, k12, k13, k14, k15, XXX, XXX, XXX, XXX, k1A, k1B, XXX, XXX, XXX }, \
    { k20, k21, k22, k23, k24, k25, XXX, XXX, XXX, XXX, k2A, k2B, k2C, k2D, XXX }, \
    { k30, k31, k32, k33, k34, k35, XXX, XXX, XXX, XXX, k3A, k3B, k3C, k3D, XXX }, \
    { k40, k41, k42, k43, k44, k45, XXX, XXX, XXX, XXX, k4A, k4B, k4C, k4D, k4E }, \
    { XXX, k61, k62, k63, k64, k65, k66, k67, k68, k69, XXX, k6B, k6C, k6D, k6E }, \
    { XXX, k71, k72, k73, k74, k75, k76, k77, k78, XXX, XXX, k7B, k7C, k7D, k7E } \
}
