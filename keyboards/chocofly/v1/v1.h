// Copyright 2022 Vitaly Volkov (@vlkv)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "chocofly.h"

#include "quantum.h"

#define K__ KC_NO

#define LAYOUT( \
         K01, K07, K02, K08, K03, K09,                      K11, K04, K12, K05, K13, K06, \
         K14, K22, K15, K23, K16, K24,                      K27, K19, K28, K20, K29, K21, \
         K30, K38, K31, K39, K32, K40, K10,                 K43, K35, K44, K36, K45, K37, \
         K46, K54, K47, K55, K48, K56, K25, K17,  K18, K26, K59, K51, K60, K52, K61, K53, \
                             K57, K49, K41, K33,  K34, K42, K50, K58 \
) \
{ \
    { K01, K02, K03, K__, K__, K04, K05, K06}, \
    { K07, K08, K09, K10, K__, K11, K12, K13}, \
    { K14, K15, K16, K17, K18, K19, K20, K21}, \
    { K22, K23, K24, K25, K26, K27, K28, K29}, \
    { K30, K31, K32, K33, K34, K35, K36, K37}, \
    { K38, K39, K40, K41, K42, K43, K44, K45}, \
    { K46, K47, K48, K49, K50, K51, K52, K53}, \
    { K54, K55, K56, K57, K58, K59, K60, K61}  \
}
