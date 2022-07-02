// Copyright 2022 Jean Bernard (@jn-bernard)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#define LAYOUT_iso( \
    k4D, k7C, k7B, k1B, k4B, k1A, k1F, k79, k77, k75, k78, k73, k13, k71, k31, k01, k23, \
    k7D, k0D, k0C, k2D, k1D, k7A, k7F, k09, k07, k05, k04, k15, k74, k08, k03, k21, \
    k0A, k0B, k1C, k2B, k2A, k2F, k19, k29, k27, k25, k24, k14, k17, k51, \
    k2C, k3D, k4C, k3B, k3A, k4A, k49, k39, k37, k35, k34, k45, k65, k33, k18, k11, \
    k5E, k6C, k5D, k5C, k5B, k5A, k6A, k69, k59, k57, k55, k44, k52, k63, k53, \
    k6H, k3F, k4G, k6B, k68, k46, k43, k60, k48, k64, k61	\
) \
{ \
    {KC_NO, k01,   KC_NO, k03, k04,   k05,   KC_NO, k07,   k08,   k09, k0A, k0B, k0C,   k0D,   KC_NO, KC_NO, KC_NO, KC_NO}, \
    {KC_NO, k11,   KC_NO, k13, k14,   k15,   KC_NO, k17,   k18,   k19, k1A, k1B, k1C,   k1D,   KC_NO, k1F,   KC_NO, KC_NO}, \
    {KC_NO, k21,   KC_NO, k23, k24,   k25,   KC_NO, k27,   KC_NO, k29, k2A, k2B, k2C,   k2D,   KC_NO, k2F,   KC_NO, KC_NO}, \
    {KC_NO, k31,   KC_NO, k33, k34,   k35,   KC_NO, k37,   KC_NO, k39, k3A, k3B, k6C,   k3D,   KC_NO, k3F,   KC_NO, KC_NO}, \
    {KC_NO, KC_NO, KC_NO, k43, k44,   k45,   k46,   KC_NO, k48,   k49, k4A, k4B, k4C,   k4D,   KC_NO, KC_NO, k4G,   KC_NO}, \
    {KC_NO, k51,   k52,   k53, k65,   k55,   KC_NO, k57,   KC_NO, k59, k5A, k5B, k5C,   k5D,   k5E,   KC_NO, KC_NO, KC_NO}, \
    {k60,   k61,   KC_NO, k63, k64,   KC_NO, KC_NO, KC_NO, k68,   k69, k6A, k6B, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k6H}, \
    {KC_NO, k71,   KC_NO, k73, k74,   k75,   KC_NO, k77,   k78,   k79, k7A, k7B, k7C,   k7D,   KC_NO, k7F,   KC_NO, KC_NO} \
}
