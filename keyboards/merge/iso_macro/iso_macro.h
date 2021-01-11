#ifndef ISOMACRO_H
#define ISOMACRO_H

#include "quantum.h"

#define LAYOUT( \
      k21, k00, k01, k02, k20, \
      k22, k10, k11, k12 \
) \
{ \
    { k00, k01, k02 }, \
    { k10, k11, k12 }, \
    { k20, k21, k22 }  \
} 

#endif
