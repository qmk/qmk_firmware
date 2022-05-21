#pragma once

#include "quantum.h"

#define XXX KC_NO

#define LAYOUT( \
    k00, k01, k02, k03, k04, k05, k06, k07, k10, k11, k12, k13, k14,    k15, \
    k20,    k21, k22, k23, k24, k25, k26, k27, k30, k31, k32, k33, k34, k35, \
    k40,     k41, k42, k43, k44, k45, k46, k47, k50, k51, k52, k53,     k54, \
    k60,      k61, k62, k63, k64, k65, k66, k67, k55, k56, k57,         k37, \
    k70,  k71,  k72,               k73,               k74,  k75,  k76,  k77 \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07 }, \
    { k10, k11, k12, k13, k14, k15, XXX, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27 }, \
    { k30, k31, k32, k33, k34, k35, XXX, k37 }, \
    { k40, k41, k42, k43, k44, k45, k46, k47 }, \
    { k50, k51, k52, k53, k54, k55, k56, k57 }, \
    { k60, k61, k62, k63, k64, k65, k66, k67 }, \
    { k70, k71, k72, k73, k74, k75, k76, k77 } \
}
