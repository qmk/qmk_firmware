// Copyright 2021 KiwiKey (@KiwiKey)
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
#define LAYOUT( \
	k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, k1E, \
	k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D,      k2E, \
	k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C,           k3E, \
	k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B,      k3D,           \
	k40,      k42,      k44, k45,      k47,      k49,           k4C, k4D, k4E       \
) \
{ \
	{ k00,   k01,   k02,   k03,   k04,   k05,   k06,   k07,   k08,   k09,   k0A,   k0B,   k0C,   k0D,   k0E }, \
	{ k10,   k11,   k12,   k13,   k14,   k15,   k16,   k17,   k18,   k19,   k1A,   k1B,   k1C,   k1D,   k1E }, \
	{ k20,   k21,   k22,   k23,   k24,   k25,   k26,   k27,   k28,   k29,   k2A,   k2B,   k2C,   KC_NO, k2E }, \
	{ k30,   k31,   k32,   k33,   k34,   k35,   k36,   k37,   k38,   k39,   k3A,   k3B,   KC_NO, k3D,   k3E }, \
	{ k40,   KC_NO, k42,   KC_NO, k44,   k45,   KC_NO, k47,   KC_NO, k49,   KC_NO, KC_NO, k4C,   k4D,   k4E }  \
}
