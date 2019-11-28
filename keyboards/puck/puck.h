#ifndef PUCK_H
#define PUCK_H

#include "quantum.h"

#define LAYOUT( \
    K00, K01, K02, \
    K03, K04, K05, \
    K06, K07, K08, \
    K09, K0A, K0B  \
) { \
    { K00, K01, K02 }, \
    { K03, K04, K05 }, \
    { K06, K07, K08 }, \
    { K09, K0A, K0B }, \
}

#endif
