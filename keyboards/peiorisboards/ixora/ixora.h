#pragma once

#define XXX KC_NO

#include "quantum.h"

// This a shortcut to help you visually see your layout.

#define LAYOUT_FULL( \
    K00, K01, K02, \
    K03, K04, K05  \
) \
{ \
    { K00, K01, K02, K03, K04, K05 } \
}

#define LAYOUT_BLOCKER_RIGHT( \
    K00, K01,      \
    K03, K04, K05  \
) \
{ \
    { K00, K01, XXX, K03, K04, K05 } \
}

#define LAYOUT_BLOCKER_LEFT( \
         K01, K02, \
    K03, K04, K05  \
) \
{ \
    { XXX, K01, K02, K03, K04, K05 } \
}

#define LAYOUT_ARROWS( \
         K01,      \
    K03, K04, K05  \
) \
{ \
    { XXX, K01, XXX, K03, K04, K05 } \
}

