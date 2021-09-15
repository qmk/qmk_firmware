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

#include "mechmini.h"

#define ___ KC_NO

#define LAYOUT( \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, \
    K00, K01, K02,           K05,                K09, K0A  \
) \
{ \
    { K00, K01, K02, ___, ___, K05, ___, ___, ___, K09, K0A, ___ }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, ___ }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, ___ }, \
    { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B } \
}

#define LAYOUT_split_space( \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, \
    K00, K01, K02,      K03, K06, K08,           K09, K0A  \
) \
{ \
    { K00, K01, K02, K03, ___, ___, K06, ___, K08, K09, K0A, ___ }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, ___ }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, ___ }, \
    { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B } \
}
