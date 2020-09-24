#pragma once

#include "quantum.h"

#define LAYOUT( \
        K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0a, K0b, K0c,\
        K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1a, K1b, K1c,\
        K20, K21, K22, K23, K24, K25, K26,      K28,      K2a, K2b, K2c \
) { \
        { K00, K01, K02, K03, K04, K05, K06, K07,   K08, K09,   K0a, K0b, K0c }, \
        { K10, K11, K12, K13, K14, K15, K16, K17,   K18, K19,   K1a, K1b, K1c }, \
        { K20, K21, K22, K23, K24, K25, K26, KC_NO, K28, KC_NO, K2a, K2b, K2c }  \
}

