 /* 
 Copyright 2020 Alec Penland
 Copyright 2020 Garret Gartner
  
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

#define xxx KC_NO

#define LAYOUT_split_space( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C,      k0D, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A,    k1B,        k1D, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A,         k2B,   k2D, \
    k30, k31,  k32,      k33,      k36,        k38,   k39,    k3A, k3B, k3D    \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, xxx, k1D }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, xxx, k2D }, \
    { k30, k31, k32, k33, xxx, xxx, k36, xxx, k38, k39, k3A, k3B, xxx, k3D }  \
}

#define LAYOUT_625_space( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C,      k0D, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A,    k1B,        k1D, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A,         k2B,   k2D, \
    k30, k31,  k32,            k36,                 k39,      k3A, k3B, k3D    \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, xxx, k1D }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, xxx, k2D }, \
    { k30, k31, k32, xxx, xxx, xxx, k36, xxx, xxx, k39, k3A, k3B, xxx, k3D }  \
}

#define LAYOUT_600_space( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C,      k0D, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A,    k1B,        k1D, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A,         k2B,   k2D, \
    k30, k31,  k32,            k36,           k38,    k39,    k3A, k3B, k3D    \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, xxx, k1D }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, xxx, k2D }, \
    { k30, k31, k32, xxx, xxx, xxx, k36, xxx, k38, k39, k3A, k3B, xxx, k3D }  \
}
