#pragma once

#include "quantum.h"
#include "matrix.h"
#include "keymap.h"
#ifdef BACKLIGHT_ENABLE
	#include "backlight.h"
#endif
#include <avr/io.h>
#include <stddef.h>

#define XXX KC_NO

// This is the 21-key keypad to 4x6 element matrix mapping
#define LAYOUT( \
    k00, k01, k02, k03, \
    k10, k11, k12, k13, \
    k20, k21, k22, k23, \
    k30, k31, k32, k33, \
    k40, k41, k42, k43, \
    k50, k51, k52, k53 \
) { \
    { k00, k01, k02, k03 }, \
    { k10, k11, k12, k13 }, \
    { k20, k21, k22, k23 }, \
    { k30, k31, k32, k33 }, \
    { k40, k41, k42, k43 }, \
    { k50, k51, k52, k53 } \
}

// This is the 21-key keypad to 2x11 element matrix mapping
#define LAYOUT_pad21( \
    k00, k01, k02, k03, \
    k10, k11, k12, k13, \
    k04, k05, k06, \
    k14, k15, k16, k07, \
    k08, k09, k0A, \
    k19,      k1A, k17 \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, XXX, k19, k1A } \
}
