#pragma once

#include "quantum.h"

#define LAYOUT( \
         k01, k02, k03, k04\
         k11, k12, k13, k14\
    k20, k21, k22, k23, k24, \
    k30, k31, k32, k33, k34 \
) \
{ \
    {KC_NO, k04, k03, k02, k01}, \
    {KC_NO, k14, k13, k12, k11}, \
    {k20,   k24, k23, k22, k21}, \
    {k30,   k34, k33, k32, k31} \
} 
