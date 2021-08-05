#ifndef JD45_H
#define JD45_H

#include "quantum.h"

/* JD45 keymap definition macro
 */
#define LAYOUT( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, \
    k10,  k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a,     k1b, \
    k20,    k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a,   k2b, \
    k30, k31, k32, k33,      k34,     k36,       k38, k39, k3a, k3b  \
) { \
    { k00,   k01,   k02,   k03,   k04,   k05,   k06,   k07,   k08,   k09,   k0a,   k0b,   k0c   }, \
    { k10,   k11,   k12,   k13,   k14,   k15,   k16,   k17,   k18,   k19,   k1a,   k1b,   KC_NO }, \
    { k20,   k21,   k22,   k23,   k24,   k25,   k26,   k27,   k28,   k29,   k2a,   k2b,   KC_NO }, \
    { k30,   k31,   k32,   k33,   k34,   KC_NO, k36,   KC_NO, k38,   k39,   k3a,   k3b,   KC_NO }  \
}

#endif
