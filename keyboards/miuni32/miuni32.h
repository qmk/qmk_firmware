#ifndef MIUNI32_H
#define MIUNI32_H

#include "quantum.h"

#define KEYMAP( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, \
    K20, K21, K22, K23,      K25, K26, K27, K28, K29, K2A ) { \
    { KC_##K00, KC_##K01, KC_##K02, KC_##K03, KC_##K04, KC_##K05, KC_##K06, KC_##K07, KC_##K08, KC_##K09, KC_##K0A }, \
    { KC_##K10, KC_##K11, KC_##K12, KC_##K13, KC_##K14, KC_##K15, KC_##K16, KC_##K17, KC_##K18, KC_##K19, KC_##K1A }, \
    { KC_##K20, KC_##K21, KC_##K22, KC_##K23, KC_NO, KC_##K25, KC_##K26, KC_##K27, KC_##K28, KC_##K29, KC_##K2A }  \
}

#endif
