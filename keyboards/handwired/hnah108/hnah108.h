/* Copyright 2019 HnahKB
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

#define LAYOUT_all( \
    k00,      k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k60, k61,   k62, k63, k64,   k65, k66, k67, k68, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k70, k71, k72,   k73, k74, k75,   k76, k77, k78, k69, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k80, k81, k82,   k83, k84, k85,   k86, k87, k79, k6A, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k91, k93, k94,                    k96, k97, k88, \
    k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4A, k90,      k92,        k95,        k98, k99, k89, k7A, \
    k50, k51, k52,                k53,                k54, k55, k56, k57,   k58, k59, k5A,   k9A,      k8A \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4A }, \
    { k50, k51, k52, k53, k54, k55, k56, k57, k58, k59, k5A }, \
    { k60, k61, k62, k63, k64, k65, k66, k67, k68, k69, k6A }, \
    { k70, k71, k72, k73, k74, k75, k76, k77, k78, k79, k7A }, \
    { k80, k81, k82, k83, k84, k85, k86, k87, k88, k89, k8A }, \
    { k90, k91, k92, k93, k94, k95, k96, k97, k98, k99, k9A } \
}

#define LAYOUT_fullsize_iso( \
    k00,      k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k60, k61,   k62, k63, k64,   k65, k66, k67, k68, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k70, k71, k72,   k73, k74, k75,   k76, k77, k78, k69, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k80, k81,        k83, k84, k85,   k86, k87, k79, k6A, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k91, k93, k94,                    k96, k97, k88, \
    k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4A, k90,      k92,        k95,        k98, k99, k89, k7A, \
    k50, k51, k52,                k53,                k54, k55, k56, k57,   k58, k59, k5A,   k9A,      k8A \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4A }, \
    { k50, k51, k52, k53, k54, k55, k56, k57, k58, k59, k5A }, \
    { k60, k61, k62, k63, k64, k65, k66, k67, k68, k69, k6A }, \
    { k70, k71, k72, k73, k74, k75, k76, k77, k78, k79, k7A }, \
    { k80, k81, XXX, k83, k84, k85, k86, k87, k88, k89, k8A }, \
    { k90, k91, k92, k93, k94, k95, k96, k97, k98, k99, k9A } \
}

#define LAYOUT_fullsize_ansi( \
    k00,      k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k60, k61,   k62, k63, k64,   k65, k66, k67, k68, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k70, k71, k72,   k73, k74, k75,   k76, k77, k78, k69, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k80, k81, k82,   k83, k84, k85,   k86, k87, k79, k6A, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k91,      k94,                    k96, k97, k88, \
    k40,      k42, k43, k44, k45, k46, k47, k48, k49, k4A, k90,      k92,        k95,        k98, k99, k89, k7A, \
    k50, k51, k52,                k53,                k54, k55, k56, k57,   k58, k59, k5A,   k9A,      k8A \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A }, \
    { k40, XXX, k42, k43, k44, k45, k46, k47, k48, k49, k4A }, \
    { k50, k51, k52, k53, k54, k55, k56, k57, k58, k59, k5A }, \
    { k60, k61, k62, k63, k64, k65, k66, k67, k68, k69, k6A }, \
    { k70, k71, k72, k73, k74, k75, k76, k77, k78, k79, k7A }, \
    { k80, k81, k82, k83, k84, k85, k86, k87, k88, k89, k8A }, \
    { k90, k91, k92, XXX, k94, k95, k96, k97, k98, k99, k9A } \
}
