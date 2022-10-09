// Copyright 2022 wavtype (@wavtype)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define _x_ KC_NO

#include "quantum.h"

/*
 *              ┌───┐ ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐ ┌───┬───┬───┐      ┌───────┐
 *              │00 │ │01 │02 │03 │04 │05 │06 │07 │08 │09 │0a │0b │0c │0d │0e │2e │ │0f │0g │0h │      │0e     │ 2u Backspace
 *              ├───┤ ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤ ├───┼───┼───┤      └─┬─────┤
 *              │10 │ │11   │12 │13 │14 │15 │16 │17 │18 │19 │1a │1b │1c │1d │1e   │ │1f │1g │1h │        │     │
 *  2.25u       ├───┤ ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ └───┴───┴───┘     ┌──┴┐1e  │ ISO Enter
 *  LShift      │20 │ │21    │22 │23 │24 │25 │26 │27 │28 │29 │2a │2b │2c │2d      │                   │2d │    │
 * ┌────────┐   ├───┤ ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤     ┌───┐       ┌─┴───┴────┤
 * │31      │   │30 │ │31  │32 │33 │34 │35 │36 │37 │38 │39 │3a │3b │3c │3d    │3e │     │3g │       │3d        │ 2.75u RShift
 * └────────┘   ├───┤ ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬┴───┤ ┌───┼───┼───┐   └──────────┘
 *              │40 │ │41  │42  │43  │47                      │4b  │4c  │4d  │4e  │ │4f │4g │4h │
 *              └───┘ └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘ └───┴───┴───┘
 *                    ┌─────┬───┬─────┬───────────────────────────┬─────┬───┬─────┐
 *                    │41   │42 │43   │47                         │4c   │4d │4e   │ Tsangan/WKL
 *                    └─────┴───┴─────┴───────────────────────────┴─────┴───┴─────┘
 */

#define LAYOUT_ansi_split_bs( \
    k00,   k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k2e,   k0f, k0g, k0h, \
    k10,   k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e,        k1f, k1g, k1h, \
    k20,   k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,                            \
    k30,   k31,      k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d,                  k3g,      \
    k40,   k41, k42, k43,                k47,                k4b, k4c, k4d, k4e,        k4f, k4g, k4h  \
) \
{ \
    { k00,   k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e,   k0f, k0g, k0h }, \
    { k10,   k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e,   k1f, k1g, k1h }, \
    { k20,   k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e,   _x_, _x_, _x_ }, \
    { k30,   k31, _x_, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, _x_,   _x_, k3g, _x_ }, \
    { k40,   k41, k42, k43, _x_, _x_, _x_, k47, _x_, _x_, _x_, k4b, k4c, k4d, k4e,   k4f, k4g, k4h }  \
}

#define LAYOUT_ansi_tsangan_split_bs( \
    k00,   k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k2e,   k0f, k0g, k0h, \
    k10,   k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e,        k1f, k1g, k1h, \
    k20,   k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,                            \
    k30,   k31,      k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d,                  k3g,      \
    k40,   k41, k42, k43,                k47,                     k4c, k4d, k4e,        k4f, k4g, k4h  \
) \
{ \
    { k00,   k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e,   k0f, k0g, k0h }, \
    { k10,   k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e,   k1f, k1g, k1h }, \
    { k20,   k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e,   _x_, _x_, _x_ }, \
    { k30,   k31, _x_, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, _x_,   _x_, k3g, _x_ }, \
    { k40,   k41, k42, k43, _x_, _x_, _x_, k47, _x_, _x_, _x_, _x_, k4c, k4d, k4e,   k4f, k4g, k4h }  \
}

#define LAYOUT_iso_split_bs_rshift( \
    k00,   k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k2e,   k0f, k0g, k0h, \
    k10,   k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,             k1f, k1g, k1h, \
    k20,   k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k1e,                       \
    k30,   k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e,             k3g,      \
    k40,   k41, k42, k43,                k47,                k4b, k4c, k4d, k4e,        k4f, k4g, k4h  \
) \
{ \
    { k00,   k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e,   k0f, k0g, k0h }, \
    { k10,   k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e,   k1f, k1g, k1h }, \
    { k20,   k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e,   _x_, _x_, _x_ }, \
    { k30,   k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e,   _x_, k3g, _x_ }, \
    { k40,   k41, k42, k43, _x_, _x_, _x_, k47, _x_, _x_, _x_, k4b, k4c, k4d, k4e,   k4f, k4g, k4h }  \
}

#define LAYOUT_iso_tsangan_split_bs_rshift( \
    k00,   k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k2e,   k0f, k0g, k0h, \
    k10,   k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,             k1f, k1g, k1h, \
    k20,   k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k1e,                       \
    k30,   k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e,             k3g,      \
    k40,   k41, k42, k43,                k47,                     k4c, k4d, k4e,        k4f, k4g, k4h  \
) \
{ \
    { k00,   k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e,   k0f, k0g, k0h }, \
    { k10,   k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e,   k1f, k1g, k1h }, \
    { k20,   k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e,   _x_, _x_, _x_ }, \
    { k30,   k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e,   _x_, k3g, _x_ }, \
    { k40,   k41, k42, k43, _x_, _x_, _x_, k47, _x_, _x_, _x_, _x_, k4c, k4d, k4e,   k4f, k4g, k4h }  \
}
