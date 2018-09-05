
#ifndef FOURX4_H
#define FOURX4_H

#include "quantum.h"
#define ___ KC_NO

// This a shortcut to help you visually see your layout.
// The first section contains all of the arguments
// The second converts the arguments into a two-dimensional array

#define LAYOUT_ortho_4x4( \
    K00, K01, K02, K03, \
    K10, K11, K12, K13, \
    K20, K21, K22, K23, \
    K30, K31, K32, K33 \
) \
{ \
    { K00, K01, K02, K03, ___, ___, ___, ___, ___, ___, ___, ___}, \
    { K10, K11, K12, K13, ___, ___, ___, ___, ___, ___, ___, ___}, \
    { K20, K21, K22, K23, ___, ___, ___, ___, ___, ___, ___, ___}, \
    { K30, K31, K32, K33, ___, ___, ___, ___, ___, ___, ___, ___} \
}
#define LAYOUT_ortho_4x8( \
    K00, K01, K02, K03, K04, K05, K06, K07, \
    K10, K11, K12, K13, K14, K15, K16, K17, \
    K20, K21, K22, K23, K24, K25, K26, K27, \
    K30, K31, K32, K33, K34, K35, K36, K37\
) \
{ \
    { K00, K01, K02, K03, K04, K05, K06, K07, ___, ___, ___, ___}, \
    { K10, K11, K12, K13, K14, K15, K16, K17, ___, ___, ___, ___}, \
    { K20, K21, K22, K23, K24, K25, K26, K27, ___, ___, ___, ___}, \
    { K30, K31, K32, K33, K34, K35, K35, K37, ___, ___, ___, ___} \
}
#define LAYOUT_ortho_4x12( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0a, K0b, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1a, K1b, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2a, K2b, \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3a, K3b  \
) \
{ \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0a, K0b}, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1a, K1b}, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2a, K2b}, \
    { K30, K31, K32, K33, K34, K35, K35, K37, K38, K39, K3a, K3b} \
}

#endif
