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

#define LAYOUT_all( \
    k61, k71, k72, k73, k74, k64, k65, k75, k76, k77, k78, k68, k66, k1A, k6A,\
     k11, k01, k02, k03, k04, k14, k15, k05, k06, k07, k08, k18, k16,  k2A, \
      k12, k21, k22, k23, k24, k34, k35, k25, k26, k27, k28, k38,   k4A, \
    k19, k13, k41, k42, k43, k44, k54, k55, k45, k46, k47, k58,   k49,    k5A, \
    k09,   k0A,   k39,           k3A,                 k59,   k69,   k57,   k29 \
) { \
    { XXX, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A }, \
    { XXX, k11, k12, k13, k14, k15, k16, XXX, k18, k19, k1A }, \
    { XXX, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A }, \
    { XXX, XXX, XXX, XXX, k34, k35, XXX, XXX, k38, k39, k3A }, \
    { XXX, k41, k42, k43, k44, k45, k46, k47, XXX, k49, k4A }, \
    { XXX, XXX, XXX, XXX, k54, k55, XXX, k57, k58, k59, k5A }, \
    { XXX, k61, XXX, XXX, k64, k65, k66, XXX, k68, k69, k6A }, \
    { XXX, k71, k72, k73, k74, k75, k76, k77, k78, XXX, XXX } \
}

#define LAYOUT_60_ansi( \
    k61, k71, k72, k73, k74, k64, k65, k75, k76, k77, k78, k68, k66,      k6A, \
     k11, k01, k02, k03, k04, k14, k15, k05, k06, k07, k08, k18, k16,  k2A, \
      k12, k21, k22, k23, k24, k34, k35, k25, k26, k27, k28, k38,   k4A, \
    k19,      k41, k42, k43, k44, k54, k55, k45, k46, k47, k58,   k49, \
    k09,   k0A,   k39,           k3A,                 k59,   k69,   k57,   k29 \
) { \
    { XXX, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A }, \
    { XXX, k11, k12, XXX, k14, k15, k16, XXX, k18, k19, XXX }, \
    { XXX, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A }, \
    { XXX, XXX, XXX, XXX, k34, k35, XXX, XXX, k38, k39, k3A }, \
    { XXX, k41, k42, k43, k44, k45, k46, k47, XXX, k49, k4A }, \
    { XXX, XXX, XXX, XXX, k54, k55, XXX, k57, k58, k59, XXX }, \
    { XXX, k61, XXX, XXX, k64, k65, k66, XXX, k68, k69, k6A }, \
    { XXX, k71, k72, k73, k74, k75, k76, k77, k78, XXX, XXX } \
}
