#pragma once

#include "quantum.h"

// Any changes to the layout names and/or definitions must also be made to info.json

#define LAYOUT( \
    K00, K01, \
    K10, K11, \
         K21, \
    K30, K31, \
    K40, K41, \
         K51 \
) { \
    { K00, K01 }, \
    { K10, K11 }, \
    { KC_NO, K21 }, \
    { K30, K31 }, \
    { K40, K41 }, \
    { KC_NO, K51 }  \
}
