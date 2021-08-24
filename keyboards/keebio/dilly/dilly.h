#ifndef DILLY_H
#define DILLY_H

#include "quantum.h"

#define LAYOUT_ortho_3x10( \
    A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, \
    B1, B2, B3, B4, B5, B6, B7, B8, B9, B10, \
    C1, C2, C3, C4, C5, C6, C7, C8, C9, C10 \
) { \
    { A1, A2, A3, A4, A5 }, \
    { B1, B2, B3, B4, B5 }, \
    { C1, C2, C3, C4, C5 }, \
    { A10, A9, A8, A7, A6 }, \
    { B10, B9, B8, B7, B6 }, \
    { C10, C9, C8, C7, C6 } \
}

#endif
