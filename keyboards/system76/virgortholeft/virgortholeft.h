#ifndef VIRGORTHOLEFT_H
#define VIRGORTHOLEFT_H

#include "quantum.h"

#define ___ KC_NO

#define LAYOUT( \
 K00, K01, K02, K03, K04, K05, K06, \
 K10, K11, K12, K13, K14, K15, K16, \
    K21,   K22, K23, K24, K25, K26, \
    K31,   K32, K33, K34, K35, K36, \
    K41,   K42, K43, K44, K45, K46, \
    K51,   K52, K53, K54,    K56    \
) { \
    { K00, K01, K02, K03, K04, K05, K06 }, \
    { K10, K11, K12, K13, K14, K15, K16 }, \
    { ___, K21, K22, K23, K24, K25, K26 }, \
    { ___, K31, K32, K33, K34, K35, K36 }, \
    { ___, K41, K42, K43, K44, K45, K46 }, \
    { ___, K51, K52, K53, K54, ___, K56 }, \
}

#endif // VIRGORTHOLEFT_H
