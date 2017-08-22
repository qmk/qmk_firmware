#ifndef KB_H
#define KB_H

#include "quantum.h"

#define LAYOUT_ortho_4x4( \
    K00, K01, K02, K03, \
    K10, K11, K12, K13, \
    K20, K21, K22, K23, \
    K30, K31, K32, K33  \
) { \
    { K00,   K01,   K02,   K03 }, \
    { K10,   K11,   K12,   K13 }, \
    { K20,   K21,   K22,   K23 }, \
    { K30,   K31,   K32,   K33 }  \
}

#define LAYOUT_numpad_4x4( \
    K00, K01, K02, K03, \
    K10, K11, K12,      \
    K20, K21, K22, K23, \
       K31,   K32      \
) { \
    { K00,   K01,   K02,   K03 }, \
    { K10,   K11,   K12,   K13 }, \
    { K20,   K21,   K22,   K23 }, \
    { K30,   K31,   K32,   K33 }  \
}

#endif