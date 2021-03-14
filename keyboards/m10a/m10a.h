#pragma once

#include "quantum.h"

#define ___ KC_NO

#define LAYOUT( \
      k00, k01, k02, \
      k10, k11, k12, \
      k20, k21, k22, \
                k32  \
) \
{ \
    { k00, k01, k02 }, \
    { k10, k11, k12 }, \
    { k20, k21, k22 }, \
    { ___, ___, k32 } \
}
