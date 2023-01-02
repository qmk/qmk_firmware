// Copyright 2021 s8erdude (@jpuerto96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define XXX KC_NO

#define LAYOUT_split_3x6_3( \
    k00, k01, k02, k03, k04, k05,	k011, k010, k09, k08, k07, k06,\
    k10, k11, k12, k13, k14, k15,	k111, k110, k19, k18, k17, k16,\
    k20, k21, k22, k23, k24, k25,	k211, k210, k29, k28, k27, k26,\
                   k33, k34, k35,	k311, k310, k39\
) { \
    { k00, k01, k02, k03, k04, k05 },\
    { k10, k11, k12, k13, k14, k15 },\
    { k20, k21, k22, k23, k24, k25 },\
    { XXX, XXX, XXX, k33, k34, k35 },\
    { k06, k07, k08, k09, k010, k011 },\
    { k16, k17, k18, k19, k110, k111 },\
    { k26, k27, k28, k29, k210, k211 },\
    { XXX, XXX, XXX, k39, k310, k311 }\
}
#define LAYOUT_split_3x5_3( \
    k01, k02, k03, k04, k05,	k011, k010, k09, k08, k07,\
    k11, k12, k13, k14, k15,	k111, k110, k19, k18, k17,\
    k21, k22, k23, k24, k25,	k211, k210, k29, k28, k27,\
                   k33, k34, k35,	k311, k310, k39\
) { \
    { XXX, k01, k02, k03, k04, k05 },\
    { XXX, k11, k12, k13, k14, k15 },\
    { XXX, k21, k22, k23, k24, k25 },\
    { XXX, XXX, XXX, k33, k34, k35 },\
    { XXX, k07, k08, k09, k010, k011 },\
    { XXX, k17, k18, k19, k110, k111 },\
    { XXX, k27, k28, k29, k210, k211 },\
    { XXX, XXX, XXX, k39, k310, k311 }\
}
