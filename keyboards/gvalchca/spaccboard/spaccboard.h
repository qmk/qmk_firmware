#pragma once

#include "quantum.h"

#define ___ KC_NO

#define LAYOUT( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,      \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,      k2d,      \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c,           \
    k40,      k42, k43,                k47,                k4b, k4c, k4d       \
) \
{ \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e },  \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, ___ },  \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, ___, k2d, ___ },  \
    { k30, ___, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, ___, ___ },  \
    { k40, ___, k42, k43, ___, ___, ___, k47, ___, ___, ___, k4b, k4c, k4d, ___ }   \
}

#define LAYOUT_ansi( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,      k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,      \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,      k2d,      \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c,           \
    k40,      k42, k43,                k47,                k4b, k4c, k4d       \
) \
{ \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, ___, k0e },  \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, ___ },  \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, ___, k2d, ___ },  \
    { k30, ___, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, ___, ___ },  \
    { k40, ___, k42, k43, ___, ___, ___, k47, ___, ___, ___, k4b, k4c, k4d, ___ }   \
}

#define LAYOUT_bae( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,           \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,      k2d,      \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c,           \
    k40,      k42, k43,                k47,                k4b, k4c, k4d       \
) \
{ \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e },  \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, ___, ___ },  \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, ___, k2d, ___ },  \
    { k30, ___, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, ___, ___ },  \
    { k40, ___, k42, k43, ___, ___, ___, k47, ___, ___, ___, k4b, k4c, k4d, ___ }   \
}
