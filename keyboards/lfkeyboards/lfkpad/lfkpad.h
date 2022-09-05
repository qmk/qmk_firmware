#pragma once

#include "quantum.h"

#define ___ KC_NO

#define LAYOUT_numpad_6x4( \
    k00, k01, k02, k03, \
    k10, k11, k12, k13, \
    k20, k21, k22,      \
    k30, k31, k32, k23, \
    k40, k41, k42,      \
    k50,      k52, k43  \
) { \
    { k00, k01, k02, k03 }, \
    { k10, k11, k12, k13 }, \
    { k20, k21, k22, k23 }, \
    { k30, k31, k32, ___ }, \
    { k40, k41, k42, k43 }, \
    { k50, ___, k52, ___ } \
}
