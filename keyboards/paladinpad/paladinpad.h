#ifndef PALADINPAD_H
#define PALADINPAD_H

#include "quantum.h"

#define KEYMAP( \
    K_NUM1, K_EQ1, K_SLSH1, K_STAR1, \
    K_7, K_8, K_9, K_MINUS1, \
    K_4, K_5, K_6, K_PLUS, \
    K_1, K_2, K_3, K_11, \
    K_0, K_10, K_DOT1, K_ENT \
) { \
    { K_NUM1, K_EQ1, K_SLSH1, K_STAR1 }, \
    { K_7, K_8, K_9, K_MINUS1 }, \
    { K_4, K_5, K_6, K_PLUS }, \
    { K_1, K_2, K_3, K_ENT }, \
    { K_0, K_DOT1, K_10, K_11 } \
}

#endif
