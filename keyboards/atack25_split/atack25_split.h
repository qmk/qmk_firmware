#ifndef ATACK25_SPLIT_H
#define ATACK25_SPLIT_H

#include "quantum.h"

#ifdef KEYBOARD_atack25_split_rev1
    #include "rev1.h"
#endif


// Used to create a keymap using only KC_ prefixed keys
#define LAYOUT_kc( \
    L00, L01, L02, L03, L04, R00, R01, R02, R03, R04, \
    L10, L11, L12, L13, L14, R10, R11, R12, R13, R14, \
    L20, L21, L22, L23, L24, R20, R21, R22, R23, R24, \
    L30, L31, L32, L33, L34, R30, R31, R32, R33, R34, \
    L40, L41, L42, L43, L44, R40, R41, R42, R43, R44 \
    ) \
    LAYOUT( \
        KC_##L00, KC_##L01, KC_##L02, KC_##L03, KC_##L04, KC_##R00, KC_##R01, KC_##R02, KC_##R03, KC_##R04, \
        KC_##L10, KC_##L11, KC_##L12, KC_##L13, KC_##L14, KC_##R10, KC_##R11, KC_##R12, KC_##R13, KC_##R14, \
        KC_##L20, KC_##L21, KC_##L22, KC_##L23, KC_##L24, KC_##R20, KC_##R21, KC_##R22, KC_##R23, KC_##R24, \
        KC_##L30, KC_##L31, KC_##L32, KC_##L33, KC_##L34, KC_##R30, KC_##R31, KC_##R32, KC_##R33, KC_##R34, \
        KC_##L40, KC_##L41, KC_##L42, KC_##L43, KC_##L44, KC_##R40, KC_##R41, KC_##R42, KC_##R43, KC_##R44 \
    )

#define KC_LAYOUT_ortho_5x10 LAYOUT_kc
#define LAYOUT_kc_ortho_5x10 LAYOUT_kc

#endif
