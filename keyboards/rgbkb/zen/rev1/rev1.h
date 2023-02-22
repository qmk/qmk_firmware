#pragma once

#include "quantum.h"

#define LAYOUT( \
    k00, k01, k02, k03, k04, k05,               k55, k54, k53, k52, k51, k50, \
    k10, k11, k12, k13, k14, k15,               k65, k64, k63, k62, k61, k60, \
    k20, k21, k22, k23, k24, k25,               k75, k74, k73, k72, k71, k70, \
    k30, k31, k32, k33, k34, k35,               k85, k84, k83, k82, k81, k80, \
    k40, k41, k42, k43, k44, k45, k46,   k96,   k95, k94, k93, k92, k91, k90 \
    ) \
    { \
        { k00, k01, k02, k03, k04, k05, KC_NO }, \
        { k10, k11, k12, k13, k14, k15, KC_NO }, \
        { k20, k21, k22, k23, k24, k25, KC_NO }, \
        { k30, k31, k32, k33, k34, k35, KC_NO }, \
        { k40, k41, k42, k43, k44, k45, k46 }, \
        { k50, k51, k52, k53, k54, k55, KC_NO }, \
        { k60, k61, k62, k63, k64, k65, KC_NO }, \
        { k70, k71, k72, k73, k74, k75, KC_NO }, \
        { k80, k81, k82, k83, k84, k85, KC_NO }, \
        { k90, k91, k92, k93, k94, k95, k96 } \
    }
