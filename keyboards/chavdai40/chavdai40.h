#pragma once

#define XXX KC_NO

#include "quantum.h"

// This a shortcut to help you visually see your layout.

#define LAYOUT_44key( \
    k01, k02, k03, k04, k05, k06, k07, k08, k09, k10, k11, k12, k13, \
    k14 , k15, k16, k17, k18, k19, k20, k21, k22, k23, k24,  k25   , \
     k26 ,  k27, k28, k29, k30, k31, k32, k33, k34, k35,  k36,  k37, \
         k38,  k39,      k40,         k41,   k42,   k43,   k44       \
) { \
    { k01, k02, k03, k04, k05, k06, k07, k08, k09, k10, k11, k12, k13 }, \
    { k14, k15, k16, k17, k18, k19, k20, k21, k22, k23, k24, k25, XXX }, \
    { k26, k27, k28, k29, k30, k31, k32, k33, k34, k35, k36, k37, XXX }, \
    { k38, k39, XXX, k40, XXX, k41, XXX, XXX, k42, k43, k44, XXX, XXX }  \
}

#define LAYOUT_42key( \
    k01, k02, k03, k04, k05, k06, k07, k08, k09, k10, k11, k12, k13, \
    k14 , k15, k16, k17, k18, k19, k20, k21, k22, k23, k24,  k25   , \
     k26 ,  k27, k28, k29, k30, k31, k32, k33, k34, k35,  k36,  k37, \
         k38,  k39,                   k41,          k43,   k44       \
) { \
    { k01, k02, k03, k04, k05, k06, k07, k08, k09, k10, k11, k12, k13 }, \
    { k14, k15, k16, k17, k18, k19, k20, k21, k22, k23, k24, k25, XXX }, \
    { k26, k27, k28, k29, k30, k31, k32, k33, k34, k35, k36, k37, XXX }, \
    { k38, k39, XXX, XXX, XXX, k41, XXX, XXX, XXX, k43, k44, XXX, XXX }  \
}

