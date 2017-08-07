#ifndef TEENSY_LC_SYNTH_H
#define TEENSY_LC_SYNTH_H
#include "quantum.h"

#define KEYMAP( \
         k31, k20,      k22, k10, k01, \
      k30, k32, k21, k11, k12, k00, k02 \
) { \
    { k00, k01, k02 }, \
    { k10, k11, k12 }, \
    { k20, k21, k22 }, \
    { k30, k31, k32 } \
}

#endif
