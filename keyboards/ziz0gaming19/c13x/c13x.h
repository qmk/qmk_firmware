#pragma once

#include "quantum.h"

#define LAYOUT_10x4( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, \
    K10, K11, K12, K13, K14, K15, K16, K17,      K19, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, \
    K30, K31,      K33,      K35,      K37,      K39  \
) { \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09 }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, KC_NO, K19 }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29 }, \
    { K30, K31, KC_NO, K33, KC_NO, K35, KC_NO, K37, KC_NO, K39 } \
}
