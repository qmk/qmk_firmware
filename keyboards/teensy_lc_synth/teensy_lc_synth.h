#ifndef TEENSY_LC_SYNTH_H
#define TEENSY_LC_SYNTH_H
#include "quantum.h"

#define KEYMAP( \
         k10, k01,      k02, k22, k13, \
      k00, k20, k11, k21, k12, k03, k23 \
) { \
    { k00, k01, k02, k03 }, \
    { k10, k11, k12, k13 }, \
    { k20, k21, k22, k23 }, \
}

#endif
