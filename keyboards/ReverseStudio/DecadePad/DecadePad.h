#pragma once

#include "quantum.h"
#define LAYOUT( \
   k01, k02, k03, k04, \
   k11, k12, k13, k14, \
   k21, k22, k23,      \
   k31, k32, k33, k34, \
   k41, k42, k43,      \
   k51,      k53, k54  \
) \
{ \
    { k01, k02, k03, k04 }, \
    { k11, k12, k13, k14 }, \
    { k21, k22, k23      }, \
    { k31, k32, k33, k34 }, \
    { k41, k42, k43      }, \
    { k51,      k53, k54 }, \
}
