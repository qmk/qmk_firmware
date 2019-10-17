#ifndef VINTA_H
#define VINTA_H

#define XXX KC_NO

#include "quantum.h"

// This a shortcut to help you visually see your layout.

#define LAYOUT_69_ansi( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, K0F, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C,      K1E, K1F, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B,           K2E, K2F, \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A,      K3C,      K3E, K3F, \
    K40, K41, K42,           K45,                K49, K4A,      K4C, K4D, K4E, K4F  \
) \
{ \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, K0F }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, XXX, K1E, K1F }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, XXX, XXX, K2E, K2F }, \
    { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, XXX, K3C, XXX, K3E, K3F }, \
    { K40, K41, K42, XXX, XXX, K45, XXX, XXX, XXX, K49, K4A, XXX, K4C, K4D, K4E, K4F }  \
}

#define LAYOUT_68_tada( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D,      K0F, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C,      K1E, K1F, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B,           K2E, K2F, \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A,      K3C,      K3E, K3F, \
    K40, K41, K42,           K45,                K49, K4A,      K4C, K4D, K4E, K4F  \
) \
{ \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, XXX, K0F }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, XXX, K1E, K1F }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, XXX, XXX, K2E, K2F }, \
    { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, XXX, K3C, XXX, K3E, K3F }, \
    { K40, K41, K42, XXX, XXX, K45, XXX, XXX, XXX, K49, K4A, XXX, XXX, K4D, K4E, K4F }  \
}

#define LAYOUT_65_ansi_blocker( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D,      K0F, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C,      K1E, K1F, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B,           K2E, K2F, \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A,      K3C,      K3E, K3F, \
    K40, K41, K42,           K45,                K49, K4A,           K4D, K4E, K4F  \
) \
{ \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, XXX, K0F }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, XXX, K1E, K1F }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, XXX, XXX, K2E, K2F }, \
    { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, XXX, K3C, XXX, K3E, K3F }, \
    { K40, K41, K42, XXX, XXX, K45, XXX, XXX, XXX, K49, K4A, XXX, XXX, K4D, K4E, K4F }  \
}

#endif
