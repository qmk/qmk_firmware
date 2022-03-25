// Copyright 2022 wavtype (@wavtype)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define _x_ KC_NO

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
    k00,   k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k2e,   k0f, k0g, k0h, \
    k10,   k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e,        k1f, k1g, k1h, \
	k20,   k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,                            \
	k30,   k31,      k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d,                  k3g,      \
	k40,   k41, k42, k43,                k47,                k4b, k4c, k4d, k4e,        k4f, k4g, k4h  \
) \
{ \
    { k00,   k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e,   k0f, k0g, k0h }, \
    { k10,   k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e,   k1f, k1g, k1h},  \
	{ k20,   k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e,   _x_, _x_, _x_},  \
    { k30,   k31, _x_, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, _x_,   _x_, k3g, _x_},  \
	{ k40,   k41, k42, k43, _x_, _x_, _x_, k47, _x_, _x_, _x_, k4b, k4c, k4d, k4e,   k4f, k4g, k4h}   \
}

#define LAYOUT_tkl_ansi_7u( \
    k00,   k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k2e,   k0f, k0g, k0h, \
    k10,   k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e,        k1f, k1g, k1h, \
	k20,   k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,                            \
	k30,   k31,      k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d,                  k3g,      \
	k40,   k41, k42, k43,                k47,                     k4c, k4d, k4e,        k4f, k4g, k4h  \
) \
{ \
    { k00,   k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e,   k0f, k0g, k0h }, \
    { k10,   k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e,   k1f, k1g, k1h},  \
	{ k20,   k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e,   _x_, _x_, _x_},  \
    { k30,   k31, _x_, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, _x_,   _x_, k3g, _x_},  \
	{ k40,   k41, k42, k43, _x_, _x_, _x_, k47, _x_, _x_, _x_, _x_, k4c, k4d, k4e,   k4f, k4g, k4h}   \
}

#define LAYOUT_tkl_iso( \
    k00,   k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k2e,   k0f, k0g, k0h, \
    k10,   k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e,        k1f, k1g, k1h, \
	k20,   k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,                            \
	k30,   k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e,             k3g,      \
	k40,   k41, k42, k43,                k47,                k4b, k4c, k4d, k4e,        k4f, k4g, k4h  \
) \
{ \
    { k00,   k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e,   k0f, k0g, k0h }, \
    { k10,   k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e,   k1f, k1g, k1h},  \
	{ k20,   k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e,   _x_, _x_, _x_},  \
    { k30,   k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e,   _x_, k3g, _x_},  \
	{ k40,   k41, k42, k43, _x_, _x_, _x_, k47, _x_, _x_, _x_, k4b, k4c, k4d, k4e,   k4f, k4g, k4h}   \
}

#define LAYOUT_tkl_iso_7u( \
     k00,   k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k2e,  k0f, k0g, k0h, \
    k10,   k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e,        k1f, k1g, k1h, \
	k20,   k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,                            \
	k30,   k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e,             k3g,      \
	k40,   k41, k42, k43,                k47,                     k4c, k4d, k4e,        k4f, k4g, k4h  \
) \
{ \
    { k00,   k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e,   k0f, k0g, k0h }, \
    { k10,   k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e,   k1f, k1g, k1h},  \
	{ k20,   k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e,   _x_, _x_, _x_},  \
    { k30,   k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e,   _x_, k3g, _x_},  \
	{ k40,   k41, k42, k43, _x_, _x_, _x_, k47, _x_, _x_, _x_, _x_, k4c, k4d, k4e,   k4f, k4g, k4h}   \
}
