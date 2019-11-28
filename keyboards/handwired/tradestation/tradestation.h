#pragma once

#include "quantum.h"

#define LAYOUT_ortho_4x4( \
    K00, K01, K02, K03, \
    K10, K11, K12, K13, \
    K20, K21, K22, K23, \
    K30, K31, K32, K33  \
) { \
    { K00,   K01,   K02,   K03 }, \
    { K10,   K11,   K12,   K13 }, \
    { K20,   K21,   K22,   K23 }, \
    { K30,   K31,   K32,   K33 }  \
}

#define LAYOUT_tradestation( \
    K00, K01, K02, K03, \
    K10, K11, K12, K13, \
       K20,      K22,   \
       K30,      K32    \
) { \
    { K00,   K01,   K02,   K03   }, \
    { K10,   K11,   K12,   K13   }, \
    { K20,   KC_NO, K22,   KC_NO }, \
    { K30,   KC_NO, K32,   KC_NO }  \
}
