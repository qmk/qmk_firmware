#pragma once

#include "quantum.h"

// readability
#define XXX KC_NO

#define LAYOUT_tkl_f13_ansi( \
    K00,      K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D,   K0F, K0G, K0H, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D,        K1F, K1G, K1H, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2E,        K2F, K2G, K2H, \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B,      K3D, \
    K40,      K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A,      K4D,             K4G, \
    K50, K51, K52,                K55,                K58, K59, K5B, K5D,        K5F, K5G, K5H \
) { \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, XXX, K0F, K0G, K0H }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, XXX, K1F, K1G, K1H }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, XXX, K2E, K2F, K2G, K2H }, \
    { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, XXX, K3D, XXX, XXX, XXX, XXX }, \
    { K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A, XXX, XXX, K4D, XXX, XXX, K4G, XXX }, \
    { K50, K51, K52, XXX, XXX, K55, XXX, XXX, K58, K59, XXX, K5B, XXX, K5D, XXX, K5F, K5G, K5H } \
}

#define LAYOUT_tkl_f13_ansi_split_bs( \
    K00,      K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D,   K0F, K0G, K0H, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E,   K1F, K1G, K1H, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2E,        K2F, K2G, K2H, \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B,      K3D, \
    K40,      K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A,      K4D,             K4G, \
    K50, K51, K52,                K55,                K58, K59, K5B, K5D,        K5F, K5G, K5H \
) { \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, XXX, K0F, K0G, K0H }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, K1F, K1G, K1H }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, XXX, K2E, K2F, K2G, K2H }, \
    { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, XXX, K3D, XXX, XXX, XXX, XXX }, \
    { K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A, XXX, XXX, K4D, XXX, XXX, K4G, XXX }, \
    { K50, K51, K52, XXX, XXX, K55, XXX, XXX, K58, K59, XXX, K5B, XXX, K5D, XXX, K5F, K5G, K5H } \
}

#define LAYOUT_tkl_f13_ansi_tsangan( \
    K00,      K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D,   K0F, K0G, K0H, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D,        K1F, K1G, K1H, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2E,        K2F, K2G, K2H, \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B,      K3D, \
    K40,      K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A,      K4D,             K4G, \
    K50, K51, K52,                K55,                     K58, K5B, K5D,        K5F, K5G, K5H \
) { \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, XXX, K0F, K0G, K0H }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, XXX, K1F, K1G, K1H }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, XXX, K2E, K2F, K2G, K2H }, \
    { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, XXX, K3D, XXX, XXX, XXX, XXX }, \
    { K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A, XXX, XXX, K4D, XXX, XXX, K4G, XXX }, \
    { K50, K51, K52, XXX, XXX, K55, XXX, XXX, K58, XXX, XXX, K5B, XXX, K5D, XXX, K5F, K5G, K5H } \
}

#define LAYOUT_tkl_f13_ansi_tsangan_split_bs( \
    K00,      K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D,   K0F, K0G, K0H, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E,   K1F, K1G, K1H, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2E,        K2F, K2G, K2H, \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B,      K3D, \
    K40,      K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A,      K4D,             K4G, \
    K50, K51, K52,                K55,                     K58, K5B, K5D,        K5F, K5G, K5H \
) { \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, XXX, K0F, K0G, K0H }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, K1F, K1G, K1H }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, XXX, K2E, K2F, K2G, K2H }, \
    { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, XXX, K3D, XXX, XXX, XXX, XXX }, \
    { K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A, XXX, XXX, K4D, XXX, XXX, K4G, XXX }, \
    { K50, K51, K52, XXX, XXX, K55, XXX, XXX, K58, XXX, XXX, K5B, XXX, K5D, XXX, K5F, K5G, K5H } \
}

#define LAYOUT_all LAYOUT_tkl_f13_ansi_split_bs
