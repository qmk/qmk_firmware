/* Copyright 2020 Swiftrax and Basekeys.com
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

#define XXX KC_NO//readabilty 

/* This a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT( \
    k10,  k01,  k11,  k02,  k12,  k03,  k13,      k04,  k14,  k05,  k15,  k06,  k16,  k07,  k17,          k37,  \
    k30,  k21,  k31,  k22,  k32,  k23,            k33,  k24,  k34,  k25,  k35,  k26,  k36,  k27,          k57,  \
    k40,  k51,  k41,  k52,  k42,  k53,            k43,  k54,  k44,  k55,  k45,  k56,  k47,                k77,  \
    k70,  k61,  k71,  k62,  k72,  k63,            k73,  k64,  k74,  k65,  k75,  k66,  k76,          k67,        \
    k90,  k81,        k91,        k82,                  k94,        k85,  k95,  k86,          k96,  k87,  k97   \
) \
{ \
   { XXX,  k01,  k02,  k03,  k04,  k05,  k06,  k07}, \
   { k10,  k11,  k12,  k13,  k14,  k15,  k16,  k17}, \
   { XXX,  k21,  k22,  k23,  k24,  k25,  k26,  k27}, \
   { k30,  k31,  k32,  k33,  k34,  k35,  k36,  k37}, \
   { k40,  k41,  k42,  k43,  k44,  k45,  XXX,  k47}, \
   { XXX,  k51,  k52,  k53,  k54,  k55,  k56,  k57}, \
   { XXX,  k61,  k62,  k63,  k64,  k65,  k66,  k67}, \
   { k70,  k71,  k72,  k73,  k74,  k75,  k76,  k77}, \
   { XXX,  k81,  k82,  XXX,  XXX,  k85,  k86,  k87}, \
   { k90,  k91,  XXX,  XXX,  k94,  k95,  k96,  k97}  \
}
