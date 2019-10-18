/* Copyright 2018 MechMerlin
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

// Written in the format K(row)(column) where numbering is in hexadecimal
#define LAYOUT( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E,  \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E,  \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2E,  \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E,  \
    k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B, k4C, k4D, k4E,  \
    k50, k51, k52, k53, k54, k55, k56, k57, k58, k59, k5A, k5B, k5C, k5D, k5E,  \
    k60, k61, k62, k63, k64, k65, k66, k67, k68, k69, k6A, k6B, k6C, k6D, k6E,  \
    k70, k71, k72, k73, k74, k75, k76, k77, k78, k79, k7A, k7B, k7C, k7D, k7E,  \
    k80, k81, k82, k83, k84, k85, k86, k87, k88, k89, k8A, k8B, k8C, k8D, k8E,  \
    k90, k91, k92, k93, k94, k95, k96, k97, k98, k99, k9A, k9B, k9C, k9D, k9E,  \
    kA0, kA1, kA2, kA3, kA4, kA5, kA6, kA7, kA8, kA9, kAA, kAB, kAC, kAD, kAE,  \
    kB0, kB1, kB2, kB3, kB4, kB5, kB6, kB7, kB8, kB9, kBA, kBB, kBC, kBD, kBE,  \
    kC0, kC1, kC2, kC3, kC4, kC5, kC6, kC7, kC8, kC9, kCA, kCB, kCC, kCD, kCE,  \
    kD0, kD1, kD2, kD3, kD4, kD5, kD6, kD7, kD8, kD9, kDA, kDB, kDC, kDD, kDE,  \
    kE0, kE1, kE2, kE3, kE4, kE5, kE6, kE7, kE8, kE9, kEA, kEB, kEC, kED, kEE  \
) \
{ \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2E, }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E, }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B, k4C, k4D, k4E, }, \
    { k50, k51, k52, k53, k54, k55, k56, k57, k58, k59, k5A, k5B, k5C, k5D, k5E, }, \
    { k60, k61, k62, k63, k64, k65, k66, k67, k68, k69, k6A, k6B, k6C, k6D, k6E, }, \
    { k70, k71, k72, k73, k74, k75, k76, k77, k78, k79, k7A, k7B, k7C, k7D, k7E, }, \
    { k80, k81, k82, k83, k84, k85, k86, k87, k88, k89, k8A, k8B, k8C, k8D, k8E, }, \
    { k90, k91, k92, k93, k94, k95, k96, k97, k98, k99, k9A, k9B, k9C, k9D, k9E, }, \
    { kA0, kA1, kA2, kA3, kA4, kA5, kA6, kA7, kA8, kA9, kAA, kAB, kAC, kAD, kAE, }, \
    { kB0, kB1, kB2, kB3, kB4, kB5, kB6, kB7, kB8, kB9, kBA, kBB, kBC, kBD, kBE, }, \
    { kC0, kC1, kC2, kC3, kC4, kC5, kC6, kC7, kC8, kC9, kCA, kCB, kCC, kCD, kCE, }, \
    { kD0, kD1, kD2, kD3, kD4, kD5, kD6, kD7, kD8, kD9, kDA, kDB, kDC, kDD, kDE, }, \
    { kE0, kE1, kE2, kE3, kE4, kE5, kE6, kE7, kE8, kE9, kEA, kEB, kEC, kED, kEE  } \
}
