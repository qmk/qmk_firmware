#pragma once

#include "quantum.h"

#define XXX KC_NO

// This a shortcut to help you visually see your layout.
// The first section contains all of the arguements
// The second converts the arguments into a two-dimensional array
#define LAYOUT( \
    k04, k01, k13, k10, k22, k33,                k36, k27, k19, k16, k08, k05, \
    k03, k00, k12, k24, k21, k32, k43,      k46, k37, k28, k25, k17, k09, k06, \
    k02, k14, k11, k23, k20, k31, k42,      k47, k38, k29, k26, k18, k15, k07, \
                        k34, k44, k41,      k48, k45, k35 \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09 }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19 }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29 }, \
    { XXX, k31, k32, k33, k34, k35, k36, k37, k38, XXX }, \
    { XXX, k41, k42, k43, k44, k45, k46, k47, k48, XXX } \
}
