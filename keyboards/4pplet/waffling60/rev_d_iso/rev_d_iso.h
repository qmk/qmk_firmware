#pragma once

#include "quantum.h"

// k<row><col>
#define LAYOUT_all( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k1d, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k2d,\
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c,  \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, \
    k40, k41, k42, k44, k46, k48, k4b, k4c, k4d  \
) \
{ \
    {k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d}, \
    {k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d}, \
    {k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d}, \
    {k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d}, \
    {k40, k41, k42, KC_NO, k44, KC_NO, k46, KC_NO, k48, KC_NO, KC_NO, k4b, k4c, k4d} \
}
