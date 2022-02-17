#pragma once

#include "quantum.h"

#define LAYOUT_ortho_2x2( \
    k00, k01, \
    k10, k11 \
) { \
    { k00, k01 }, \
    { k10, k11 } \
}
