#pragma once

#include "quantum.h"

#define LAYOUT_60_ansi(\
     k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0e, \
     k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1e, \
     k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,      k2e, \
     k30, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,           k3c, \
     k40, k41, k42,                k47,                k4a, k4b, k4c, k4e  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0e, KC_NO }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1e, KC_NO }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, KC_NO, k2e, }, \
    { k30, KC_NO, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, KC_NO, k3c, KC_NO, }, \
    { k40, k41, k42, KC_NO, KC_NO, KC_NO, k47, KC_NO, KC_NO, k4a, k4b, k4c, KC_NO, KC_NO, k4e }, \
}

#define LAYOUT_60_iso(\
     k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0e, \
     k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,      \
     k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2e, k1e, \
     k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,      k3c, \
     k40, k41, k42,                k47,                k4a, k4b, k4c, k4e  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0e, KC_NO }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1e, KC_NO }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, KC_NO, k2e, }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, KC_NO, KC_NO, k3c, }, \
    { k40, k41, k42, KC_NO, KC_NO, KC_NO, k47, KC_NO, KC_NO, k4a, k4b, k4c, KC_NO, KC_NO, k4e }, \
}

#define LAYOUT_60_ansi_arrow(\
     k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0e, \
     k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1e, \
     k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,      k2e, \
     k30, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,           k3c, k3d, \
     k40, k41, k42,                k47,                k4a, k4b, k4c, k4e, k4f  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0e, KC_NO }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1e, KC_NO }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, KC_NO, k2e, }, \
    { k30, KC_NO, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, KC_NO, k3c, k3d, }, \
    { k40, k41, k42, KC_NO, KC_NO, KC_NO, k47, KC_NO, KC_NO, k4a, k4b, k4c, KC_NO, k4e, k4f, }, \
}

#define LAYOUT_60_ansi_split_bs(\
     k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0e, k0f, \
     k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1e, \
     k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,      k2e, \
     k30, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,           k3c, \
     k40, k41, k42,                k47,                k4a, k4b, k4c, k4e  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0e, k0f }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1e, KC_NO }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, KC_NO, k2e, }, \
    { k30, KC_NO, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, KC_NO, k3c, KC_NO }, \
    { k40, k41, k42, KC_NO, KC_NO, KC_NO, k47, KC_NO, KC_NO, k4a, k4b, k4c, KC_NO, KC_NO, k4e, }, \
}
