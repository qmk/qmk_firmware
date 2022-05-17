// Copyright 2022 Andrew Dunai (@and3rson)
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef ENDGAME48_H
#define ENDGAME48_H

#include "quantum.h"
#include "config.h"

#define DEBUG_COLOR 0xFFFF00

#define NOPE KC_NO

enum eg_custom_keycodes {
    KC_EGMENU = SAFE_RANGE,
    EG_SAFE_RANGE,
};

#define LAYOUT( \
    K00, K01, K02, K03, K04, K05,      K40, K41, K42, K43, K44, K45, \
    K10, K11, K12, K13, K14, K15,      K50, K51, K52, K53, K54, K55, \
    K20, K21, K22, K23, K24, K25,      K60, K61, K62, K63, K64, K65, \
    K30, K31, K32, K33, K34, K35, K76, K70, K71, K72, K73, K74, K75 \
) { \
    {K00, K01, K02, K03, K04, K05, NOPE}, \
    {K10, K11, K12, K13, K14, K15, NOPE}, \
    {K20, K21, K22, K23, K24, K25, NOPE}, \
    {K30, K31, K32, K33, K34, K35, NOPE}, \
    {K40, K41, K42, K43, K44, K45, NOPE}, \
    {K50, K51, K52, K53, K54, K55, NOPE}, \
    {K60, K61, K62, K63, K64, K65, NOPE}, \
    {K70, K71, K72, K73, K74, K75, K76} \
}

void request_reset(void);

#endif
