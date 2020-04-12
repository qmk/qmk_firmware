#pragma once

#include "quantum.h"

#define LAYOUT( \
    k00, k01, k02, k03, k04, \
    k10, k11, k12, k13, k14, \
    k20, k21, k22, k23, k24, \
    k30, k31, k32, k33, k34 \
) \
{ \
    {k00, k01, k02, k03, k04}, \
    {k10, k11, k12, k13, k14}, \
    {k20, k21, k22, k23, k24}, \
    {k30, k31, k32, k33, k34} \
} 


/* alternate? 
#define LAYOUT( \
          k101, k102, k103, k104, \
          k201, k202, k203, k204, \
    k300, k301, k302, k303, k304, \
    k400, k401, k402, k403, k404 \
) \
{ \
    {k101, k101, k102, k103, k104}, \
    {k201, k201, k202, k203, k204}, \
    {k300, k301, k302, k303, k304}, \
    {k400, k401, k402, k403, k404} \
} 

*/

#endif
