#pragma once

#include "quantum.h"

#define XXX KC_NO

#define LAYOUT( \
    K01, K02, K03, K04, \
    K11, K12, K13, K14, \
    K20, K21, K22, K23, K24  \
) { \
    { XXX, K01, K02, K03, K04 }, \
    { XXX, K11, K12, K13, K14 }, \
    { K20, K21, K22, K23, K24 }, \
}
