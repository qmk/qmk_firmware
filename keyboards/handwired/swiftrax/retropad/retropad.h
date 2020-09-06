#pragma once

#include "quantum.h"

// readability
#define XXX KC_NO

#define LAYOUT( \
       K001,    \
    K100, K101, \
    K200, K201  \
) { \
    {  XXX,  K001, }, \
    { K100,  K101, }, \
    { K200,  K201, }  \
}
