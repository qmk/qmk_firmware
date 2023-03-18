#pragma once

#include "quantum.h"

#define LAYOUT( \
  k00, k01, k02, k03, k04, k05,      \
       k11, k12, k13, k14, k15,      \
  k20, k21, k22, k23, k24, k25, k26, \
  k30, k31,           k34, k35, k36, \
  k40,                     k45, k46  \
) \
{ \
    { k00,   k01,   k02,   k03,   k04,   k05,   KC_NO }, \
    { KC_NO, k11,   k12,   k13,   k14,   k15,   KC_NO }, \
    { k20,   k21,   k22,   k23,   k24,   k25,   k26 }, \
    { k30,   k31,   KC_NO, KC_NO, k34,   k35,   k36 }, \
    { k40,   KC_NO, KC_NO, KC_NO, KC_NO, k45,   k46 } \
}
