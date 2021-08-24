#pragma once

#ifdef KEYBOARD_keebio_nyquist_rev1
    #include "rev1.h"
#endif
#ifdef KEYBOARD_keebio_nyquist_rev2
    #include "rev2.h"
#endif
#ifdef KEYBOARD_keebio_nyquist_rev3
    #include "rev3.h"
#endif

#include "quantum.h"

#define LAYOUT_ortho_4x12( \
    L00, L01, L02, L03, L04, L05, R00, R01, R02, R03, R04, R05, \
    L10, L11, L12, L13, L14, L15, R10, R11, R12, R13, R14, R15, \
    L20, L21, L22, L23, L24, L25, R20, R21, R22, R23, R24, R25, \
    L30, L31, L32, L33, L34, L35, R30, R31, R32, R33, R34, R35 \
    ) \
    LAYOUT_ortho_5x12( \
        L00, L01, L02, L03, L04, L05, R00, R01, R02, R03, R04, R05, \
        L10, L11, L12, L13, L14, L15, R10, R11, R12, R13, R14, R15, \
        L20, L21, L22, L23, L24, L25, R20, R21, R22, R23, R24, R25, \
        L30, L31, L32, L33, L34, L35, R30, R31, R32, R33, R34, R35, \
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO \
    )
