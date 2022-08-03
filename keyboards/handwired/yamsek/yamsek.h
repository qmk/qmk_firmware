/* Copyright 2022 Johannes Schneider (@JohSchneider) */
/* SPDX-License-Identifier: GPL-2.0-or-later */
#pragma once

#include "quantum.h"

#ifdef RGBLIGHT_ENABLE
#    include "rgblight.h"
#endif

#include <gpio.h>
// defined in the used mainboard/MCU
extern const pin_t row_pins_MCU[MATRIX_ROWS / 2];
extern const pin_t col_pins_MCU[MATRIX_COLS];


// This a shortcut to help you visually see your layout.
// The following is an example using the Planck MIT layout
// The first section contains all of the arguements
// The second converts the arguments into a two-dimensional array
#define LAYOUT( \
    k00, k01, k02, k03, k04, k05, \
    k10, k11, k12, k13, k14, k15, \
    k20, k21, k22, k23, k24, k25, \
    \
    k30, k31, k32,     k33, k34, k35, \
    \
    \
    k40, k41, k42, k43, k44, k45,     \
    k50, k51, k52, k53, k54, k55,     \
    k60, k61, k62, k63, k64, k65,     \
                                      \
    k70, k71, k72,     k73, k74, k75  \
) \
{ \
    { k00, k01, k02, k03, k04, k05}, \
    { k10, k11, k12, k13, k14, k15}, \
    { k20, k21, k22, k23, k24, k25}, \
    { k30, k31, k32, k33, k34, k35}, \
        \
    { k40, k41, k42, k43, k44, k45}, \
    { k50, k51, k52, k53, k54, k55}, \
    { k60, k61, k62, k63, k64, k65}, \
    { k70, k71, k72, k73, k74, k75}, \
}
