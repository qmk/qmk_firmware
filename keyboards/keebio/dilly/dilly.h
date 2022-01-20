#pragma once

#include "quantum.h"

#define LAYOUT_ortho_3x10( \
    k00, k01, k02, k03, k04, k34, k33, k32, k31, k30, \
    k10, k11, k12, k13, k14, k44, k43, k42, k41, k40, \
    k20, k21, k22, k23, k24, k54, k53, k52, k51, k50 \
) { \
    { k00, k01, k02, k03, k04 }, \
    { k10, k11, k12, k13, k14 }, \
    { k20, k21, k22, k23, k24 }, \
    { k30, k31, k32, k33, k34 }, \
    { k40, k41, k42, k43, k44 }, \
    { k50, k51, k52, k53, k54 } \
}
