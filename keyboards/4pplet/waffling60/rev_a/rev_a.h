#pragma once

#include "quantum.h"

// k<row><col>
#define LAYOUT_all( \
    k00, k01, k11, k02, k03, k04, k05, k15, k06, k07, k08, k18, k09, k0a, k1a, \
    k10, k21, k12, k22, k13, k14, k25, k35, k16, k17, k28, k19, k29, k2a, \
    k20, k31, k32, k23, k33, k24, k45, k26, k36, k27, k38, k39, k3a, \
    k30, k40, k41, k42, k43, k34, k44, k55, k46, k37, k47, k48, k49, k4a, \
    k50, k51, k52, k53, k54, k56, k57, k58, k59, k5a  \
) \
{ \
    {k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a}, \
    {k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a}, \
    {k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a}, \
    {k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a}, \
    {k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a}, \
    {k50, k51, k52, k53, k54, k55, k56, k57, k58, k59, k5a}  \
}
