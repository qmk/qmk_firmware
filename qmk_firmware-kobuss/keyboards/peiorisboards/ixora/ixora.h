#pragma once

#define XXX KC_NO

#include "quantum.h"

// This a shortcut to help you visually see your layout.

#define LAYOUT_full( \
    K00, K01, K02, \
    K03, K04, K05  \
) \
{ \
    { K00, K01, K02, K03, K04, K05 } \
}

#define LAYOUT_blocker_right( \
    K00, K01,      \
    K03, K04, K05  \
) \
{ \
    { K00, K01, XXX, K03, K04, K05 } \
}

#define LAYOUT_blocker_left( \
         K01, K02, \
    K03, K04, K05  \
) \
{ \
    { XXX, K01, K02, K03, K04, K05 } \
}

#define LAYOUT_arrows( \
         K01,      \
    K03, K04, K05  \
) \
{ \
    { XXX, K01, XXX, K03, K04, K05 } \
}

