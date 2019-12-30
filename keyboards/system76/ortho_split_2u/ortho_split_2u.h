#ifndef ORTHO_SPLIT_2U_H
#define ORTHO_SPLIT_2U_H

#include "quantum.h"

#define ___ KC_NO

#define LAYOUT( \
      K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, K0F, \
      K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C,    K1D,   K1F, \
         K21,   K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, K2E, K2F, \
         K31,   K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C,    K3D,   K3F, \
         K41,   K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4B,    K4C,   K4E, K4F, \
         K51,   K52, K53, K54,    K56,       K57,   K59, K5A,   K5B,   K56, K5E, K5F  \

) { \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, K0F }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, ___, K1F }, \
    { ___, K21, K22, K23, K24, K25, K26, K17, K28, K29, K2A, K2B, K2C, K2D, K2E, K2F }, \
    { ___, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D, ___, K3F }, \
    { ___, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4B, K4C, ___, K4E, K4F }, \
    { ___, K51, K52, K53, K54, ___, K56, K57, ___, K59, K5A, K5B, ___, K5D, K5E, K5F }, \
}

#endif // VIRGORTHOLEFT_H
