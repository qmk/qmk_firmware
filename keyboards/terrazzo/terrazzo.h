#pragma once

#include "quantum.h"

#define LAYOUT( \
    K00, K01, K02, K03, K04, K05, K70, K71, K72, K73, K74, K75, K65, \
    K10, K11, K12, K13, K14, K15, K60, K61, K62, K63, K64, K55, \
    K20, K21, K22, K23, K24, K25, K50, K51, K52, K53, K54, K45, \
    K30, K31, K32, K33, K40, K42, K43 \
){ \
    { K00, K01, K02, K03, K04, K05,},    \
    { K10, K11, K12, K13, K14, K15,},    \
    { K20, K21, K22, K23, K24, K25,},    \
    { K30, K31, K32, K33, KC_NO, KC_NO,},\
    { K40, KC_NO, K42, K43, KC_NO, K45,},\
    { K50, K51, K52, K53, K54, K55,},    \
    { K60, K61, K62, K63, K64, K65,},    \
    { K70, K71, K72, K73, K74, K75, },    \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, } \
}

//  R   Esc   Q    W    E    R    T    Y    U    I    O    P    Back
#define LAYOUT_ortho( \
    K00, K01, K02, K03, K04, K05, K70, K71, K72, K73, K74, K75, K65, \
    K10, K11, K12, K13, K14, K15, K60, K61, K62, K63, K64, K54, K55, \
    K20, K21, K22, K23, K24, K25, K50, K51, K52, K53, K43, K44, K45, \
    K30,      K31, K32, K33, K34, K35, K40, K41, K42  \
){ \
    { K00, K01, K02, K03, K04, K05,},    \
    { K10, K11, K12, K13, K14, K15,},    \
    { K20, K21, K22, K23, K24, K25,},    \
    { K30, K31, K32, K33, K34, K35,},    \
    { K40, K41, K42, K43, K44, K45,},    \
    { K50, K51, K52, K53, K54, K55,},    \
    { K60, K61, K62, K63, K64, K65,},    \
    { K70, K71, K72, K73, K74, K75, },    \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, } \
}


#define LAYOUT_ortho_2u( \
    K00, K01, K02, K03, K04, K05, K70, K71, K72, K73, K74, K75, K65, \
    K10, K11, K12, K13, K14, K15, K60, K61, K62, K63, K64, K54, K55, \
    K20, K21, K22, K23, K24, K25, K50, K51, K52, K53, K43, K44, K45, \
    K30,      K31, K32, K33, K84,   K35,    K85, K40, K41, K42  \
){ \
    { K00, K01, K02, K03, K04, K05,},    \
    { K10, K11, K12, K13, K14, K15,},    \
    { K20, K21, K22, K23, K24, K25,},    \
    { K30, K31, K32, K33, KC_NO, K35,},    \
    { K40, K41, K42, K43, K44, K45,},    \
    { K50, K51, K52, K53, K54, K55,},    \
    { K60, K61, K62, K63, K64, K65,},    \
    { K70, K71, K72, K73, K74, K75, },    \
    { KC_NO, KC_NO, KC_NO, KC_NO, K84, K85, } \
}

#define LAYOUT_ortho_all( \
    K00, K01, K02, K03, K04, K05, K70, K71, K72, K73, K74, K75, K65, \
    K10, K11, K12, K13, K14, K15, K60, K61, K62, K63, K64, K54, K55, \
    K20, K21, K22, K23, K24, K25, K50, K51, K52, K53, K43, K44, K45, \
    K30,      K31, K32, K33, K84, K34, K35, K85, K40, K41, K42  \
){ \
    { K00, K01, K02, K03, K04, K05,},    \
    { K10, K11, K12, K13, K14, K15,},    \
    { K20, K21, K22, K23, K24, K25,},    \
    { K30, K31, K32, K33, K34, K35,},    \
    { K40, K41, K42, K43, K44, K45,},    \
    { K50, K51, K52, K53, K54, K55,},    \
    { K60, K61, K62, K63, K64, K65,},    \
    { K70, K71, K72, K73, K74, K75, },    \
    { KC_NO, KC_NO, KC_NO, KC_NO, K84, K85, } \
}


enum terrazzo_matrix_effects {
    TERRAZZO_NONE = 0,
// --------------------------------------
// -----Begin led effect enum macros-----
#define TERRAZZO_EFFECT(name, ...) TERRAZZO_EFFECT_##name,
#include "terrazzo_effects/terrazzo_effects.inc"
#undef TERRAZZO_EFFECT
    // --------------------------------------
    // -----End led effect enum macros-------
    // All new effects go above this line
    TERRAZZO_EFFECT_MAX
};

void terrazzo_render(void);
void terrazzo_set_pixel(uint8_t x, uint8_t y, uint8_t value);
void terrazzo_draw_at(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t image[]);
void terrazzo_scroll_pixel(bool clockwise);
void terrazzo_step_mode(void);
void terrazzo_step_mode_reverse(void);
