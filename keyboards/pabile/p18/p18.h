#ifndef P18_H
#define P18_H

#include "quantum.h"

#define LAYOUT( \
    k100, k101, k102, k103, k104, \
    k200, k201, k202, k203, k204, \
    k300, k301, k302, k303, k304, \
    k400, k401, k402, k403, k404 \
) \
{ \
    {k100, k101, k102, k103, k104}, \
    {k200, k201, k202, k203, k204}, \
    {k300, k301, k302, k303, k304}, \
    {k400, k401, k402, k403, k404} \
} 

#endif
