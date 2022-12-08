#pragma once

#include "quantum.h"
#include "led.h"

#define XXX KC_NO

#define LAYOUT( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, \
    k30, k31, k32, k33, k34,      k36, k37, k38, k39, k3A \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, XXX }, \
    { k30, k31, k32, k33, k34, XXX, k36, k37, k38, k39, k3A, XXX } \
}
