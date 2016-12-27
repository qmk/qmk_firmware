#ifndef BLUEPAD_H
#define BLUEPAD_H

#include "keymap.h"
#include "quantum.h"
#include "matrix.h"
#include <avr/sfr_defs.h>

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif

#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

// This a shortcut to help you visually see your layout.
// The following is an example using the Planck MIT layout
// The first section contains all of the arguements
// The second converts the arguments into a two-dimensional array
#define KEYMAP( \
    k00, k01, k02, k03, \
    k10, k11, k12, k13, \
    k20, k21, k22, \
    k30, k31, k32, k33, \
    k40,      k42 \
) { \
    { k00, k01, k02, k03, }, \
    { k10, k11, k12, k13, }, \
    { k20, k21, k22, KC_NO, }, \
    { k30, k31, k32, k33, }, \
    { k40, KC_NO, k42, KC_NO } \
}

#endif
