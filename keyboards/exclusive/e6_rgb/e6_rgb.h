 /**
  * e6_rgb.h
  *
  */
#pragma once

#include "quantum.h"

#define ___ KC_NO

// This a shortcut to help you visually see your layout.
// The first section contains all of the arguements
// The second converts the arguments into a two-dimensional array
#define LAYOUT_60_ansi( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1e, \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2e, \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, \
    k40,      k42, k43,                k47, k48, k49, k4a, k4b       \
) \
{ \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, ___ }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1e }, \
    { k20, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2e, k0e }, \
    { k30, k32, k33, k34, k35, k36, k37, k38, ___, k39, k3a, k3b, k3c, ___ }, \
    { k40, k42, k43, ___, ___, ___, k47, ___, ___, ___, k48, k49, k4a, k4b }  \
}

#define LAYOUT_60_wkl( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1e, \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2e, \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, \
    k40,      k42, k43,                k47,      k49, k4a, k4b       \
) \
{ \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, ___ }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1e }, \
    { k20, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2e, k0e }, \
    { k30, k32, k33, k34, k35, k36, k37, k38, ___, k39, k3a, k3b, k3c, k3d }, \
    { k40, k42, k43, ___, ___, ___, k47, ___, ___, ___, ___, k49, k4a, k4b }  \
}

#define LAYOUT_60_hhkb( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1e, \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2e, \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, \
       k42, k43,                     k47,                k49, k4a \
) \
{ \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1e }, \
    { k20, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2e, k0e }, \
    { k30, k32, k33, k34, k35, k36, k37, k38, ___, k39, k3a, k3b, k3c, k3d }, \
    { ___, k42, k43, ___, ___, ___, k47, ___, ___, ___, ___, k49, k4a, ___ }  \
}

#define LAYOUT_60_wkl_split_bs( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1e, \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2e, \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, \
    k40,      k42, k43,                k47,      k49, k4a, k4b       \
) \
{ \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1e }, \
    { k20, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2e, k0e }, \
    { k30, k32, k33, k34, k35, k36, k37, k38, ___, k39, k3a, k3b, k3c, k3d }, \
    { k40, k42, k43, ___, ___, ___, k47, ___, ___, ___, ___, k49, k4a, k4b }  \
}
#define LAYOUT_60_ansi_split_bs_shift( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1e, \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2e, \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, \
    k40,      k42, k43,                k47,      k48,  k49, k4a, k4b       \
) \
{ \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1e }, \
    { k20, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2e, k0e }, \
    { k30, k32, k33, k34, k35, k36, k37, k38, ___, k39, k3a, k3b, k3c, k3d }, \
    { k40, k42, k43, ___, ___, ___, k47, ___, ___, ___, k48, k49, k4a, k4b }  \
}
