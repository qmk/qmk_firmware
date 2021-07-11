#pragma once

#include "quantum.h"

#ifdef KEYBOARD_adkb96_rev1
    #include "rev1.h"
#endif


// Used to create a keymap using only KC_ prefixed keys
#define LAYOUT_kc_ortho_6x16( \
    L00, L01, L02, L03, L04, L05, L06, L07, R00, R01, R02, R03, R04, R05, R06, R07, \
    L10, L11, L12, L13, L14, L15, L16, L17, R10, R11, R12, R13, R14, R15, R16, R17, \
    L20, L21, L22, L23, L24, L25, L26, L27, R20, R21, R22, R23, R24, R25, R26, R27, \
    L30, L31, L32, L33, L34, L35, L36, L37, R30, R31, R32, R33, R34, R35, R36, R37, \
    L40, L41, L42, L43, L44, L45, L46, L47, R40, R41, R42, R43, R44, R45, R46, R47, \
    L50, L51, L52, L53, L54, L55, L56, L57, R50, R51, R52, R53, R54, R55, R56, R57 \
    ) \
    LAYOUT( \
        KC_##L00, KC_##L01, KC_##L02, KC_##L03, KC_##L04, KC_##L05, KC_##L06, KC_##L07, KC_##R00, KC_##R01, KC_##R02, KC_##R03, KC_##R04, KC_##R05, KC_##R06, KC_##R07, \
        KC_##L10, KC_##L11, KC_##L12, KC_##L13, KC_##L14, KC_##L15, KC_##L16, KC_##L17, KC_##R10, KC_##R11, KC_##R12, KC_##R13, KC_##R14, KC_##R15, KC_##R16, KC_##R17, \
        KC_##L20, KC_##L21, KC_##L22, KC_##L23, KC_##L24, KC_##L25, KC_##L26, KC_##L27, KC_##R20, KC_##R21, KC_##R22, KC_##R23, KC_##R24, KC_##R25, KC_##R26, KC_##R27, \
        KC_##L30, KC_##L31, KC_##L32, KC_##L33, KC_##L34, KC_##L35, KC_##L36, KC_##L37, KC_##R30, KC_##R31, KC_##R32, KC_##R33, KC_##R34, KC_##R35, KC_##R36, KC_##R37, \
        KC_##L40, KC_##L41, KC_##L42, KC_##L43, KC_##L44, KC_##L45, KC_##L46, KC_##L47, KC_##R40, KC_##R41, KC_##R42, KC_##R43, KC_##R44, KC_##R45, KC_##R46, KC_##R47, \
        KC_##L50, KC_##L51, KC_##L52, KC_##L53, KC_##L54, KC_##L55, KC_##L56, KC_##L57, KC_##R50, KC_##R51, KC_##R52, KC_##R53, KC_##R54, KC_##R55, KC_##R56 ,KC_##R57 \
    )

#define LAYOUT_kc LAYOUT_kc_ortho_6x16
