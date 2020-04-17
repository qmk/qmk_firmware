#ifndef P20_H
#define P20_H

#include "quantum.h"

#define LAYOUT( \
    k00, k01, k02, k03, \
    k10, k11, k12, k13, \
    k20, k21, k22, k23, \
    k30, k31, k32, k33, \
    k40, k41, k42, k43 \
) \
{ \
    {k00, k01, k02, k03}, \
    {k10, k11, k12, k13}, \
    {k20, k21, k22, k23}, \
    {k30, k31, k32, k33}, \
    {k40, k41, k42, k43} \
} 

#endif
