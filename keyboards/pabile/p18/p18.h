#ifndef P18_H
#define P18_H

#include "quantum.h"

#define LAYOUT( \
    k104, k103, k102, k101, \
    k204, k203, k202, k201, \
    k304, k303, k302, k301, k300\
    k404, k403, k402, k401, k400\
) \
{ \
    {k104, k103, k102, k101}, \
    {k204, k203, k202, k201}, \
    {k304, k303, k302, k301, k300}, \
    {k404, k403, k402, k401, k400} \
} 

#endif
