#pragma once

#include "quantum.h"

#define XXX KC_NO

// This is a shortcut to help you visually see your layout.
#define LAYOUT_numpad_4x4( \
    k00, k01, k02, k03, \
    k10, k11, k12, \
    k20, k21, k22, k23, \
    k30,      k32 \
) { \
    { k00, k01, k02, k03 }, \
    { k10, k11, k12, XXX }, \
    { k20, k21, k22, k23 }, \
    { k30, XXX, k32, XXX } \
}

#define LAYOUT_ortho_4x4( \
    k00, k01, k02, k03, \
    k10, k11, k12, k13, \
    k20, k21, k22, k23, \
    k30, k31, k32, k33 \
) { \
    { k00, k01, k02, k03 }, \
    { k10, k11, k12, k13 }, \
    { k20, k21, k22, k23 }, \
    { k30, k31, k32, k33 } \
}
