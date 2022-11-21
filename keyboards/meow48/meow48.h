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
    k01, k07, k02, k08, k03, k09, k15, k04, k10, k05, k11, k06, k12, \
    k13,  k19, k14, k20, k21, k27, k16, k22, k17, k23, k18,     k24, \
    k25,   k31, k26, k32, k33, k39, k28, k34, k29, k35, k30,    k36, \
    k37,  k43, k38, k44,    k45,    k40,    k46, k41, k47, k42, k48 \
    ) { \
    { k01, k02, k03, k04, k05, k06 }, \
    { k07, k08, k09, k10, k11, k12 }, \
    { k13, k14, k15, k16, k17, k18 }, \
    { k19, k20, k21, k22, k23, k24 }, \
    { k25, k26, k27, k28, k29, k30 }, \
    { k31, k32, k33, k34, k35, k36 }, \
    { k37, k38, k39, k40, k41, k42 }, \
    { k43, k44, k45, k46, k47, k48 } \
    }
