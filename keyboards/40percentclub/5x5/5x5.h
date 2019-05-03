#pragma once

#include "quantum.h"
#define ___ KC_NO

// This a shortcut to help you visually see your layout.
// The first section contains all of the arguments
// The second converts the arguments into a two-dimensional array

#define LAYOUT_ortho_5x5( \
    K00, K01, K02, K03, K04, \
    K10, K11, K12, K13, K14, \
    K20, K21, K22, K23, K24, \
    K30, K31, K32, K33, K34, \
    K40, K41, K42, K43, K44 \
) \
{ \
    { K00, K01, K02, K03, K04, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___}, \
    { K10, K11, K12, K13, K14, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___}, \
    { K20, K21, K22, K23, K24, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___}, \
    { K30, K31, K32, K33, K34, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___}, \
    { K40, K41, K42, K43, K44, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___} \
}

#define LAYOUT_ortho_5x10( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, \
    K40, K41, K42, K43, K44, K45, K46, K47, K48, K49 \
) \
{ \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, ___, ___, ___, ___, ___}, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, ___, ___, ___, ___, ___}, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, ___, ___, ___, ___, ___}, \
    { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, ___, ___, ___, ___, ___}, \
    { K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, ___, ___, ___, ___, ___} \
}

#define LAYOUT_ortho_5x15( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0a, K0b, K0c, K0d, K0e, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1a, K1b, K1c, K1d, K1e, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2a, K2b, K2c, K2d, K2e, \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3a, K3b, K3c, K3d, K3e, \
    K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4a, K4b, K4c, K4d, K4e \
) \
{ \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0a, K0b, K0c, K0d, K0e}, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1a, K1b, K1c, K1d, K1e}, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2a, K2b, K2c, K2d, K2e}, \
    { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3a, K3b, K3c, K3d, K3e}, \
    { K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4a, K4b, K4c, K4d, K4e} \
}
