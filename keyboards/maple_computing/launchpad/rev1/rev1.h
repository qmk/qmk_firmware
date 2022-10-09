#pragma once

#include "../launchpad.h"

#include "quantum.h"

#define LAYOUT( \
    k00, k01, \
    k10, k11, \
    k20, k21, \
    k30, k31 \
) { \
    { k00, k01 }, \
    { k10, k11 }, \
    { k20, k21 }, \
    { k30, k31 } \
}
