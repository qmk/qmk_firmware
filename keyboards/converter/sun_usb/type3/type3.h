/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

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

/* Sun type 3 keyboard
,-------.  ,-----------------------------------------------------------.  ,-----------.
| 01| 03|  | 05| 06|     08|     0A|     0C|     0E|     10| 11| 12| 2B|  | 15| 16| 17|
|-------|  |-----------------------------------------------------------|  |-----------|
| 19| 1A|  | 1D| 1E| 1F| 20| 21| 22| 23| 24| 25| 26| 27| 28| 29| 58| 2A|  | 2D| 2E| 2F|
|-------|  |-----------------------------------------------------------|  |-----------|
| 31| 33|  |  35 | 36| 37| 38| 39| 3A| 3B| 3C| 3D| 3E| 3F| 40| 41| 42  |  | 44| 45| 46|
|-------|  |-----------------------------------------------------------|  |-----------|
| 48| 49|  |  4C  | 4D| 4E| 4F| 50| 51| 52| 53| 54| 55| 56| 57|   59   |  | 5B| 5C| 5D|
|-------|  |-----------------------------------------------------------|  |-----------|
| 5F| 61|  |   63   | 64| 65| 66| 67| 68| 69| 6A| 6B| 6C| 6D|    6E| 6F|  | 70| 71| 72|
`-------'  |-----------------------------------------------------------|  `-----------'
           | 77 | 78  |               79                  | 7A  |   13 |
           `-----------------------------------------------------------'
*/
#define LAYOUT( \
    k01, k03,  k05, k06,      k08,      k0A,      k0C,      k0E,      k10, k11, k12, k2B,  k15, k16, k17, \
    k19, k1A,  k1D, k1E, k1F, k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k58, k2A,  k2D, k2E, k2F, \
    k31, k33,  k35,  k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E, k3F, k40, k41,     k42,  k44, k45, k46, \
    k48, k49,  k4C,   k4D, k4E, k4F, k50, k51, k52, k53, k54, k55, k56, k57,         k59,  k5B, k5C, k5D, \
    k5F, k61,  k63,    k64, k65, k66, k67, k68, k69, k6A, k6B, k6C, k6D,        k6E, k6F,  k70, k71, k72, \
               k77, k78,                      k79,                              k7A, k13 \
) { \
    { XXX, k01, XXX, k03, XXX, k05, k06, XXX }, \
    { k08, XXX, k0A, XXX, k0C, XXX, k0E, XXX }, \
    { k10, k11, k12, k13, XXX, k15, k16, k17 }, \
    { XXX, k19, k1A, XXX, XXX, k1D, k1E, k1F }, \
    { k20, k21, k22, k23, k24, k25, k26, k27 }, \
    { k28, k29, k2A, k2B, XXX, k2D, k2E, k2F }, \
    { XXX, k31, XXX, k33, XXX, k35, k36, k37 }, \
    { k38, k39, k3A, k3B, k3C, k3D, k3E, k3F }, \
    { k40, k41, k42, XXX, k44, k45, k46, XXX }, \
    { k48, k49, XXX, XXX, k4C, k4D, k4E, k4F }, \
    { k50, k51, k52, k53, k54, k55, k56, k57 }, \
    { k58, k59, XXX, k5B, k5C, k5D, XXX, k5F }, \
    { XXX, k61, XXX, k63, k64, k65, k66, k67 }, \
    { k68, k69, k6A, k6B, k6C, k6D, k6E, k6F }, \
    { k70, k71, k72, XXX, XXX, XXX, XXX, k77 }, \
    { k78, k79, k7A, XXX, XXX, XXX, XXX, XXX } \
}
