 /**
  * e6_rgb.h
  *
  */
#pragma once

#include "quantum.h"

#define ___ KC_NO

// This a shortcut to help you visually see your layout.
// The first section contains all of the arguements
// The second converts the arguments into a two-dimensional array
#define LAYOUT_60_ansi( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K2D, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B,      K2C, \
    K30,      K31, K32, K33, K34, K35, K36, K37, K39, K3A, K3B,      K3C, \
    K40, K41, K42,                K46,                K4A, K4B, K4C, K4D  \
) \
{ \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, ___ }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D }, \
    { K30, K31, K32, K33, K34, K35, K36, K37, ___, K39, K3A, K3B, K3C, ___ }, \
    { K40, K41, K42, ___, ___, ___, K46, ___, ___, ___, K4A, K4B, K4C, K4D }  \
}

#define LAYOUT_60_hhkb( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K2D, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B,      K2C, \
    K30,      K31, K32, K33, K34, K35, K36, K37, K39, K3A, K3B, K3C, K3D, \
         K41, K42,                K46,                     K4B, K4C       \
) \
{ \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D }, \
    { K30, K31, K32, K33, K34, K35, K36, K37, ___, K39, K3A, K3B, K3C, K3D }, \
    { ___, K41, K42, ___, ___, ___, K46, ___, ___, ___, ___, K4B, K4C, ___ }  \
}

#define LAYOUT_60_tsangan_hhkb( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K2D, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B,      K2C, \
    K30,      K31, K32, K33, K34, K35, K36, K37, K39, K3A, K3B, K3C, K3D, \
    K40, K41, K42,                K46,                     K4B, K4C, K4D  \
) \
{ \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D }, \
    { K30, K31, K32, K33, K34, K35, K36, K37, ___, K39, K3A, K3B, K3C, K3D }, \
    { K40, K41, K42, ___, ___, ___, K46, ___, ___, ___, ___, K4B, K4C, K4D }  \
}

#define LAYOUT_60_ansi_split_bs_rshift( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K2D, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B,      K2C, \
    K30,      K31, K32, K33, K34, K35, K36, K37, K39, K3A, K3B, K3C, K3D, \
    K40, K41, K42,                K46,                K4A, K4B, K4C, K4D  \
) \
{ \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D }, \
    { K30, K31, K32, K33, K34, K35, K36, K37, ___, K39, K3A, K3B, K3C, K3D }, \
    { K40, K41, K42, ___, ___, ___, K46, ___, ___, ___, K4A, K4B, K4C, K4D }  \
}
