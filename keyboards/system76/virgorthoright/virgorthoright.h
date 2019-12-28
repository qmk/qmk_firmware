#ifndef VIRGORTHORIGHT_H
#define VIRGORTHORIGHT_H

#include "quantum.h"

#define ___ KC_NO

#define LAYOUT( \
 K00, K01, K02, K03, K04, K05, K06, K07, K08, \
 K10, K11, K12, K13, K14, K15,    K16,   K18, \
 K20, K21, K22, K23, K24, K25, K26, K27, K28, \
 K30, K31, K32, K33, K34, K35,    K36,   K38, \
 K40, K41, K42, K43, K44,    K45,   K47, K48, \
    K50,   K52, K53,    K54,   K56, K57, K58  \
) { \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08 }, \
    { K10, K11, K12, K13, K14, K15, K16, ___, K18 }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28 }, \
    { K30, K31, K32, K33, K34, K35, K36, ___, K38 }, \
    { K40, K41, K42, K43, K44, K45, ___, K47, K48 }, \
    { K50, ___, K52, K53, K54, ___, K56, K57, K58 }, \
}

#endif // VIRGORTHORIGHT_H
