#pragma once

#include "quantum.h"

#define XXX KC_NO

#define LAYOUT( \
    k00, k01, k02, k03, k04,      \
    k10, k11, k12, k13,           \
    k20, k21, k22,                \
    k30, k31, k32, k33,           \
    k40, k41, k42,                \
    k50,      k52, k53, k54, k55  \
) { \
    { k00, k01, k02, k03, k04, XXX }, \
    { k10, k11, k12, k13, XXX, XXX }, \
    { k20, k21, k22, XXX, XXX, XXX }, \
    { k30, k31, k32, k33, XXX, XXX }, \
    { k40, k41, k42, XXX, XXX, XXX }, \
    { k50, XXX, k52, k53, k54, k55 }  \
}
