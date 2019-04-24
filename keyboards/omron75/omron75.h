#pragma once

#include "quantum.h"

// readability
#define XXX KC_NO

#define LAYOUT_all( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08,      k0a, k0b, k0c, k0d, k0e, k0f, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,      k2f, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d,      k3f, \
    k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b, k4c, k4d,      k4f, \
    k50, k51,                     k56,                k5a, k5b, k5c, k5d,      k5f  \
) \
{ \
    {k00, k01, k02, k03, k04, k05, k06, k07, k08, XXX, k0a, k0b, k0c, k0d, k0e, k0f}, \
    {k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f}, \
    {k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, XXX, k2f}, \
    {k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, XXX, k3f}, \
    {k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b, k4c, k4d, XXX, k4f}, \
    {k50, k51, XXX, XXX, XXX, XXX, k56, XXX, XXX, XXX, k5a, k5b, k5c, k5d, XXX, k5f}  \
}

void matrix_init_user(void);
void matrix_scan_user(void);
