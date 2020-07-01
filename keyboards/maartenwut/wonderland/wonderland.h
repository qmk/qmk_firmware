#pragma once
#include "quantum.h"

// readability
#define XXX KC_NO
#define LAYOUT( \
    k10, k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
    k20, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, \
    k30, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c,      k2e, \
         k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, \
         k41,           k43, k45, k46,      k48, k4a,                     k4e  \
) \
{ \
    {k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e}, \
    {k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e}, \
    {k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, XXX, k2e}, \
    {k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e}, \
    {XXX, k41, XXX, k43, XXX, k45, k46, XXX, k48, XXX, k4a, XXX, XXX, XXX, k4e}  \
}

void matrix_init_user(void);
void matrix_scan_user(void);
