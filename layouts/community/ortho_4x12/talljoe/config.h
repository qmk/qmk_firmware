#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include QMK_KEYBOARD_CONFIG_H
#define SPACE_COUNT 3

#define LAYOUT(                                                                     \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K2D,      \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D,           \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C,                \
    K30,      K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D,           \
    K40, K41, K42,      K44, K45, K46,      K48, K49,      K4B, K4C                 \
)                                                                                   \
LAYOUT_ortho_4x12(                                              \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1D, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, \
    K30, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, \
    K40, K41, K0D, K42, K44, K45, K45, K46, K48, K49, K4B, K4C  \
)


#endif //CONFIG_USER_H
