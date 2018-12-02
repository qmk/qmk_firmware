#pragma once

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
    { K00, K01, K02, K03, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___}, \
    { K10, K11, K12, K13, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___}, \
    { K20, K21, K22, K23, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___}, \
    { K30, K31, K32, K33, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___} \
}
#define LAYOUT_ortho_4x8( \
    K00, K01, K02, K03, K04, K05, K06, K07, \
    K10, K11, K12, K13, K14, K15, K16, K17, \
    K20, K21, K22, K23, K24, K25, K26, K27, \
    K30, K31, K32, K33, K34, K35, K36, K37\
) \
{ \
    { K00, K01, K02, K03, K04, K05, K06, K07, ___, ___, ___, ___, ___, ___, ___, ___}, \
    { K10, K11, K12, K13, K14, K15, K16, K17, ___, ___, ___, ___, ___, ___, ___, ___}, \
    { K20, K21, K22, K23, K24, K25, K26, K27, ___, ___, ___, ___, ___, ___, ___, ___}, \
    { K30, K31, K32, K33, K34, K35, K35, K37, ___, ___, ___, ___, ___, ___, ___, ___} \
}
#define LAYOUT_ortho_4x12( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0a, K0b, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1a, K1b, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2a, K2b, \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3a, K3b  \
) \
{ \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0a, K0b, ___, ___, ___, ___}, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1a, K1b, ___, ___, ___, ___}, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2a, K2b, ___, ___, ___, ___}, \
    { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3a, K3b, ___, ___, ___, ___} \
}

#define LAYOUT_ortho_4x16( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0a, K0b, K0c, K0d, K0e, K0f, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1a, K1b, K1c, K1d, K1e, K1f, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2a, K2b, K2c, K2d, K2e, K2f, \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3a, K3b, K3c, K3d, K3e, K3f \
) \
{ \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0a, K0b, K0c, K0d, K0e, K0f }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1a, K1b, K1c, K1d, K1e, K1f }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2a, K2b, K2c, K2d, K2e, K2f }, \
    { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3a, K3b, K3c, K3d, K3e, K3f } \
}

#define LAYOUT_kc_ortho_4x12( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0a, K0b, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1a, K1b, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2a, K2b, \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3a, K3b  \
) \
{ \
    { KC_##K00, KC_##K01, KC_##K02, KC_##K03, KC_##K04, KC_##K05, KC_##K06, KC_##K07, KC_##K08, KC_##K09, KC_##K0a, KC_##K0b, ___, ___, ___, ___}, \
    { KC_##K10, KC_##K11, KC_##K12, KC_##K13, KC_##K14, KC_##K15, KC_##K16, KC_##K17, KC_##K18, KC_##K19, KC_##K1a, KC_##K1b, ___, ___, ___, ___}, \
    { KC_##K20, KC_##K21, KC_##K22, KC_##K23, KC_##K24, KC_##K25, KC_##K26, KC_##K27, KC_##K28, KC_##K29, KC_##K2a, KC_##K2b, ___, ___, ___, ___}, \
    { KC_##K30, KC_##K31, KC_##K32, KC_##K33, KC_##K34, KC_##K35, KC_##K36, KC_##K37, KC_##K38, KC_##K39, KC_##K3a, KC_##K3b, ___, ___, ___, ___} \
}
