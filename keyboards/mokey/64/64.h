#pragma once

#include "quantum.h"

// 64

#define LAYOUT( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,      k0e, \
    k10,      k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,      \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, \
    k40, k41,      k43,           k46,                k4a, k4b, k4c, k4d, k4e  \
) { \
    { k00,  k01,   k02,   k03,  k04,  k05,   k06,  k07,   k08,  k09,   k0a,  k0b,  k0c,   KC_NO,  k0e   }, \
    { k10,  KC_NO, k12,   k13,  k14,  k15,   k16,  k17,   k18,  k19,   k1a,  k1b,  k1c,   k1d,  k1e   }, \
    { k20,  KC_NO, k22,   k23,  k24,  k25,   k26,  k27,   k28,  k29,   k2a,  k2b,  k2c,   k2d,  KC_NO }, \
    { k30,  KC_NO, k32,   k33,  k34,  k35,   k36,  k37,   k38,  k39,   k3a,  k3b,  k3c, k3d,  k3e   }, \
    { k40,  k41,   KC_NO, k43,  KC_NO,  KC_NO, k46,  KC_NO, KC_NO,  KC_NO, k4a,  k4b,  k4c,   k4d,  k4e   }  \
}
